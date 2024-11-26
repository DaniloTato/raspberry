#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <wiringPi.h>

// GPIOs para botones
const int BUTTON1 = 5;
const int BUTTON2 = 6;
const int BUTTON3 = 13;
const int BUTTON4 = 19;

// GPIOs para LEDs controlados por el LDR
const int LED1 = 14;
const int LED2 = 15;
const int LED3 = 18;
const int LED4 = 23;

// GPIOs para LEDs de inicio y fin de juego
const int LED5 = 17;
const int LED6 = 27;

// GPIOs para buzzer
const int BUZZER1 = 24;

// Umbral para LDR
const int LDR_THRESHOLD = 700;

// Declaración de la función para configurar GPIO
void configureGPIO();

// Declaración de la función para manejar los LEDs
void leds();

#endif
