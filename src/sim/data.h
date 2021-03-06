#ifndef SRC_SIM_DATA_H_
#define SRC_SIM_DATA_H_

#include <algorithm>
#include <iostream>
#include "base/base.h"
#include "boost/property_tree/ptree.hpp"

DECLARE_bool(print_html);

using namespace std;
using boost::property_tree::ptree;

typedef pair<int, int> Point; // x * 2, y

inline Point load_point(const ptree& p) {
  int x = p.get<int>("x");
  int y = p.get<int>("y");
  return Point(x * 2 + y % 2, y);
}

inline Point point_offset(const Point& p, const Point& offset) {
  return Point(p.first + offset.first, p.second + offset.second);
}
inline Point point_subtract(const Point& p, const Point& offset) {
  return Point(p.first - offset.first, p.second - offset.second);
}

inline int div2(int x) {
  return (x % 2 != 0 ? x - 1 : x) / 2;
}

static constexpr char kMoveW[] = "p'!.03";
static constexpr char kMoveE[] = "bcefy2";
static constexpr char kMoveSW[] = "aghij4";
static constexpr char kMoveSE[] = "lmno 5";
static constexpr char kRotateCW[] = "dqrvz1";
static constexpr char kRotateCCW[] = "kstuwx";
static constexpr char kIgnored[] = "\t\n\r";

enum Command {
  UNKNOWN = 0,
  MOVE_W = 1,
  MOVE_E = 2,
  MOVE_SW = 3,
  MOVE_SE = 4,
  ROTATE_CW = 5,
  ROTATE_CCW = 6,
  IGNORED = 7,
};

inline Command translate_command(char c) {
  static const uint8 kTable[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,5,2,1,3,4,0,0,0,0,0,0,0,0,0,0,0,3,2,2,5,2,2,3,3,3,3,6,4,4,4,4,1,5,5,6,6,6,5,6,6,2,5,0,0,0,0,0,0,3,2,2,5,2,2,3,3,3,3,6,4,4,4,4,1,5,5,6,6,6,5,6,6,2,5};
  return static_cast<Command>(kTable[static_cast<int>(c)]);
};
inline const char* command_name(Command c) {
  switch (c) {
    case MOVE_W: return "move W";
    case MOVE_E: return "move E";
    case MOVE_SW: return "move SW";
    case MOVE_SE: return "move SE";
    case ROTATE_CW: return "rotate CW";
    case ROTATE_CCW: return "rotate CCW";
    case IGNORED: return "ignored";
    default: return "invalid";
  }
}

struct Field {
  // _ : empty
  // x : full
  vector<vector<char>> data;

  // Assumes height is aligned to even, width is doubled
  Field(int height, int width) {
    CHECK_GT(height, 0);
    CHECK_GT(width, 0);
    data.assign(height, vector<char>((width + 1) / 2, '_'));
  }

  bool contain(const Point& p) const {
    return 0 <= p.first && p.first < width() && 0 <= p.second && p.second < height();
  }
  char get(const Point& p) const {
    CHECK_EQ(p.first & 1, p.second & 1) << "Misaligned access";
    if (!contain(p)) return '#';
    return data[p.second][p.first / 2];
  }
  void set(const Point& p, char c) {
    CHECK_EQ(p.first & 1, p.second & 1) << "Misaligned access";
    CHECK_GE(p.first, 0);
    CHECK_GE(p.second, 0);
    CHECK_LT(p.first, width());
    CHECK_LT(p.second, height());
    data[p.second][p.first / 2] = c;
  }
  void fill(const vector<Point>& v, char c) {
    for (const auto& i : v) set(i, c);
  }
  void fill(const vector<Point>& v, Point offset, char c) {
    for (const auto& i : v) set(point_offset(i, offset), c);
  }
  // Returns if target points are empty.
  bool test(const Point& p) { return get(p) == '_'; }
  bool test(const vector<Point>& v, Point offset) {
    bool ok = true;
    for (const auto& i : v) ok = ok && test(point_offset(i, offset));
    return ok;
  }

