#include "../include/iot.hpp"

scrolling_text::scrolling_text(int x, int y, std::string texture, int speed):
_speed(speed), drawable(x,y,texture,0,0){}

void scrolling_text::draw(sf::RenderWindow &window){
    _x -= _speed;
    _my_sprite.setPosition(_x,_y);
    window.draw(_my_sprite);
}