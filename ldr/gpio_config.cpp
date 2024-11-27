#include "gpio_config.h"

// Configurar los GPIOs
void configureGPIO() {
    // Configuración de LEDs como salida
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // Inicializar LEDs apagados
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
}

// Controlar los LEDs según el valor del LDR
void manejarLEDs(int valorLDR) {
    if (valorLDR < LDR_THRESHOLD) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
    } else {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
    }
}
