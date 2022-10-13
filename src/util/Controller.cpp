#include <Arduino.h>
#include <Ps3Controller.h>
#include "util/Serial.h"
#include "util/OLED.h"
#include "settings/ps3Set.h"
#include "Controller.h"

unsigned long prevMillis = 0;

void onConnect() {
    srlInfo("ps3ctl: Connected");
}

void initPs3() {
    Ps3.attachOnConnect(onConnect);
    Ps3.begin(MASTER_ADDRESS);
    srlInfo("ps3ctl: Initialized");
    writeToDisplay("ps3ctl:", "Initialized");
}

void ps3Stat() {
    if (Ps3.isConnected()) {
        unsigned long currMillis = millis();
        if (currMillis - prevMillis > PS3_LOG_INTERVAL) {
            prevMillis = currMillis;
            String LOG_STRING = "("
                + String(Ps3.data.analog.stick.rx) 
                + "/" + String(Ps3.data.analog.stick.ry)
                + ") ("
                + String(Ps3.data.analog.stick.lx)
                + "/" + String(Ps3.data.analog.stick.ly)
                + ")";
            srlInfo("ps3ctl: " + LOG_STRING);
            writeToDisplay("ps3ctl", LOG_STRING);
        } else return;
    }
}
