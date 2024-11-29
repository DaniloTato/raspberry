#include "../../include/iot.hpp"
#include "../functions.cpp"

card::card(int x, int y, int face, float paralax):
_face(face), ui(x,y,"textures/lottery/card.png",45,93,paralax,0){
    sf::Image img;
    img.loadFromFile("textures/lottery/icons.png");

    sf::Image cropped = crop_image(img,face*32,0,32,32);
    sf::Image bordered = add_border(cropped, 1);

    _symbol = new ui(0,0,"textures/lottery/icons.png", 32, 32);
    _symbol -> update_texture(bordered);

    _spdx = -9.5;
}

card::~card(){
    delete _symbol;
}

void card::card_exit(){
    _going_out = 1;
}

void card::pos_plus_spd(){
    _x += _spdx;
    _y += _spdy;

    _spdx *= 0.95;
    _spdy *= 0.95; 
}

void card::draw(sf::RenderWindow& window){

    if(_going_out) _spdx -= 0.8;

    pos_plus_spd();

    drawable::draw(window);
    _symbol -> _x = _x + 13;
    _symbol -> _y = _y + 90;
    _symbol -> draw(window);
}

int card::get_symbol_costume(){
    return _face;
}