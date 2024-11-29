#include "../../include/iot.hpp"

clouds::clouds(double x, double y, float paralax, int opacity):
drawable(x, y, "", 656, 288, paralax){
    for (int i = 0; i < 4; i++){
        _cloud_parts[i] = new drawable(x,y,"textures/clouds_" + std::to_string(4 - i) + ".png", 656, 288, _paralax + (i+1)*0.4);
        _cloud_parts[i] -> _opacity = opacity;
    }
}

void clouds::draw(sf::RenderWindow& window){
    _frames_alive++;

    for (auto i: _cloud_parts){
        i -> _x = _x;
        i -> _y = _y + sinf((float)_frames_alive/60) * (30/ i -> _paralax);
        i -> draw(window);
    }
}