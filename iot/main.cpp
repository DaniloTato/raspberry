#include "include/iot.hpp"
#include "include/macros.hpp"
#include "src/functions.cpp"
#include "src/drawable.cpp"
#include "src/cowboy_src/clouds.cpp"
#include "src/cowboy_src/cowboy.cpp"
#include "src/cowboy_src/flash_effect.cpp"
#include "src/scrolling_text.cpp"
#include "src/fps_counter.cpp"
#include "src/ui.cpp"
#include "src/lottery_src/animated_pointer.cpp"
#include "src/games/cowboy_game.cpp"
#include "src/games/lottery_game.cpp"
#include "src/lottery_src/card.cpp"
#include "src/drawable_with_physics.cpp"
#include "src/lottery_src/coin.cpp"

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
    {"blue", sf::Color(44,232,245)},
};

typedef bool (*function_ptr)(sf::RenderWindow&, sql::Connection*);

int main(){
    //mysql connection

    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    sql::Connection* conn = driver->connect("tcp://127.0.0.1:3306", "root", "");
    conn->setSchema("neurobox");

    //load arial font
    if (!font.loadFromFile("8-BIT WONDER.TTF")) {
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

    functions[0](window, conn);
    RESTART_GLOBAL_VARS();
    functions[1](window, conn);
    RESTART_GLOBAL_VARS();
    functions[0](window, conn);

    return 0;
}