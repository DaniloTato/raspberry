#include <wiringPi.h>
#include "gpio_config.h"

void configureGPIO() {
    // Inputs (Botones)
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);

    // Outputs (LEDs controlados por el LDR)
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // Outputs (LEDs de inicio y fin de juego)
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);

    // Outputs (Buzzer)
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
