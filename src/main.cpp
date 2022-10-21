/*
  main file
  folder structure explained below

  src/
  ├─ main.cpp
  ├─ settings/
  │  ├─ header files with settings for other code modules
  ├─ pin/
  │  ├─ contains header files with pin definitions
  ├─ util/
  │  ├─ general use modules and code
*/

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
  handleLoRa();
  hwbtListener();
  ps3Stat();
}
