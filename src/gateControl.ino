// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : gateControl.ino
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// --------------------------------------------------------------------------------------------

#include "Headers/led.h"
#include "Headers/ota.h"
#include "Headers/wifi.h"
#include "Headers/timer.h"
#include "Headers/serial.h"
#include "Headers/resetDevice.h"
#include "Headers/gateControl.h"
#include "Headers/feedbackGate.h"
#include "Headers/Frontend_Web/frontend_web.h"

// --------------------------------------------------------------------------------------------

// ########### ********************************************************************************
//
// Function   : setup
//
// Parameters : void
// Return     : void
//
// Description: General setup
//
// ########### ********************************************************************************

void setup(void ) {

  startTimers();
  initializeGateControl();
  initializeFeedbackGate();
  initializeSerial();
  initializeLed();
  initializeWiFi();
  initializeFrontEndWeb();
  initializeResetDevice();
  
} 

// ########### ********************************************************************************
//
// Function   : loop
//
// Parameters : void
// Return     : void
//
// Description: Main Loop
//
// ########### ********************************************************************************

void loop(void ) {
  
  loopTimers();

  if(manageWiFi.status == _CONNECTED) {
    OTATasks();
  } 

  if(timer[_15_sec]) {
    if(manageWiFi.status == _CONNECTED) {
      checkDisconnectionWiFi();
    }
  }

  if(timer[_15_min]) {
    changeAccessPointChannel();
  }

}