  int height() const { return data.size(); }
  int width() const { return data[0].size() * 2; }

  // Clears full rows and slide remaining rows down alongside of edges.
  int clear_rows() {
    int n = stable_partition(data.begin(), data.end(), [](const vector<char>& row) {
      return all_of(row.begin(), row.end(), [](char c){ return c == 'x'; });
    }) - data.begin();
    for (int i = 0; i < n; ++i) data[i].assign(data[i].size(), '_');
    return n;
  }

  void print(std::ostream& os) const {
    if (FLAGS_print_html) {
      print_html(os);
      return;
    }
    for (int i = 0; i < height(); ++i) {
      int odd = i % 2;
      if (odd) os << " ";
      for (int j = 0; j < width() / 2; ++j) {
        os << data[i][j] << " ";
      }
      os << "\n";
    }
  }
  void print_html(std::ostream& os) const;
};

// A pivot origin unit
struct Unit {
  // The local origin is shifted to the pivot.
  vector<Point> members;

  void load(const ptree &p) {
    Point pivot = load_point(p.get_child("pivot"));
    for (const auto& i : p.get_child("members")) {
      members.push_back(point_subtract(load_point(i.second), pivot));
    }
    CHECK_GT(members.size(), 0);
  }
  int top_most() const {
    int e = members[0].second;
    for (int i = 1; i < members.size(); ++i) e = min(e, members[i].second);
    return e;
  }
  int bottom_most() const {
    int e = members[0].second;
    for (int i = 1; i < members.size(); ++i) e = max(e, members[i].second);
    return e;
  }
  int left_most() const {
    int e = members[0].first;
    for (int i = 1; i < members.size(); ++i) e = min(e, members[i].first);
    return e;
  }
  int right_most() const {
    int e = members[0].first;
    for (int i = 1; i < members.size(); ++i) e = max(e, members[i].first);
    return e;
  }
  // Returns sub-field to show the entire unit information.
  Field make_field() const {
    // Aligns offset even
    int top = min(0, top_most()) & ~1;
    int h = max(0, bottom_most()) - top + 1;
    int left = min(0, left_most()) & ~1;
    int w = max(0, right_most()) - left + 1;
    Field f(h, w);
    Point offset(-left, -top);
    f.fill(members, offset, 'o');
    f.set(offset, (f.test(offset) ? '@' : '&'));
    return f;
  }
  Unit rotate_cw() const {
    Unit u;
    u.members.resize(members.size());
    for (int i = 0; i < members.size(); ++i) {
      u.members[i] = Point((members[i].first - 3 * members[i].second) / 2, (members[i].first + members[i].second) / 2);
      // (... / 2) is safe, because (...) is always even.
    }
    return u;
  }
  Unit rotate_ccw() const {
    Unit u;
    u.members.resize(members.size());
    for (int i = 0; i < members.size(); ++i) {
      u.members[i] = Point((members[i].first + 3 * members[i].second) / 2, (members[i].second - members[i].first) / 2);
      // (... / 2) is safe, because (...) is always even.
    }
    return u;
  }
  // Returns the point relative to the local cordinate system on which the unit spawns.
  Point spawn(int width) const {
    return spawn1(width);
  }
  Point spawn2(int width) const {
    int y = -top_most();
    int x = (width - left_most());
    x = (x & ~1) + (y & 1);
    while (true) {
      int l = width / 2, r = width / 2;
      for (int i = 0; i < members.size(); ++i) {
        int z = x + members[i].first;
        l = min(l, div2(z));
        r = min(r, div2(width - 1 - z));
      }
      if (l <= r) return Point(x, y);
      x -= 2;
    }
  }
  Point spawn1(int width) const {
    int y = -top_most();
    int odd = y & 1;
    int l = div2(left_most() + odd);
    int r = div2(width - 1 - odd - right_most());
    int x = odd + ((r - l) & ~1);
    return Point(x, y);
  }
};

