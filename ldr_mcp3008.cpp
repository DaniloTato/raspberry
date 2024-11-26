#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h> // Para sleep

#define SPI_CHANNEL 0 // Canal SPI 0
#define SPI_SPEED 1000000 // Velocidad SPI en Hz

using namespace std;

// Función para leer del MCP3008
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

    cout << "Leyendo valores del LDR..." << endl;

    try {
        for (int i = 0; i < 10; ++i) { // Leer 10 veces
            int valor = readMCP3008(0); // Leer el canal 0
            cout << "Valor LDR: " << valor << endl;
            usleep(500000); // Esperar 500 ms
        }
    } catch (...) {
        cerr << "Error inesperado." << endl;
    }

    cout << "Programa terminado." << endl;
    return 0;
}
