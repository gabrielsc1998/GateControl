// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : feedbackGate.cpp
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/serial.h"
#include "Headers/feedbackGate.h"

// ----------------------------------------------------------------------------------------- //

static boolean _feedbackGate = GATE_CLOSED;

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

void initializeFeedbackGate(void ) {

  initializeGPIOFeedbackGate();
  initializeFeedbackGateTask();

}

// ########### ********************************************************************************
//
// Function   : initializeGPIOFeedbackGate
//
// Parameters : void
// Return     : void
//
// Description: 
//
// ########### ********************************************************************************

void initializeGPIOFeedbackGate(void ) {

  pinMode(GPIO_FEEDBACK_GATE, INPUT);

}

// ########### *******************************************************************************
//
// Function   : initializeFeedbackGateTask
//
// Parameters : void
// Return     : void
//
// Description: Inicializa a tarefa de feedback do portão
//
// ########### ********************************************************************************

void initializeFeedbackGateTask(void ) {

  xTaskCreatePinnedToCore(feedbackGateTask, // Callback
                          "FdbGateTask",    // Name of the task
                          2000,             // Stack size
                          NULL,             // Parameters 
                          1,                // Priority
                          NULL,             // Handle
                          APP_CPU_NUM);     // CPU - core

}

// ########### *******************************************************************************
//
// Function   : feedbackGateTask
//
// Parameters : void
// Return     : void
//
// Description: Tarefa de feedback do portão
//
// ########### ********************************************************************************

void feedbackGateTask(void *pvParameters) {

  while(1) {

    vTaskDelay( 750 / portTICK_PERIOD_MS );
    
    if(digitalRead(GPIO_FEEDBACK_GATE) == LOW) {
      _feedbackGate = GATE_CLOSED;
    } else {
      _feedbackGate = GATE_OPENING_CLOSING_STOPED;
    }

  }
}

// ########### *******************************************************************************
//
// Function   : getFeedbackGate
//
// Parameters : void
// Return     : void
//
// Description: Extrai o feedback do portão
//
// ########### ********************************************************************************

uint8_t getFeedbackGate(void) {

  return _feedbackGate;

}