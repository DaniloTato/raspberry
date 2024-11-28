#ifndef IOT
#define IOT

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>

#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <stdexcept>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>

#include <mosquitto.h>


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float camera_zoom;
extern int camera_x;
extern int camera_y;
extern int resized_window_width;
extern int resized_window_height;

extern float go_to_camera_zoom;

extern int go_to_camera_x;
extern int go_to_camera_y;
extern float camera_speed;

extern bool paused;

extern int patient_id;
extern int specialist_id;

extern bool button1;
extern bool button2;
extern bool button3;
extern bool button4;

class fps_counter;

extern fps_counter fpsc;
extern std::unordered_map<std::string, sf::Color> color_palette;
extern sf::Font font;

class drawable{
public:
    drawable(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax = 1, int first_frame_x = 0);
    virtual void draw(sf::RenderWindow &window);
    virtual void update_position();
    void set_spritesheet_coords();
    void update_texture(std::string texture);
    void update_texture(sf::Image img);
    int get_x();
    void animation_update();
    void animate(int number_of_frames, int frame_y, float animation_speed = 7, bool invert = 0);
    void loop_animate(int number_of_frames, int frame_y, float animation_speed = 7);
    void end_loop_animate();
    int get_frame_x();

    float _opacity = 255;
    double _x;
    double _y;
    double _extra_x = 0;
    double _extra_y = 0;
    float _paralax = 1;
    sf::Sprite _my_sprite;
    int _animation_request = 0;
    float _size = 1;
    float _animation_speed = 7;
    bool _invert_animation = 0;
    int _size_position_mode = 0;
    
protected:
    int _direction = 1;
    sf::Texture _my_spritesheet;
    sf::IntRect _spritesheet_coords;
    int _r = 255; 
    int _g = 255;
    int _b = 255;
    int _frame_x;
    int _frame_y = 0;
    unsigned int _frame_count = 0;
    int _SPRITESHEET_GRID_WIDTH;
    int _SPRITESHEET_GRID_HEIGHT;
};

class ui: public drawable{
public:
    ui(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax = 1, int first_frame_x = 0);
    virtual void update_position();
};

class clouds: public drawable{
public:
    clouds(double x, double y, float paralax, int opacity);
    void draw(sf::RenderWindow& window) override;

protected:
    drawable* _cloud_parts[4];
    long _frames_alive = 0;
};

class cowboy: public drawable{
public:
    cowboy(int x, int y, int direction);
    void animation();
    std::string _state = "idle";
    std::string _last_frame_state = "idle";
protected:
    int _last_frame_x;
};

class flash_effect{
public:
    void draw(sf::RenderWindow &window);
    int get_frames();
protected:
    int _frames = 0;
};

class scrolling_text: public drawable{
public:
    scrolling_text(int x, int y, std::string texture, int speed, float size = 1);
    void draw(sf::RenderWindow &window) override;
protected:
    int _speed;

};

class fps_counter{
public:
    fps_counter(int x, int y, sf::Font& font, sf::Clock* clock);
    void calculate_fps();
    void draw(sf::RenderWindow& window);
protected:
    sf::Clock* _clock;
    sf::Text _fpsText;
    float _last_time = 0;
    int _frame_count = 0;
    float _fps = 0;
};


///LOTTERY

class animated_pointer: public drawable{
public:
    animated_pointer(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, int animation_frames, float paralax = 1, int first_frame_x = 0);
    void draw(sf::RenderWindow& window) override;
    void update_position() override;
    void shake_it(float magnitude);
    int _go_to_x;
    int _go_to_y;
    float _shake_magnitude = 0;
protected:
    const int _ANIMATION_FRAMES;
    float _GO_TO_SPEED = 0.2;
    float _shake_factor = 0;
};

class physics_object{
public:
    virtual void pos_plus_spd() = 0;
    virtual void gravity(float g) = 0;
    double _spdx = 0;
    double _spdy = 0;
};

class drawable_with_physics: public drawable, public physics_object{
public:
    drawable_with_physics(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax = 1, int first_frame_x = 0);
    void pos_plus_spd() override;
    void gravity(float g) override;
};

class coin: public drawable_with_physics{
public:
    coin(int x, int y, int my_floor, int linked_space);
    void draw(sf::RenderWindow& window) override;
    int get_linked_space();
protected:
    int _my_floor;
    int _linked_space;

};

class card: public ui, public physics_object{
public:
    card(int x, int y, int face, float paralax = 1);
    void draw(sf::RenderWindow& window) override;
    void card_exit();
    void pos_plus_spd() override;
    void gravity(float g) override{}
    ~card();
    int get_symbol_costume();
private:
    ui* _symbol;
    bool _going_out = 0;
    int _face;
};

class circle_transition{
public:
    circle_transition();
    void start_transition();
    void draw(sf::RenderWindow& window);
    bool ending();
private:
    float _radius = 1;
    sf::CircleShape _circle;
    bool _on = 0;
};

class input_manager{
public:
    void assign_button(std::string identifier, bool* control_variable){
        inputs[identifier] = std::make_pair(control_variable, false);
    }

    bool is_button_pressed(std::string button){
        bool res = false;
        if(inputs.find(button) != inputs.end()){
            res = *(inputs[button].first) == true && *(inputs[button].first) != inputs[button].second;
        }
        inputs[button].second = *(inputs[button].first);
        return res;
    }

private:
    std::unordered_map<std::string, std::pair<bool*, bool>> inputs;
};

extern input_manager input_m;

#endif