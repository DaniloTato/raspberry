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
#include "src/games/end_game_screen.cpp"
#include "src/games/selection_screen.cpp"
#include "src/lottery_src/card.cpp"
#include "src/drawable_with_physics.cpp"
#include "src/lottery_src/coin.cpp"
#include "src/circle_transition.cpp"

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
bool paused = 0;

int patient_id = 1001;
int specialist_id = 2002;

int game_selection = -1;

sf::Clock sfclock;

sf::Font font;

//object to show frames per second of the project
fps_counter fpsc(10,10,font, &sfclock);

std::unordered_map<std::string, sf::Color> color_palette{
    {"purple", sf::Color(104,56,108)},
    {"black", sf::Color(24,20,37)},
    {"blue", sf::Color(44,232,245)},
};

//Mosquitto get message
void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    std::cout << message->topic << " with message: " << (char*)message->payload << std::endl;

    std::string payload_str((char*)message->payload, message->payloadlen);

    if(payload_str == "green_on"){
        game_selection = 0;
    } else if (payload_str == "green_off"){
        game_selection = 1;
    }
}

typedef bool (*function_ptr)(sf::RenderWindow&, sql::Connection*, circle_transition&);

int main(){

    //mysql connection

        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* conn = driver->connect("tcp://127.0.0.1:3306", "root", "");
        conn->setSchema("neurobox");

    //end to musql connection

    //add patient to database if it isnt registered yet
    add_patient_id(conn, patient_id);

    //-----------------------------------------------------------------------------------

    //mqtt connection

        //credentials can be found on include/macros.hpp
        mosquitto_lib_init();
        struct mosquitto *mosq = mosquitto_new(CLIENT_ID, true, nullptr);
        if (!mosq) {
            std::cerr << "Failed to create Mosquitto client" << std::endl;
            return -1;
        }
        //link the function created above to be excecuted once a message is received.
        mosquitto_message_callback_set(mosq, message_callback);

        if (mosquitto_connect(mosq, BROKER_ADDRESS, BROKER_PORT, 60) != MOSQ_ERR_SUCCESS) {
            std::cerr << "Failed to connect to broker: " << BROKER_ADDRESS << std::endl;
            return -1;
        }
        std::cout << "Connected to broker " << BROKER_ADDRESS << std::endl;

        //subscribe to topic
        if (mosquitto_subscribe(mosq, nullptr, TOPIC, 0) != MOSQ_ERR_SUCCESS) {
            std::cerr << "Failed to subscribe to topic: " << TOPIC << std::endl;
            return -1;
        }
        std::cout << "Mosquitto is successfully listening to topic : " << TOPIC << std::endl;

        mosquitto_loop_start(mosq);
        
    //mqtt connection

    //-----------------------------------------------------------------------------------

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

    circle_transition transition;

    while(true){
        if(!selection_screen(window, game_selection)) break;
        RESTART_GLOBAL_VARS();
        if(!functions[game_selection](window, conn, transition)) break;
        RESTART_GLOBAL_VARS();
        if(!end_game_screen(window)) break;
        RESTART_GLOBAL_VARS();
    }

    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    std::cout << "good_bye" << "\n";

    return 0;
}