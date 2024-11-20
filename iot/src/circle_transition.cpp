#include "../include/iot.hpp"

circle_transition::circle_transition(){
    _circle.setFillColor(sf::Color::White);
    _circle.setPosition(resized_window_width*0.5, resized_window_height*0.5);
}

void circle_transition::start_transition(){
    _on = true;
}

void circle_transition::draw(sf::RenderWindow& window){
    if(_on){
        _radius += 8;
        _circle.setRadius(_radius);
        _circle.setOrigin(_radius, _radius);
        window.draw(_circle);
    }
}

bool circle_transition::ending(){
    bool screen_covered = _radius > std::sqrt((resized_window_width * resized_window_width) + (resized_window_height * resized_window_height))*0.5;
    if(screen_covered) _on = false, _radius = 1;
    return screen_covered;
}