#include "include/iot.hpp"
#include "include/macros.hpp"
#include "src/functions.cpp"
#include "src/drawable.cpp"
#include "src/clouds.cpp"
#include "src/cowboy.cpp"
#include "src/flash_effect.cpp"
#include "src/scrolling_text.cpp"
#include "src/fps_counter.cpp"
#include "src/lottery_src/animated_pointer.cpp"
#include "src/games/cowboy_game.cpp"
#include "src/games/lottery_game.cpp"

int SCREEN_WIDTH = 480;
int SCREEN_HEIGHT = 240;
float camera_zoom = 1;
int camera_x = 0;
int camera_y = 0;

int go_to_camera_x = 0;
int go_to_camera_y = 0;
float go_to_camera_zoom = 1;

int resized_window_width = SCREEN_WIDTH;
int resized_window_height = SCREEN_HEIGHT;
float camera_speed = 0.1;
bool pause = 0;

sf::Clock sfclock;

sf::Font font;

//object to show frames per second of the project
fps_counter fpsc(10,10,font, &sfclock);

std::unordered_map<std::string, sf::Color> color_palette{
    {"purple", sf::Color(104,56,108)},
    {"black", sf::Color(24,20,37)},
};

typedef bool (*function_ptr)(sf::RenderWindow&);

int main(){
    //load arial font
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font\n";
        return 0;
    }

    function_ptr functions[2];

    functions[0] = cowboy_game;
    functions[1] = lottery_game;

    ///////sfml window stuff////////////
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "NEUROBOX");
    window.setFramerateLimit(60);

    int game_selection = 0;

    functions[1](window);
    RESTART_GLOBAL_VARS();
    functions[1](window);
    RESTART_GLOBAL_VARS();
    functions[0](window);

    return 0;
}