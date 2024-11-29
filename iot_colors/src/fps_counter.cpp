#include "../include/iot.hpp"

fps_counter::fps_counter(int x, int y, sf::Font& font, sf::Clock* clock):
_clock(clock){
    _fpsText.setFont(font);
    _fpsText.setCharacterSize(10);
    _fpsText.setFillColor(sf::Color::White);
    _fpsText.setPosition(x, y);
}

void fps_counter::calculate_fps(){
    float currentTime = _clock -> getElapsedTime().asSeconds();
    _frame_count++;

    if (currentTime - _last_time >= 1.0f) {
        _fps = _frame_count / (currentTime - _last_time);

        _last_time = currentTime;
        _frame_count = 0;
    }

    _fpsText.setString("FPS " + std::to_string(static_cast<int>(_fps)));
}

void fps_counter::draw(sf::RenderWindow& window){
    window.draw(_fpsText);
}