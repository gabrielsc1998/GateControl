// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : gateControl.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/serial.h"
#include "Headers/gateControl.h"

// ----------------------------------------------------------------------------------------- //

static TaskHandle_t handleGateControlTask;

// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : initializeGateControl
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void initializeGateControl(void ) {

  initializeGPIOGateControl();

  xTaskCreatePinnedToCore(gateControlTask,
                          "GateControlTask",
                          2000,
                          NULL,
                          1,
                          &handleGateControlTask,
                          PRO_CPU_NUM);

  vTaskSuspend(handleGateControlTask);

}

// ########### ********************************************************************************
//
// Function   : gateControlTask
//
// Parameters : void *pvParameters -> 
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void gateControlTask(void *pvParameters) {

  while(1) {

    vTaskDelay(100);

    digitalWrite(GPIO_GATE_CONTROL, LOW); 
    vTaskDelay(1000); 
    digitalWrite(GPIO_GATE_CONTROL, HIGH);

    vTaskDelay(100); 

    vTaskSuspend(handleGateControlTask);

  }
}

// ########### ********************************************************************************
//
// Function   : initializeGPIOGateControl
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void initializeGPIOGateControl(void ) {

  pinMode(GPIO_GATE_CONTROL, OUTPUT);
  digitalWrite(GPIO_GATE_CONTROL, HIGH);

}

// ########### *******************************************************************************
//
// Function   : executePulseInGateControl
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void executePulseInGateControl(void ) {

  vTaskResume(handleGateControlTask);

}
