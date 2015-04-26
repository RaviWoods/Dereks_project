#include <TVout.h>
#include <fontALL.h>
#include "House.h"
#include "six.h"
TVout TV;

void setup() {
  TV.begin(NTSC,120,96);
  TV.select_font(font6x8);
}

void loop() {
   TV.clear_screen();
   TV.bitmap(0,0,six);
   TV.delay(10000);
}
