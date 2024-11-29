#include "../../include/iot.hpp"

void flash_effect::draw(sf::RenderWindow &window){
    _frames++;
    if(_frames < 7 || (_frames > 9 && _frames < 12) || (_frames > 15 && _frames < 18)){
        sf::RectangleShape rect(sf::Vector2f(resized_window_width,resized_window_height));
        window.draw(rect);
    }
}

int flash_effect::get_frames(){
    return _frames;
}