#include "src/sim/data.h"

#include <cmath>
#include "base/base.h"

DEFINE_bool(print_html, false, "berobero");

namespace {
const double kSqrt3 = std::sqrt(3);
}

using googleapis::StrAppend;
using googleapis::StringAppendF;

void Field::print_html(std::ostream& os) const {
  int w = 2 + 2 * width();
  int h = 2 + kSqrt3 * height();
  string buf;
  StringAppendF(
    &buf,
    R"(<svg width=%dpt height=%dpt viewBox="0 0 %d %d" xmlns:xlink="http://www.w3.org/1999/xlink">
<defs><polygon id="h" fill="#eee" points="0,-1 .866,-.5 .866,.5 0,1 -.866,.5 -.866,-.5"/></defs>)", //"
    w * 10, h * 10, w, h);
  for (int i = 0; i < height(); ++i) {
    for (int j = 0; j < width() / 2; ++j) {
      double x = 1 + 2 * i + j % 2;
      double y = 1 + kSqrt3 * j;
      switch (data[i][j]) {
        case 'x':
          StringAppendF(&buf, R"(<use x="%.0f" y="%.2f" xlink:href="#h" fill="orange"/>)", x, y);
          break;
        case 'o':
          StringAppendF(&buf, R"(<use x="%.f" y="%.2f" xlink:href="#h" fill="lightskyblue"/>)", x, y);
          break;
        case '?':
          StringAppendF(&buf, R"(<use x="%.f" y="%.2f" xlink:href="#h" fill="greenyellow"/>)", x, y);
          break;
        case '@':
          StringAppendF(&buf, R"(<circle cx="%.f" cy="%.2f" r=".2" fill="red"/>)", x, y);
          break;
        case '&':
          StringAppendF(&buf, R"(<use x="%.f" y="%.2f" xlink:href="#h" fill="greenyellow"/>)", x, y);
          StringAppendF(&buf, R"(<circle cx="%.f" cy="%.2f" r=".2" fill="red"/>)", x, y);
          break;
        case '$':
          StringAppendF(&buf, R"(<use x="%.f" y="%.2f" xlink:href="#h" fill="orange"/>)", x, y);
          StringAppendF(&buf, R"(<circle cx="%.f" cy="%.2f" r=".2" fill="red"/>)", x, y);
          break;
        default:
          StringAppendF(&buf, R"(<use x="%.f" y="%.2f" xlink:href="#h"/>)", x, y);
          break;
      }
    }
  }
  StrAppend(&buf, "</svg>");
  os << buf << endl;
}
