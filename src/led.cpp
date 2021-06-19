// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : serial.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/led.h"
#include "Headers/serial.h"

// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : initializeLed
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void initializeLed(void ) {

  initializeGPIOLed();
  initializeLedControlTask();

}

// ########### ********************************************************************************
//
// Function   : initializeGPIOLed
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void initializeGPIOLed(void ) {

  pinMode(GPIO_LED, OUTPUT);
  digitalWrite(GPIO_LED, HIGH);

}

// ########### *******************************************************************************
//
// Function   : initializeLedControlTask
//
// Parameters : void
// Return     : void
//
// Description: Inicializa a tarefa de controle do Led
//
// ########### ********************************************************************************

void initializeLedControlTask(void ) {

  xTaskCreatePinnedToCore(ledControlTask, // Callback
                          "LedCtrlTask",  // Name of the task
                          700,            // Stack size
                          NULL,           // Parameters 
                          1,              // Priority
                          NULL,           // Handle
                          APP_CPU_NUM);   // CPU - core

}

// ########### *******************************************************************************
//
// Function   : ledControlTask
//
// Parameters : void
// Return     : void
//
// Description: Tarefa de controle do Led
//
// ########### ********************************************************************************

void ledControlTask(void *pvParameters) {

  while(1) {

    vTaskDelay( 250 / portTICK_PERIOD_MS );
    digitalWrite(GPIO_LED, !digitalRead(GPIO_LED));

  }
}