// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : timer.h
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#include "Headers/timer.h"

// ----------------------------------------------------------------------------------------- //

static unsigned long initialTime[QTD_TIMERS] = {0};
static unsigned long currentTime[QTD_TIMERS] = {0};

boolean timer[QTD_TIMERS] = {false};

// ----------------------------------------------------------------------------------------- //

// ########### ********************************************************************************
//
// Function   : startTimers
//
// Parameters : void
// Return     : void 
//
// Description: Inicializa os temporizadores
//
// ########### ********************************************************************************

void startTimers(void ) {

    initialTime[0] = millis();
    for(register uint8_t i = 0; i < QTD_TIMERS; i++) {
        initialTime[i + 1] = initialTime[i];
    }
}

// ########### ********************************************************************************
//
// Function   : loopTimers
//
// Parameters : void
// Return     : void 
//
// Description: Loop dos temporizadores
//
// ########### ********************************************************************************

void loopTimers(void ) {
    
    for(register uint8_t i = 0; i < QTD_TIMERS; i++) {
        timer[i] = false;
    }
    
    unsigned long auxMillis = millis();
        
    currentTime[_15_sec] = auxMillis;
    if(currentTime[_15_sec] - initialTime[_15_sec] >= sec2ms(15)) {
        timer[_15_sec] = true;
        initialTime[_15_sec] = currentTime[_15_sec];
    }

    currentTime[_15_min] = auxMillis;
    if(currentTime[_15_min] - initialTime[_15_min] >= min2ms(15)) {
        timer[_15_min] = true;
        initialTime[_15_min] = currentTime[_15_min];
    }
}
