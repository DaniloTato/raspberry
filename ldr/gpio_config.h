#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <wiringPi.h>

// GPIOs para LEDs controlados por el LDR
const int LED1 = 14;
const int LED2 = 15;
const int LED3 = 18;
const int LED4 = 23;

// Umbral para LDR
const int LDR_THRESHOLD = 700;

// Declaración de funciones
void configureGPIO();
void manejarLEDs(int valorLDR);

#endif
