#include <iostream>
#include <wiringPiSPI.h>
#include "gpio_config.h"


using namespace std;

#define SPI_CHANNEL 0 // Canal SPI 0
#define SPI_SPEED 1000000 // Velocidad SPI en Hz

// Lecutra  del MCP3008
int readMCP3008(int channel) {
    if (channel < 0 || channel > 7) {
        cerr << "Canal inválido. Debe estar entre 0 y 7." << endl;
        return -1;
    }

    unsigned char buffer[3];
    buffer[0] = 1;                      // Inicio de la lectura
    buffer[1] = (8 + channel) << 4;     // Canal a leer
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3); // Comunicación SPI

    int resultado = ((buffer[1] & 3) << 8) + buffer[2]; // Combinar bits para obtener el valor
    return resultado;
}

void leds() {
    cout << "Leyendo valores del LDR (Ctrl C para terminar)" << endl;

    while (true) {

        // Leer el valor del LDR en el canal 0
        int ldrValue = readMCP3008(0);

        // Encender LEDs ssi estan por abajo del umbral (al momento 700)
        if (ldrValue < LDR_THRESHOLD) {
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);

        } else {
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
            digitalWrite(LED3, LOW);

        }

        cout << "Valor LDR: " << ldrValue << endl;
        delay(500); //Delay de 0.5s
    }
}

int main() {
    // Inicializar WiringPi y SPI
    if (wiringPiSetup() == -1) {
        cerr << "Error al configurar WiringPi." << endl;
        return -1;
    }

    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        cerr << "Error al configurar el canal SPI." << endl;
        return -1;
    }

    // Configurar GPIO
    configureGPIO();

    //Lógica para el encendido de los leds
    leds();

    return 0;
}
