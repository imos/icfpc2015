#include <sstream>

#include "base/test.h"
#include "src/sim/data.h"
#include "src/sim/sim.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"

using boost::property_tree::json_parser::read_json;
using boost::property_tree::ptree;

TEST(HexSampleTest, Simulate) {
  std::stringstream ss1;
  ss1 << (R"(
      {
        "height":10,
        "width":10,
        "sourceSeeds":[0],
        "units":[
          {
            "members":[{"x":0,"y":0}],
            "pivot":{"x":0,"y":0}
          },{
            "members":[{"x":0,"y":0},{"x":1,"y":0}],
            "pivot":{"x":0,"y":0}
          },{
            "members":[{"x":0,"y":0},{"x":1,"y":0},{"x":2,"y":0}],
            "pivot":{"x":1,"y":0}
          },{
            "members":[{"x":0,"y":0},{"x":1,"y":0},{"x":0,"y":1}],
            "pivot":{"x":0,"y":0}
          },{
            "members":[{"x":0,"y":0},{"x":1,"y":0},{"x":1,"y":1}],
            "pivot":{"x":1,"y":0}
          }],
        "id":6,
        "filled":[],
        "sourceLength":150})");
  ptree data;
  read_json(ss1, data);

  Problem p;
  p.load(data);

  std::stringstream ss2;
  ss2 << R"(
      {
        "problemId": 6,
        "seed": 0,
        "tag": "sample play",
        "solution": "iiiiiiimimiiiiiimmimiiiimimimmimimimimmeemmimimiimmmmimmimiimimimmimmimeeemmmimimmimeeemiimiimimimiiiipimiimimmmmeemimeemimimimmmmemimmimmmiiimmmiiipiimiiippiimmmeemimiipimmimmipppimmimeemeemimiieemimmmm"
      })";
  read_json(ss2, data);
  Solution s;
  s.load(data);

  Sim sim(p, s);
  EXPECT_EQ(61, sim.Play());

  std::stringstream ss3;
  sim.field_.print(ss3);

  EXPECT_EQ(
      "_ _ _ _ x x _ _ _ _ \n"
      " _ _ _ _ x x _ _ _ _ \n"
      "x x _ _ x x x x _ _ \n"
      " x x x _ x x x x _ _ \n"
      "_ x x _ _ x x x _ _ \n"
      " _ x x x x x x x x _ \n"
      "_ _ x x x x x x x _ \n"
      " x _ x x x x x x x _ \n"
      "x _ x x x x x x x _ \n"
      " x x x _ x x x x x _ \n",
      ss3.str());
}
