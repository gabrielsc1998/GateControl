// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : frontend_web.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/serial.h"
#include "Headers/gateControl.h"
#include "Headers/feedbackGate.h"
#include "Headers/Frontend_Web/frontend_web.h"

// ----------------------------------------------------------------------------------------- //

AsyncWebServer server(80);

// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : initializeFrontEndWeb
//
// Parameters : void
// Return     : void
//
// Description: Initialize the frontend web
//
// ########### ********************************************************************************

void initializeFrontEndWeb(void ) {

  initializeRouters();
  server.begin();
  
}

// ########### ********************************************************************************
//
// Function   : initializeRouters
//
// Parameters : void
// Return     : void
//
// Description: Initialize the routers of frontend web
//
// ########### ********************************************************************************

void initializeRouters(void ) {

  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(ON_STA_FILTER(request)) {
      if(!checkAuthentication(request)) {
        return request->requestAuthentication();
      }
    }
    request->send_P(200, F("text/html"), htmlPageGateControl);
  });

  server.on("/pulse", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(ON_STA_FILTER(request)) {
      if(!checkAuthentication(request)) {
        return request->requestAuthentication();
      }
    }
    request->send(200, F("text/html"), F(""));
    executePulseInGateControl();
  });

  server.on("/feedbackGate", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(ON_STA_FILTER(request)) {
      if(!checkAuthentication(request)) {
        return request->requestAuthentication();
      }
    }
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonObject jsonObject = response->getRoot();
    jsonObject[F("feedbackGate")] = getFeedbackGate();
    response->setLength();
    request->send(response);
  });

}

// ########### ********************************************************************************
//
// Function   : checkAuthentication
//
// Parameters : AsyncWebServerRequest *request -> ponteiro para a requisição do 'browser'
// Return     : void
//
// Description: Verifica a autenticação
//
// ########### ********************************************************************************

boolean checkAuthentication(AsyncWebServerRequest *request) {
  
  if(!request->authenticate("caetano@admin", "admin@cgo32437235")) {
    return false;
  } 

  return true;
}