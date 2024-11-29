#include "../include/iot.hpp"

scrolling_text::scrolling_text(int x, int y, std::string texture, int speed, float size):
_speed(speed), drawable(x,y,texture,0,0){
    _size = size;
}

void scrolling_text::draw(sf::RenderWindow &window){
    _x -= _speed;
    int sum_due_to_size_x = -(_SPRITESHEET_GRID_WIDTH)*(_size - 1);
    int sum_due_to_size_y = -(_SPRITESHEET_GRID_HEIGHT)*(_size - 1);
    _my_sprite.setPosition(_x + sum_due_to_size_x, _y + sum_due_to_size_y);
    _my_sprite.setScale(_size, _size);
    window.draw(_my_sprite);
}