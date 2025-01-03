// Simple 1-bit Adafruit_GFX-compatible framebuffer for PicoDVI.
#include <Arduino.h>
#include <PicoDVI.h>

// Here's how a 640x480 1-bit (black, white) framebuffer is declared.
// Second argument ('false' here) means NO double-buffering; all drawing
// operations are shown as they occur. Third argument is a hardware
// configuration -- examples are written for Adafruit Feather RP2040 DVI,
// but that's easily switched out for boards like the Pimoroni Pico DV
// (use 'pimoroni_demo_hdmi_cfg') or Pico DVI Sock ('pico_sock_cfg').

//不启用双缓冲
// DVIGFX1 display(DVI_RES_320x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_400x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_400x240p30, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_640x480p60, false, adafruit_lilygo_rp2350_cfg);
DVIGFX1 display(DVI_RES_800x480p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_800x480p30, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_640x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_800x240p60, false, adafruit_lilygo_rp2350_cfg);
// DVIGFX1 display(DVI_RES_800x240p30, false, adafruit_lilygo_rp2350_cfg);

// An 800x480 mode is possible but pushes overclocking even higher than
// 640x480 mode. SOME BOARDS MIGHT SIMPLY NOT BE COMPATIBLE WITH THIS.
// May require selecting QSPI div4 clock (Tools menu) to slow down flash
// accesses, may require further over-volting the CPU to 1.25 or 1.3 V.

void setup() { // Runs once on startup
  Serial.begin(115200);
  while (!display.begin()) { // Blink LED if insufficient RAM
    Serial.println("display begin fail!!!");
  }
}

void loop() {
  // Draw random lines
  display.drawLine(random(display.width()), random(display.height()), // Start X,Y
                   random(display.width()), random(display.height()), // End X,Y
                   random(2)); // Color (0 or 1)
}
