#ifndef MACROS_H
#define MACROS_H

#define INITIALIZE_GAME_OBJECTS()   \
    sf::Text game_over;\
    game_over.setFont(font);\
    game_over.setCharacterSize(25);\
    game_over.setFillColor(sf::Color::White);\
    game_over.setString("Fin del Juego...");\
    \
    sf::Text disqualified;\
    disqualified.setFont(font);\
    disqualified.setCharacterSize(25);\
    disqualified.setFillColor(sf::Color::White);\
    disqualified.setString("Descalificado...");\
    \
    std::vector<flash_effect*> flash_vector;\
    std::vector<scrolling_text*> scrolling_text_vector;\
    bool show_fuego = 0;\
    int time_until_fire = 300;\
    int game_state = 0;\
    bool pause = 0;\
    int difficulty = 5; /*the lower the number, the higher the difficulty. Must be highr than 1 */ \
    int tolerance = 60;\
    int min_tolerance = 3;\
    float frames_passed = 0;\
    drawable sand(-55,100, "textures/scenario.png", 586, 104);\
    drawable sun(-50,-50, "textures/sun.png", 90, 76, 100);\
    drawable fuego((SCREEN_WIDTH - 80)*0.5,80, "textures/fuego.png", 80, 46);\
    clouds cld(-300,-130,10,60);\
    cowboy player(130,120,1);\
    cowboy enemy(280,120,-1);\
    sf::RectangleShape bar1(sf::Vector2f(SCREEN_WIDTH, 30));\
    sf::RectangleShape bar2(sf::Vector2f(SCREEN_WIDTH, 30));\
    bar1.setFillColor(color_palette["black"]);\
    bar2.setFillColor(color_palette["black"]);\

    #define RESTART_GLOBAL_VARS()  \
    SCREEN_WIDTH = 480;\
    SCREEN_HEIGHT = 240;\
    camera_zoom = 1;\
    camera_x = 0;\
    camera_y = 0;\
    go_to_camera_x = camera_x;\
    go_to_camera_y = camera_y;\
    go_to_camera_zoom = camera_zoom;\
    pause = 0;\

    #define CAMERA_POSITION_UPDATE()\
    camera_x += (go_to_camera_x - camera_x) * camera_speed;\
    camera_y += (go_to_camera_y - camera_y) * camera_speed;\
    camera_zoom += (go_to_camera_zoom - camera_zoom) * 0.1;\

#endif