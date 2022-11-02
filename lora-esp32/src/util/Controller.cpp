/*
    Interfacing with the PS3 Controller
    and other stuff related to it
*/

#include <Arduino.h>
#include <Ps3Controller.h>
#include "Controller.h"
#include "util/Serial.h"
#include "util/OLED.h"
#include "settings/ps3Set.h"

// timeouts for main
unsigned long prCTRL = 0;
unsigned long crCTRL = 0;
// main stick val array
int stickOut[4];
// button array
int btnOut[6];

void onConnect() {
    srlInfo("ps3ctl", "Connected");
}

void initPs3() {
    Ps3.attachOnConnect(onConnect);
    Ps3.begin(MASTER_ADDRESS);
    srlInfo("ps3ctl", "Initialized");
    writeToDisplay("ps3ctl:", "Initialized");
}

void procps3() {
    if (Ps3.isConnected()) {
        // fetch all values
        stickOut[0] = Ps3.data.analog.stick.ry;
        stickOut[1] = Ps3.data.analog.stick.rx;
        stickOut[2] = Ps3.data.analog.stick.lx;
        stickOut[3] = Ps3.data.analog.stick.ly;
        btnOut[0] = Ps3.data.analog.button.r2;
        btnOut[1] = Ps3.data.analog.button.l2;
        btnOut[2] = Ps3.data.button.cross;
        btnOut[3] = Ps3.data.button.square;
        btnOut[4] = Ps3.data.button.triangle;
        btnOut[5] = Ps3.data.button.circle;
        // apply deadzone
        for (int i = 0; i < 4; i = i + 1) {
            if (stickOut[i] < DEADZONE && stickOut[i] > (DEADZONE*(-1)) ) {
                stickOut[i] = 0;
            }
        }
    } else return;
}

// main controller fetch loop
void ps3Stat() {
    if (Ps3.isConnected()) {
        crCTRL = millis();
        if (crCTRL - prCTRL > PS3_LOG_INTERVAL) {
            prCTRL = crCTRL;
            String LOG_STRING = "("
                + String(stickOut[0]) 
                + "/" + String(stickOut[1])
                + ") ("
                + String(stickOut[2])
                + "/" + String(stickOut[3])
                + ")";
            srlInfo("ps3ctl:", LOG_STRING);
            writeToDisplay("ps3ctl", LOG_STRING);
        } else return;
    } else return;
}

// expose controls
int fetchCtrl(int id) {
    return stickOut[id];
}

// expose buttons
int fetchBtn(int id) {
    return btnOut[id];
}
