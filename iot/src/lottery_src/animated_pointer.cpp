#include "../../include/iot.hpp"

animated_pointer::animated_pointer(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, int animation_frames, float paralax, int first_frame_x):
_ANIMATION_FRAMES(animation_frames), _go_to_x(x), _go_to_y(y), drawable(x,y,texture,spritesheet_width,spritesheet_height,paralax,first_frame_x){}

void animated_pointer::draw(sf::RenderWindow& window){

    _x += (_go_to_x - _x) * _GO_TO_SPEED;
    _y += (_go_to_y - _y) * _GO_TO_SPEED;
    
    _shake_factor = _shake_magnitude * (rand() % 2 - 1);
    _shake_magnitude *= 0.9;
    if(_shake_magnitude < 0.5) _shake_factor = 0, _shake_magnitude = 0;


    if(_frame_count == 60) animate(_ANIMATION_FRAMES, 0);
    drawable::draw(window);
}

void animated_pointer::shake_it(float magnitude){
    _shake_magnitude = magnitude;
}

void animated_pointer::update_position(){
    int x_with_diff = _x + _shake_factor;
    int y_with_diff = _y;

    int sum_due_to_size_x = -(_SPRITESHEET_GRID_WIDTH)*(_size - 1);
    int sum_due_to_size_y = -(_SPRITESHEET_GRID_HEIGHT)*(_size - 1);
    
    int sum_due_to_parallax_x = ((-2 + SCREEN_WIDTH * (-1 + _paralax)) / (2 * _paralax) + 1);
    int sum_due_to_parallax_y = ((-2 + SCREEN_HEIGHT * (-1 + _paralax)) / (2 * _paralax) + 1);

    int sum_due_to_zoom_x = (camera_zoom - 1)* (x_with_diff + sum_due_to_parallax_x);
    int sum_due_to_zoom_y = (camera_zoom - 1)* (y_with_diff + sum_due_to_parallax_y);

    _my_sprite.setPosition(x_with_diff - (camera_x/_paralax) + sum_due_to_zoom_x + sum_due_to_parallax_x + sum_due_to_size_x, 
                            y_with_diff - (camera_y / _paralax) + sum_due_to_zoom_y + sum_due_to_parallax_y + sum_due_to_size_y);
}