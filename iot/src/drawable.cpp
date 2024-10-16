#include "../include/iot.hpp"

drawable::drawable(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax):
_x(x), _y(y), _SPRITESHEET_GRID_WIDTH(spritesheet_width), _SPRITESHEET_GRID_HEIGHT(spritesheet_height), _paralax(paralax){
    _spritesheet_coords.height = _SPRITESHEET_GRID_HEIGHT;
    update_texture(texture);
}

void drawable::update_position(){
    int x_with_diff = _x;
    int y_with_diff = _y;
    
    int sum_due_to_parallax_x = ((-2 + SCREEN_WIDTH * (-1 + _paralax)) / (2 * _paralax) + 1);
    int sum_due_to_parallax_y = ((-2 + SCREEN_HEIGHT * (-1 + _paralax)) / (2 * _paralax) + 1);

    int sum_due_to_zoom_x = (camera_zoom - 1)* (x_with_diff + sum_due_to_parallax_x);
    int sum_due_to_zoom_y = (camera_zoom - 1)* (y_with_diff + sum_due_to_parallax_y);

    _my_sprite.setPosition(x_with_diff - (camera_x/_paralax) + sum_due_to_zoom_x + sum_due_to_parallax_x, 
                            y_with_diff - (camera_y / _paralax) + sum_due_to_zoom_y + sum_due_to_parallax_y);
}

void drawable::update_texture(std::string texture){
    if (texture != "") _my_spritesheet.loadFromFile(texture);
    _my_sprite.setTexture(_my_spritesheet);
}

void drawable::draw(sf::RenderWindow &window){
    update_position();
    _my_sprite.setScale(camera_zoom, camera_zoom);
    _my_sprite.setColor(sf::Color(_r,_g,_b, _opacity));

    set_spritesheet_coords();
    _my_sprite.setTextureRect(_spritesheet_coords);
    window.draw(_my_sprite);
}

void drawable::set_spritesheet_coords(){
    _spritesheet_coords.left = _frame_x * _SPRITESHEET_GRID_WIDTH + _SPRITESHEET_GRID_WIDTH * ((_direction - 1)/-2);
    _spritesheet_coords.width = _SPRITESHEET_GRID_WIDTH * _direction;
    _spritesheet_coords.top = _frame_y * _SPRITESHEET_GRID_HEIGHT;
}

int drawable::get_x(){
    return _x;
}
