// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : frontend_web.h
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#ifndef _FRONTEND_WEB_H
#define _FRONTEND_WEB_H

// ----------------------------------------------------------------------------------------- //

#include <Arduino.h>
#include <AsyncTCP.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

#include "HTMLPages/gateControl.h"

// ----------------------------------------------------------------------------------------- //

extern AsyncWebServer server;

// ----------------------------------------------------------------------------------------- //

void initializeRouters(void );
void initializeFrontEndWeb(void );
boolean checkAuthentication(AsyncWebServerRequest *request);

// ----------------------------------------------------------------------------------------- //

#endif

// ----------------------------------------------------------------------------------------- //
