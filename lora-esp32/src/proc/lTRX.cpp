/*
    lTRX
    Protocol for intercommunication and packet parsing
*/

#include <Arduino.h>
#include "lTRX.h"
#include "util/LoRa.h"
#include "util/Controller.h"
#include "util/Serial.h"
#include "settings/ltrxset.h"

// timeouts for main loop
unsigned long prCL = 0;
unsigned long crCL = 0;
// keep track of packet count
unsigned int pktCnt = 0;

// craft control packets to be handled by receiver
void craftCTL(int t) {
    switch (t) {
        case 31:
            // most important packet
            // crafts controlle stick vals
            // ( A[val]E[val]R[val]Q )
            sendLoRa(t,
                "A" +
                String(fetchCtrl(0)) +
                "E" +
                String(fetchCtrl(1)) +
                "R" +
                String(fetchCtrl(2)) +
                "Q"
            );
            ++pktCnt;
            break;
        case 32:
            // L/R Shoulder Buttons
            // ( SR[val]SL[val]Q )
            sendLoRa(t,
                "SR" + 
                String(fetchBtn(0)) +
                "SL" +
                String(fetchBtn(1))
            );
            ++pktCnt;
            break;
        case 33:
            // Symbol Buttons
            // ( PX[val]PS[val]PT[val]PC[val]Q )
            sendLoRa(t,
                "PX" + 
                String(fetchBtn(2)) +
                "PS" + 
                String(fetchBtn(3)) +
                "PT" + 
                String(fetchBtn(4)) +
                "PC" + 
                String(fetchBtn(5))
            );
            ++pktCnt;
            break;
    }
}

// decoder function for lTRX packets
void declTRX(int msgType, String data) {
    switch (msgType) {
        /*
        case 10 ... 19:
            // LNK, @TODO, do nothing for now
            break;
        case 20 ... 29:
            // GPS, @TODO, do nothing for now
            break;
        */
    }
}

// lTRX main control loop
void lTRXctl() {
    crCL = millis();
    if (crCL - prCL > LTRX_DELAY) {
        prCL = crCL;
        craftCTL(31);
        if (pktCnt >= 16) { 
            craftCTL(32);
            craftCTL(33);
            craftCTL(34);
        }
    } else return;
}
