#include <TVout.h>
#include <fontALL.h>

void setup() {
  TV.begin(NTSC,120,96);
  TV.select_font(font6x8);
  intro();
}

void loop() {
   TV.println("HELLLO");

}
