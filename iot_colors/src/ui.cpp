#include "../include/iot.hpp"

ui::ui(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax, int first_frame_x):
drawable(x,y,texture,spritesheet_width,spritesheet_height,paralax,first_frame_x){}

void ui::update_position(){
    _my_sprite.setPosition(_x,_y);
}