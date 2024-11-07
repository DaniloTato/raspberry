#ifndef IOT
#define IOT

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>

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

extern bool pause;

class fps_counter;

extern fps_counter fpsc;
extern std::unordered_map<std::string, sf::Color> color_palette;
extern sf::Font font;

class drawable{
public:
    drawable(int x, int y, std::string texture, int spritesheet_width, int spritesheet_height, float paralax = 1, int first_frame_x = 0);
    virtual void draw(sf::RenderWindow &window);
    void update_position();
    void set_spritesheet_coords();
    void update_texture(std::string texture);
    int get_x();

    float _opacity = 255;
    int _x;
    int _y;
    float _paralax = 1;
    sf::Sprite _my_sprite;
    
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
    scrolling_text(int x, int y, std::string texture, int speed);
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


#endif