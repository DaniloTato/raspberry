#include "../../include/iot.hpp"
#include "../functions.cpp"
#include "../../include/macros.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    // Contador de aciertos
    int score = 0;

    //Botones
    button1 = gpioRead(PIN_BUTTON_1);
    button2 = gpioRead(PIN_BUTTON_2);
    button3 = gpioRead(PIN_BUTTON_3);
    button4 = gpioRead(PIN_BUTTON_4);

    // Inicializar la ventana
    sf::RenderWindow window(sf::VideoMode(500, 300), "Color Selection Game");

    // Colores y teclas correspondientes
    sf::Color colors[] = {sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue};
    sf::Keyboard::Key keys[] = {sf::Keyboard::G, sf::Keyboard::R, sf::Keyboard::Y, sf::Keyboard::B};

    // Variables de estado
    int currentColorIndex = -1;
    bool colorVisible = false;
    sf::Clock clock; // Reloj para controlar el tiempo
    sf::Time colorDisplayTime = sf::seconds(0.5f); // Tiempo de espera antes de mostrar el siguiente color

    // Semilla para la generación aleatoria
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Procesar la entrada del teclado solo cuando ocurre un evento de KeyPressed
            if (event.type == sf::Event::KeyPressed && colorVisible) {
                for (int i = 0; i < 4; ++i) {
                    if (event.key.code == keys[i]) {
                        if (i == currentColorIndex) {
                            // Respuesta correcta
                            score++;
                            std::cout << "Puntaje actual: " << score << "\n";

                            colorVisible = false;   // Esconder el color actual
                            clock.restart();        // Reiniciar el reloj para el siguiente color
                        } else {
                            // Respuesta incorrecta
                            std::cout << "Respuesta incorrecta. Puntaje final: " << score << "\n";
                            return 0; // Terminar el juego
                        }
                        break; // Salir del bucle for una vez procesada la tecla
                    }
                }
            }
        }

        // Limpiar la ventana con blanco
        window.clear(sf::Color::White);

        // Mostrar un nuevo color si no está visible
        if (!colorVisible && clock.getElapsedTime() >= colorDisplayTime) {
            currentColorIndex = std::rand() % 4; // Seleccionar color aleatorio
            colorVisible = true;
            clock.restart();
        }

        // Mostrar el color en pantalla
        if (colorVisible) {
            window.clear(colors[currentColorIndex]);
        }

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
