#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <csignal>  // Para manejar señales (Ctrl+C)
#include <unistd.h> // Para usleep
using namespace std;

#define SPI_CHANNEL 0 // Canal SPI 0
#define SPI_SPEED 1000000 // Velocidad SPI en Hz

bool running = true; // Bandera para detener el programa

// Manejador de señal para capturar Ctrl+C
void signalHandler(int signum) {
    cout << "\nDeteniendo la lectura del LDR..." << endl;
    running = false; // Cambiar la bandera para salir del bucle
}

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
    // Configurar el manejador de señal para Ctrl+C
    signal(SIGINT, signalHandler);

    // Inicializar WiringPi y SPI
    if (wiringPiSetup() == -1) {
        cerr << "Error al configurar WiringPi." << endl;
        return -1;
    }

    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        cerr << "Error al configurar el canal SPI." << endl;
        return -1;
    }

    cout << "Leyendo valores del LDR... (Presiona Ctrl+C para detener)" << endl;

    while (running) { // Bucle infinito hasta que se detenga manualmente
        int valor = readMCP3008(0); // Leer el canal 0
        if (valor != -1) {
            cout << "Valor LDR: " << valor << endl;
        }
        usleep(500000); // Esperar 500 ms (0.5 segundos)
    }

    cout << "Programa terminado." << endl;
    return 0;
}
