#include <Arduino.h>
#include "util/hwbts.h"
#include "util/Comms.h"
#include "util/Controller.h"
#include "util/Serial.h"
#include "util/OLED.h"

void setup() {
    Serial.begin(115200);
    initOLED();
    initLoRa();
    inithwbts();
    initPs3();
}

void loop() {
    hwbtListener();
    ps3Stat();
}
