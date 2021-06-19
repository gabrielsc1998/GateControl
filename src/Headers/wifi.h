// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : wifi.h
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#ifndef _WIFI_H
#define _WIFI_H

// ----------------------------------------------------------------------------------------- //

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>

// ----------------------------------------------------------------------------------------- //

enum WiFiManageStatus {

  _DISCONNECTED = 0,
  _CONNECTED,
  _AWAITING_CONNECTION,

};

// Estrutura de gerenciamento da rede wifi
struct __attribute__((packed)) ManageWiFi {
  uint8_t status = _DISCONNECTED;
};

extern ManageWiFi manageWiFi;

// ----------------------------------------------------------------------------------------- //

void initializeWiFi(void );
void initializeAccessPoint(void );
void initializeStationMode(void );
void wifiManageDependecies(void );
void initializeWiFiTask(void );
void wifiManageTask(void *pvParameters);
void wifiManageDependecies(void );
void changeAccessPointChannel(void );
void checkDisconnectionWiFi(void );

// ----------------------------------------------------------------------------------------- //

#endif

// ----------------------------------------------------------------------------------------- //
