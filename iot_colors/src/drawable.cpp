#include "../include/iot.hpp"

drawable::drawable(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax, int first_frame_x):
_x(x), _y(y), _frame_x(first_frame_x), _SPRITESHEET_GRID_WIDTH(spritesheet_width), _SPRITESHEET_GRID_HEIGHT(spritesheet_height), _paralax(paralax){
    _spritesheet_coords.height = _SPRITESHEET_GRID_HEIGHT;
    update_texture(texture);
}

void drawable::update_position(){
    int x_with_diff = _x + _extra_x;
    int y_with_diff = _y + _extra_y;

    int sum_due_to_size_x = -(_SPRITESHEET_GRID_WIDTH - (_size_position_mode == 1)*_SPRITESHEET_GRID_WIDTH*0.5)*(_size - 1);
    int sum_due_to_size_y = -(_SPRITESHEET_GRID_HEIGHT - (_size_position_mode == 1)*_SPRITESHEET_GRID_HEIGHT*0.5)*(_size - 1);
    
    int sum_due_to_parallax_x = ((-2 + SCREEN_WIDTH * (-1 + _paralax)) / (2 * _paralax) + 1);
    int sum_due_to_parallax_y = ((-2 + SCREEN_HEIGHT * (-1 + _paralax)) / (2 * _paralax) + 1);

    int sum_due_to_zoom_x = (camera_zoom - 1)* (x_with_diff + sum_due_to_parallax_x);
    int sum_due_to_zoom_y = (camera_zoom - 1)* (y_with_diff + sum_due_to_parallax_y);

    _my_sprite.setPosition(x_with_diff - (camera_x/_paralax) + sum_due_to_zoom_x + sum_due_to_parallax_x + sum_due_to_size_x, 
                            y_with_diff - (camera_y / _paralax) + sum_due_to_zoom_y + sum_due_to_parallax_y + sum_due_to_size_y);
}

void drawable::update_texture(std::string texture){
    if (texture != "") _my_spritesheet.loadFromFile(texture);
    _my_sprite.setTexture(_my_spritesheet);
}

void drawable::update_texture(sf::Image img){
    _my_spritesheet.loadFromImage(img);
    _my_sprite.setTexture(_my_spritesheet);
}

void drawable::draw(sf::RenderWindow &window){
    animation_update();
    update_position();
    _my_sprite.setScale(camera_zoom * _size, camera_zoom * _size);
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

void drawable::animation_update(){
    _frame_count++;

    if (_animation_request < 0){
        if (_invert_animation) _frame_x = _animation_request - int(_frame_count/_animation_speed) % (-_animation_request), std::cout << _frame_x << "\n";
        else _frame_x = int(_frame_count/_animation_speed) % (-_animation_request);
    } else if(_animation_request){
        if (_invert_animation) _frame_x = _animation_request - (_frame_count/_animation_speed);
        else _frame_x = (_frame_count/_animation_speed);

        if((_frame_count/_animation_speed) >= _animation_request) _animation_request = 0, _frame_x = 0, _frame_count = 0;
    }

}

void drawable::animate(int number_of_frames, int frame_y, float animation_speed, bool invert){
    _animation_request = number_of_frames;
    _frame_y = frame_y;
    _frame_x = 0;
    _frame_count = 0;
    _animation_speed = animation_speed;
    _invert_animation = invert;
}

void drawable::loop_animate(int number_of_frames, int frame_y, float animation_speed){
    if(!_animation_request){
        _animation_request = -number_of_frames;
        _frame_y = frame_y;
        _frame_x = 0;
        _frame_count = 0;
        _animation_speed = animation_speed;
    }
}

void drawable::end_loop_animate(){
    _animation_request = 0;
    _frame_x = 0;
    _frame_count = 0;
}

int drawable::get_frame_x(){
    return _frame_x;
}
