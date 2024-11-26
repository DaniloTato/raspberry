#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <wiringPi.h>

// GPIOs para botones
const int BUTTON1 = 5;
const int BUTTON2 = 6;
const int BUTTON3 = 13;
const int BUTTON4 = 19;


// GPIOs para LEDs
const int LED1 = 14;
const int LED2 = 15;
const int LED3 = 18;
const int LED4 = 23;

//GPIOs para LEDs de inicio y fin de juego
const int LED5 = 17;
const int LED6 = 27;

// GPIOs para buzzer
const int BUZZER1 = 24;


// Umbral para LDR
const int LDR_THRESHOLD = 700;

inline void configureGPIO() {
    // Inputs (Botones)
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);

    // Outputs (LEDs y Buzzer)
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
    pinMode(BUZZER1, OUTPUT);

    // Inicialización de LEDs y buzzer apagados
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(BUZZER1, LOW);
}

void leds();

#endif
  