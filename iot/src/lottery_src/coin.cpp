#include "../../include/iot.hpp"

coin::coin(int x, int y, int my_floor, int linked_space):
_linked_space(linked_space), _my_floor(my_floor), drawable_with_physics(x,y,"textures/lottery/coin.png",15,16,1,0){}

void coin::draw(sf::RenderWindow& window){
    gravity(0.4);
    pos_plus_spd();

    if(_y > _my_floor){
        _y -= _y - _my_floor;
        if(_spdy > 1.5) _spdy = -abs(_spdy);
        else _spdy = 0;
    }

    drawable::draw(window);
}

int coin::get_linked_space(){
    return _linked_space;
}
