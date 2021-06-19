// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : resetDevice.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/wifi.h"
#include "Headers/serial.h"
#include "Headers/resetDevice.h"

// ----------------------------------------------------------------------------------------- //

static TaskHandle_t handleResetDeviceTask;

// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : initializeResetDevice
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void initializeResetDevice(void ) {

  pinMode(GPIO_RESET_DEVICE, INPUT_PULLUP);

  xTaskCreatePinnedToCore(resetDeviceTask,       // Callback
                          "RstDeviceTask",       // Name of the task
                          1250,                   // Stack size
                          NULL,                   // Parameters 
                          1,                      // Priority
                          &handleResetDeviceTask, // Handle
                          PRO_CPU_NUM);           // CPU - core

  vTaskSuspend(handleResetDeviceTask);

  attachInterruptResetDevice();

}

// ########### ********************************************************************************
//
// Function   : attachInterruptResetDevice
//
// Parameters : void
// Return     : void
//
// Description: Liga a interrupção do botão
//
// ########### ********************************************************************************

void attachInterruptResetDevice(void ) {

  attachInterrupt(GPIO_RESET_DEVICE, interruptResetDevice, FALLING);
    
}

// ########### ********************************************************************************
//
// Function   : detachInterruptResetDevice
//
// Parameters : void
// Return     : void
//
// Description: Desliga a interrupção do botão
//
// ########### ********************************************************************************

void detachInterruptResetDevice(void ) {

  detachInterrupt(GPIO_RESET_DEVICE);
    
}

// ########### ********************************************************************************
//
// Function   : interruptResetDevice
//
// Parameters : void
// Return     : void
//
// Description: Interrupção do botão
//
// ########### ********************************************************************************

void IRAM_ATTR interruptResetDevice() {

  vTaskResume(handleResetDeviceTask);

}

// ########### ********************************************************************************
//
// Function   : readButton
//
// Parameters : void
// Return     : boolean -> resultado da leitura do botão
//
// Description: Lê o botão
//
// ########### ********************************************************************************

boolean readButton(void ) {

  return digitalRead(GPIO_RESET_DEVICE);

}

// ########### ********************************************************************************
//
// Function   : resetDeviceTask
//
// Parameters : void * pvParameters -> parâmetros de 'task' do RTOS (NULL)
// Return     : void
//
// Description: Tarefa (task rtos)
//
// ########### ********************************************************************************

void resetDeviceTask(void * pvParameters) {

  while(1) {

    detachInterruptResetDevice();

    vTaskDelay( _BUTTON_DEBOUNCE_TIME / portTICK_PERIOD_MS );

    if(readButton() == LOW) {
      #if defined(SERIAL_ENABLED)
      Serial.println(F(" ## Button Pressed!"));
      #endif

      WiFi.disconnect(true, true); 
      WiFi.mode(WIFI_OFF);
      vTaskDelay( 1000 / portTICK_PERIOD_MS );
      ESP.restart();

    }

    attachInterruptResetDevice();
    vTaskSuspend(handleResetDeviceTask);
  }

}