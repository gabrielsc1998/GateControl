// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : ota.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/ota.h"
#include "Headers/serial.h"

// ----------------------------------------------------------------------------------------- //


// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : initializeOTA
//
// Parameters : void 
// Return     : void
//
// Description: Initialize OTA (Over-The-Air) to program wireless
//
// ########### ********************************************************************************

void initializeOTA(void ) {

    // Carrega o nome do HOST
    String hostName = "gate_control_" + WiFi.macAddress();
    ArduinoOTA.setHostname(hostName.c_str());

    ArduinoOTA.onStart([]() {
        #ifdef SERIAL_ENABLED
        Serial.println(F("Start"));
        #endif
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        #ifdef SERIAL_ENABLED
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        #endif
    });

    ArduinoOTA.onError([](ota_error_t error) {
        #ifdef SERIAL_ENABLED
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println(F("Auth Failed"));
        else if (error == OTA_BEGIN_ERROR) Serial.println(F("Begin Failed"));
        else if (error == OTA_CONNECT_ERROR) Serial.println(F("Connect Failed"));
        else if (error == OTA_RECEIVE_ERROR) Serial.println(F("Receive Failed"));
        else if (error == OTA_END_ERROR) Serial.println(F("End Failed"));
        #endif
    });

    ArduinoOTA.onEnd([]() {
        #ifdef SERIAL_ENABLED
        Serial.println(F("\nEnd"));
        #endif
    });

    ArduinoOTA.begin();

    #ifdef SERIAL_ENABLED
    Serial.println(F(" ## OTA Started!"));
    #endif

}

// ########### ********************************************************************************
//
// Function   : OTATasks
//
// Parameters : void
// Return     : void
//
// Description: Loop OTA (Over-The-Air) reading
//
// ########### ********************************************************************************

void OTATasks(void ) {
    
    ArduinoOTA.handle();
    
}