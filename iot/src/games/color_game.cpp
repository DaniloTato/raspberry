#include "../../include/iot.hpp"
#include "../functions.cpp"
#include "../../include/macros.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    // Inicializar ventana
    sf::RenderWindow window(sf::VideoMode(500, 300), "Juego de Selección de Colores con GPIO");

    // Colores disponibles
    sf::Color colors[] = {sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Yellow};

    // Variables de estado
    int currentColorIndex = -1;
    bool colorVisible = false;
    int score = 0; // Contador de puntuación
    sf::Clock clock;
    sf::Time colorDisplayTime = sf::seconds(0.5f); // Tiempo para mostrar colores
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Semilla aleatoria

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Leer botones GPIO
        int button1 = gpioRead(PIN_BUTTON_1); // Rojo
        int button2 = gpioRead(PIN_BUTTON_2); // Verde
        int button3 = gpioRead(PIN_BUTTON_3); // Azul
        int button4 = gpioRead(PIN_BUTTON_4); // Amarillo

        // Lógica del juego
        if (colorVisible) {
            if (button1 && currentColorIndex == 1) { // Botón rojo
                std::cout << "¡Correcto! Puntuación: " << ++score << "\n";
                colorVisible = false;
                clock.restart();
            } else if (button2 && currentColorIndex == 0) { // Botón verde
                std::cout << "¡Correcto! Puntuación: " << ++score << "\n";
                colorVisible = false;
                clock.restart();
            } else if (button3 && currentColorIndex == 2) { // Botón azul
                std::cout << "¡Correcto! Puntuación: " << ++score << "\n";
                colorVisible = false;
                clock.restart();
            } else if (button4 && currentColorIndex == 3) { // Botón amarillo
                std::cout << "¡Correcto! Puntuación: " << ++score << "\n";
                colorVisible = false;
                clock.restart();
            } else if (button1 || button2 || button3 || button4) { // Respuesta incorrecta
                std::cout << "Respuesta incorrecta. Puntuación final: " << score << "\n";
                return 0;
            }
        }

        // Mostrar un nuevo color si no hay uno visible
        if (!colorVisible && clock.getElapsedTime() >= colorDisplayTime) {
            currentColorIndex = std::rand() % 4; // Seleccionar color aleatorio
            colorVisible = true;
            clock.restart();
        }

        // Actualizar ventana
        window.clear(colorVisible ? colors[currentColorIndex] : sf::Color::White);
        window.display();
    }

    return 0;
}
