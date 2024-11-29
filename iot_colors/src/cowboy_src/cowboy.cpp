#include "../../include/iot.hpp"

cowboy::cowboy(int x, int y, int direction):
drawable(x,y,"textures/player.png",61,41){
    _direction = direction;
}

void cowboy::animation(){
    if(_last_frame_state != _state) _frame_count = 0, _last_frame_x = 0;

    if(_state == "idle"){
        _frame_x = int(_frame_count/40) % 2;
        _frame_y = 0;

    } else if(_state == "won"){
        _frame_x = int(_frame_count/2);
        _frame_y = 3;

        if(_frame_x > 4) _frame_x = 4;

        if(_frame_count > 100) _state = "dancing";

    } else if(_state == "dancing"){
        _frame_x = int(_frame_count/10) % 4;
        _frame_y = 2;

        if(_frame_count > 200) _state = "idle";

    } else if(_state == "lost"){
        _frame_x = 0;
        _frame_y = 1;
    }

    _last_frame_state = _state;
    _last_frame_x = _frame_x;
}