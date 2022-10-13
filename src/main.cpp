#include <Arduino.h>
#include "util/hwbts.h"
#include "util/Comms.h"
#include "util/Serial.h"
#include "util/OLED.h"

void setup() {
    Serial.begin(115200);
    initOLED();
    inithwbts();
    initLoRa();
}

void loop() {
    hwbtListener();
}
