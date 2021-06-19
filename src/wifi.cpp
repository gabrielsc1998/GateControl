// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : wifi.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// --------------------------------------------------------------------------------------------

#include "Headers/ota.h"
#include "Headers/wifi.h"
#include "Headers/serial.h"

// --------------------------------------------------------------------------------------------

static WiFiMulti WiFiMulti;
static TaskHandle_t handleWiFiTask;
ManageWiFi manageWiFi;

static uint8_t accessPointChannel[3] = {1, 6, 11};
static uint8_t currentChannel = 0;

// --------------------------------------------------------------------------------------------

// ########### ********************************************************************************
//
// Function   : initializeWiFi
//
// Parameters : void
// Return     : void
//
// Description: Inicializa o módulo WiFi
//
// ########### ********************************************************************************

void initializeWiFi(void ) {

  WiFi.disconnect(true, true); 
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_AP_STA);
  WiFi.setSleep(false);

  initializeAccessPoint();
  initializeStationMode();

}

// ########### ********************************************************************************
//
// Function   : initializeAccessPoint
//
// Parameters : void
// Return     : void
//
// Description: Inicializa o WiFi para o modo de 'access point'
//
// ########### ********************************************************************************

void initializeAccessPoint(void ) {

  WiFi.softAP("your_ssid", // SSID
              "your_password",  // password
              accessPointChannel[currentChannel],  // -> channel 
              0,  // -> ssid_hidden
              1); // -> max_connection 

  #ifdef SERIAL_ENABLED
  IPAddress IP = WiFi.softAPIP();
  Serial.print(F(" ## Access Point IP address: "));
  Serial.println(IP);
  #endif

}

// ########### ********************************************************************************
//
// Function   : initializeAccessPoint
//
// Parameters : void
// Return     : void
//
// Description: Inicializa o WiFi para o modo de 'access point'
//
// ########### ********************************************************************************

void changeAccessPointChannel(void ) {

  currentChannel++;
  if(currentChannel == 4) {
    currentChannel = 0;
  }

  initializeAccessPoint();

}

// ########### ********************************************************************************
//
// Function   : initializeStationMode
//
// Parameters : void
// Return     : void
//
// Description: Inicializa o WiFi para o modo 'state mode'
//
// ########### ********************************************************************************

void initializeStationMode(void ) {

  initializeWiFiTask();

  IPAddress ip(192, 168, 1, 44);
  IPAddress dns(8, 8, 8, 8);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress gateway(192, 168, 1, 1);

  WiFi.config(ip, gateway, subnet, dns); 

  WiFiMulti.addAP("your_net_ssid", "your_net_password");
  WiFiMulti.addAP("your_net2_ssid", "your_net2_password");

  manageWiFi.status = _AWAITING_CONNECTION;
  vTaskResume(handleWiFiTask);

}

// ########### ********************************************************************************
//
// Function   : initializeWiFiTask
//
// Parameters : void
// Return     : void
//
// Description: Inicializa a tarefa (task RTOS) do wifi
//
// ########### ********************************************************************************

void initializeWiFiTask(void ) {

  xTaskCreatePinnedToCore(wifiManageTask,  // Callback
                          "WiFiTask",      // Name of the task
                          3500,            // Stack size
                          NULL,            // Parameters 
                          1,               // Priority
                          &handleWiFiTask, // Handle
                          APP_CPU_NUM);    // CPU - core

  vTaskSuspend(handleWiFiTask);

}
  
// ########### ********************************************************************************
//
// Function   : wifiManageTask
//
// Parameters : void * pvParameters -> parâmetros de 'task' do RTOS (NULL)
// Return     : void
//
// Description: Tarefas (task rtos) do wifi
//
// ########### ********************************************************************************

void wifiManageTask(void *pvParameters) {

  while(1) {

    register uint16_t wdtTask = 1;
    register boolean _auxSuspendTask = false;
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); 

    if(WiFi.status() == WL_CONNECTED) {
      if(manageWiFi.status == _AWAITING_CONNECTION) {
        manageWiFi.status = _CONNECTED;

        #if defined(SERIAL_ENABLED)
        Serial.println(F(" ## WiFi connected!"));
        Serial.print(F(" ## Connected to: ")); 
        Serial.println(WiFi.SSID());
        Serial.print(F(" ## IP address: "));
        Serial.println(WiFi.localIP());
        Serial.print(" ## Subnet Mask: ");
        Serial.println(WiFi.subnetMask());
        Serial.print(" ## Gateway IP: ");
        Serial.println(WiFi.gatewayIP());
        Serial.print(" ## DNS 1: ");
        Serial.println(WiFi.dnsIP(0));
        #endif

        vTaskDelay( 1000 / portTICK_PERIOD_MS );
        wifiManageDependecies();
        _auxSuspendTask = true;
      }
    } else {

      if(manageWiFi.status == _CONNECTED) {

        #if defined(SERIAL_ENABLED)
        Serial.println(F(" ## WiFi Disconnected!"));
        #endif

        manageWiFi.status = _DISCONNECTED;
        wifiManageDependecies();
        manageWiFi.status = _AWAITING_CONNECTION;
      }

      if(!_auxSuspendTask) {
        WiFiMulti.run(1500);
        wdtTask = 15000;
      }
    }

    vTaskDelay( wdtTask / portTICK_PERIOD_MS ); 

    if(_auxSuspendTask) {
      vTaskSuspend(handleWiFiTask);
    }
  }
}

// ########### ********************************************************************************
//
// Function   : wifiManageDependecies
//
// Parameters : void
// Return     : void
//
// Description: Gerencia as dependências do WiFi
//
// ########### ********************************************************************************

void wifiManageDependecies(void ) {

  if(manageWiFi.status == _CONNECTED) {
    initializeOTA();   
  } else if(manageWiFi.status == _DISCONNECTED) {

  }
}

// ########### ********************************************************************************
//
// Function   : checkDisconnectionWiFi
//
// Parameters : void
// Return     : void
//
// Description: Verifica se houve uma desconexão da rede WiFi
//
// ########### ********************************************************************************

void checkDisconnectionWiFi(void ) {

  if(WiFi.status() != WL_CONNECTED) {
    vTaskResume(handleWiFiTask);
  }
}