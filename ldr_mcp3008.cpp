#include <iostream>
#include <wiringPiSPI.h>
using namespace std;

#define SPI_CHANNEL 0 // Canal SPI 0
#define SPI_SPEED 1000000 // Velocidad SPI en Hz

// Leer del MCP3008
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

    cout << "Leyendo valores del LDR (Ctrl+C para salir):" << endl;

    while (true) {
        int ldrValue = readMCP3008(0); // Leer del canal 0
        cout << "Valor LDR: " << ldrValue << endl;
        delay(500); // Esperar 500 ms
    }

    return 0;
}
