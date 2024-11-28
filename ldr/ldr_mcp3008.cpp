#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <csignal>  
#include <unistd.h>  

using namespace std;

#define SPI_CHANNEL 0  
#define SPI_SPEED 1000000  

// GPIOs para LEDs
const int LED1 = 15;
const int LED2 = 16;
const int LED3 = 4;
const int LED4 = 5;

// Umbral para LDR
const int LDR_THRESHOLD = 700;

bool running = true;

void signalHandler(int signum) {
    cout << "\nDeteniendo la lectura del LDR" << endl;
    running = false; 
}

// Configurar GPIOs
void configureGPIO() {
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

// Función para leer el ADC MCP3008
int readMCP3008(int channel) {
    if (channel < 0 || channel > 7) {
        cerr << "Canal inválido. Debe estar entre 0 y 7." << endl;
        return -1;
    }

    unsigned char buffer[3];
    buffer[0] = 1;                      // Inicio de la lectura
    buffer[1] = (8 + channel) << 4;     // Canal a leer
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);  // Comunicación SPI

    int resultado = ((buffer[1] & 3) << 8) + buffer[2];  // Combinar bits para obtener el valor
    return resultado;
}

int main() {

    signal(SIGINT, signalHandler);
    if (wiringPiSetup() == -1) {
        cerr << "Error al configurar WiringPi." << endl;
        return -1;
    }

    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        cerr << "Error al configurar el canal SPI." << endl;
        return -1;
    }

    // Configurar GPIOs
    configureGPIO();

    cout << "Leyendo valores del LDR... (Presiona Ctrl+C para detener)" << endl;

    while (running) {  
        int valor = readMCP3008(0);  
        if (valor != -1) {
            cout << "Valor LDR: " << valor << endl;

            // Encendido de LEDs según el valor del LDR
            manejarLEDs(valor);
        }
        usleep(500000); 
    }

    cout << "Programa terminado." << endl;
    return 0;
}
