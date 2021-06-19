// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : serial.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/serial.h"

// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : initializeSerial
//
// Parameters : void
// Return     : void
//
// Description: Initialize device serial communication
//
// ########### ********************************************************************************

void initializeSerial(void ) {

  #if defined(SERIAL_ENABLED)

    Serial.begin(BAUD_RATE_SERIAL); while(!Serial); Serial.println(F("."));

  #endif

  #if defined(SERIAL_1_ENABLED)
  
    Serial1.begin(BAUD_RATE_SERIAL_1); while(!Serial1); Serial1.println(F("."));

  #endif

}
