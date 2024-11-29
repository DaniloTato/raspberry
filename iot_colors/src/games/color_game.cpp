#include "../../include/iot.hpp"
#include "../functions.cpp"
#include "../../include/macros.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

bool color_game(sf::RenderWindow& window, sql::Connection* conn, circle_transition& transition, sf::RectangleShape& fade) {

    // Colores disponibles
    sf::Color colors[] = {sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Yellow};

    sf::Event event;
    button1 = gpioRead(PIN_BUTTON_1);

    // Variables de estado
    int currentColorIndex = -1;
    bool colorVisible = false;
    int score = 0; // Contador de puntuación
    sf::Clock clock;
    sf::Time colorDisplayTime = sf::seconds(0.5f); // Tiempo para mostrar colores
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Semilla aleatoria
    int frames = 0;

    int game_id = insert_into_juego(conn, "Relación de colores.", "Colors", "Sin notas.");

    if (fade.getFillColor().a > 0) fade.setFillColor(sf::Color(0,0,0, fade.getFillColor().a - 8));

    // Bucle principal del juego
    while (window.isOpen()) {
        frames++;
	sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){

                if (event.key.code == sf::Keyboard::Escape){
                    return 1;
                }
            }
        }

        // Leer botones GPIO
        button1 = gpioRead(PIN_BUTTON_1); // Rojo
        button2 = gpioRead(PIN_BUTTON_2); // Verde
        button3 = gpioRead(PIN_BUTTON_3); // Azul
        button4 = gpioRead(PIN_BUTTON_4); // Amarillo

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
                transition.start_transition();
                insert_into_results(conn, score, game_id, "aciertos");
                insert_game_duration(conn, frames/57.0f, game_id);
                std::cout << "Respuesta incorrecta. Puntuación final: " << score << "\n";
                clock.restart();
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

        transition.draw(window);

        window.draw(fade);
        if(transition.ending()) return 1;

        window.display();
    }

    return 0;
}