// All unique occupied and normalized positions of rotation of a unit
struct UnitCache {
  vector<Unit> rotation;

  void init(const Unit& unit) {
    rotation.push_back(unit);
    sort(rotation[0].members.begin(), rotation[0].members.end());
    for (Unit u = unit.rotate_cw(); ; u = u.rotate_cw()) {
      sort(u.members.begin(), u.members.end());
      if (u.members == rotation[0].members) break;
      rotation.push_back(u);
    }
  }
};

// A kind of unit placed on field
struct UnitControl {
  const UnitCache* cache;
  Point loc;
  // The current rotation to the original position.
  int angle;

  UnitControl(const UnitCache* c, Point p, int a)
      : cache(c), loc(p), angle(a) {}
  UnitControl(const UnitCache* c, int width)
      : cache(c), loc(c->rotation[0].spawn(width)), angle(0) {}
  const vector<Point>& members() const {
    return cache->rotation[angle].members;
  }
  // Commands
  UnitControl command(Command c) const {
    switch (c) {
      case MOVE_W: return move_w();
      case MOVE_E: return move_e();
      case MOVE_SW: return move_sw();
      case MOVE_SE: return move_se();
      case ROTATE_CW: return rotate_cw();
      case ROTATE_CCW: return rotate_ccw();
      case IGNORED: return *this;
      default: LOG(FATAL) << "Unrecognized command.";
    }
  }
  UnitControl move_w() const {
    return UnitControl(cache, Point(loc.first - 2, loc.second), angle);
  }
  UnitControl move_e() const {
    return UnitControl(cache, Point(loc.first + 2, loc.second), angle);
  }
  UnitControl move_sw() const {
    return UnitControl(cache, Point(loc.first - 1, loc.second + 1), angle);
  }
  UnitControl move_se() const {
    return UnitControl(cache, Point(loc.first + 1, loc.second + 1), angle);
  }
  UnitControl rotate_cw() const {
    return UnitControl(cache, loc, (angle + 1) % cache->rotation.size());
  }
  UnitControl rotate_ccw() const {
    return UnitControl(cache, loc, (angle + 5) % cache->rotation.size());
  }

  // Test if all cells empty
  bool test(Field* field) const {
    return field->test(members(), loc);
  }
  // Just returns # of cells
  int fill(Field* field, char c) const {
     field->fill(members(), loc, c);
     return members().size();
  }
  uint32 serialize() const {
    return (loc.first << 17) ^ (loc.second << 3) ^ angle;
  }
};

struct Problem {
  int width;
  int height;
  vector<int> seeds;
  vector<Unit> units;
  int id;
  vector<Point> filled;
  int length;

  void load(const ptree &p) {
    width = p.get<int>("width");
    height = p.get<int>("height");
    for (const auto& i : p.get_child("sourceSeeds")) {
      seeds.push_back(i.second.get_value<int>());
    }
    for (const auto& i : p.get_child("units")) {
      Unit u;
      u.load(i.second);
      units.push_back(u);
    }
    id = p.get<int>("id");
    for (const auto& i : p.get_child("filled")) {
      filled.push_back(load_point(i.second));
    }
    length = p.get<int>("sourceLength");
  }
  Field make_field() const {
    Field f(height, width * 2);
    f.fill(filled, 'x');
    return f;
  }
};

struct Solution {
  int id;
  int seed;
  string tag;
  string solution;

  void load(const ptree &p) {
    id = p.get<int>("problemId");
    seed = p.get<int>("seed");
    tag = p.get<string>("tag", "(notag)");
    solution = p.get<string>("solution");
  }
};

struct Output {
  vector<Solution> solutions;

  void load(const ptree &p) {
    for (const auto& i : p) {
      Solution s;
      s.load(i.second);
      solutions.push_back(s);
    }
  }
};

#endif  // SRC_SIM_DATA_H_
