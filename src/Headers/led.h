// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : led.h
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#ifndef _LED_H
#define _LED_H

// ----------------------------------------------------------------------------------------- //

#include <Arduino.h>

// ----------------------------------------------------------------------------------------- //

#define GPIO_LED        2

// ----------------------------------------------------------------------------------------- //

void initializeLed(void );
void initializeGPIOLed(void );
void initializeLedControlTask(void );
void ledControlTask(void *pvParameters);

// ----------------------------------------------------------------------------------------- //

#endif

// ----------------------------------------------------------------------------------------- //
