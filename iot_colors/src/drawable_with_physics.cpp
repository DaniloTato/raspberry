#include "../include/iot.hpp"

drawable_with_physics::drawable_with_physics(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax, int first_frame_x):
drawable(x,y,texture,spritesheet_width,spritesheet_height,paralax,first_frame_x){}

void drawable_with_physics::pos_plus_spd(){
    _x += _spdx;
    _y += _spdy;

    _spdx *= 0.95;
    _spdy *= 0.95; 
}

void drawable_with_physics::gravity(float g){
    _spdy += g;
}