#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <wiringPi.h>

// GPIO para botones
const int BUTTON1 = 5;
const int BUTTON2 = 6;
const int BUTTON3 = 13;
const int BUTTON4 = 19;

// GPIO para LEDs
const int LED1 = 14;
const int LED2 = 15;
const int LED3 = 18;

// Umbral para LDR
const int LDR_THRESHOLD = 700;

inline void configureGPIO() {
    // Inputs (Botones)
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);

    // Outputs (LEDs)
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    //Inicialización de LEDs
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
}

void leds();

#endif
