#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "util/Comms.h"
#include "util/Serial.h"
#include "pins/oledPins.h"
#include "settings/oledSet.h"
#include "OLED.h"

// display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// write to display
void writeToDisplay(String type, String msg) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("AAE Hawk");
    display.setCursor(0, 28);
    display.println(type);
    display.setCursor(0, 44);
    display.println(msg);
    display.display();
}

// initialize display
void initOLED() {
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(20);
    digitalWrite(OLED_RST, HIGH);
    Wire.begin(OLED_SDA, OLED_SCL);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) {
        srlError("Unable to initialized OLED");
        while (1);
    }
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(OLED_FONT_SIZE);
    writeToDisplay("Info:","Station Ready");
    srlInfo("OLED initialized");
}
