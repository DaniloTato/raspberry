#include "../../include/iot.hpp"

animated_pointer::animated_pointer(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, int animation_frames, float paralax, int first_frame_x):
_ANIMATION_FRAMES(animation_frames), _go_to_x(x), _go_to_y(y), drawable(x,y,texture,spritesheet_width,spritesheet_height,paralax,first_frame_x){}

void animated_pointer::draw(sf::RenderWindow& window){

    _x += (_go_to_x - _x) * go_to_speed;
    _y += (_go_to_y - _y) * go_to_speed;

    animation_update();
    if(_frame_count == 60) animate(_ANIMATION_FRAMES, 0);
    drawable::draw(window);
}