// 8-bit Adafruit_GFX-compatible framebuffer for PicoDVI.

#include <PicoDVI.h>

// Here's how a 320x240 8-bit (color-paletted) framebuffer is declared.
// Second argument ('false' here) means NO double-buffering; all drawing
// operations are shown as they occur. Third argument is a hardware
// configuration -- examples are written for Adafruit Feather RP2040 DVI,
// but that's easily switched out for boards like the Pimoroni Pico DV
// (use 'pimoroni_demo_hdmi_cfg') or Pico DVI Sock ('pico_sock_cfg').

// DVIGFX8 display(DVI_RES_320x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_400x240p60, false, adafruit_lilygo_rp2350_cfg);
DVIGFX8 display(DVI_RES_400x240p30, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_640x480p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_800x480p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_800x480p30, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_640x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_800x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX8 display(DVI_RES_800x240p30, false, adafruit_lilygo_rp2350_cfg);

// A 400x240 mode is possible but pushes overclocking even higher than
// 320x240 mode. SOME BOARDS MIGHT SIMPLY NOT BE COMPATIBLE WITH THIS.
// May require selecting QSPI div4 clock (Tools menu) to slow down flash
// accesses, may require further over-volting the CPU to 1.25 or 1.3 V.
//DVIGFX8 display(DVI_RES_400x240p60, false, adafruit_feather_dvi_cfg);

void setup() { // Runs once on startup
    Serial.begin(115200);
    delay(2000);

    if (!display.begin())
    {
        Serial.println("display begin fail!!!");
    }

  // Randomize color palette. First entry is left black, last is set white.
  for (int i=1; i<255; i++) display.setColor(i, random(65536));
  display.setColor(255, 0xFFFF);
}

void loop() {
  // display.print("Hello World!");
  // Serial.println("loop");
  // delay(2000);
  // Draw random lines
  display.drawLine(random(display.width()), random(display.height()), random(display.width()), random(display.height()), random(256));
}
