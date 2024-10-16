#include "include/iot.hpp"
#include "src/functions.cpp"
#include "src/drawable.cpp"
#include "src/clouds.cpp"
#include "src/cowboy.cpp"
#include "src/flash_effect.cpp"
#include "src/scrolling_text.cpp"

int SCREEN_WIDTH = 480;
int SCREEN_HEIGHT = 240;
float camera_zoom = 1;
int camera_x = 0;
int camera_y = -25;
int resized_window_width = SCREEN_WIDTH;
int resized_window_height = SCREEN_HEIGHT;

int go_to_camera_x = camera_x;
int go_to_camera_y = camera_y;
float go_to_camera_zoom = camera_zoom;
float camera_speed = 0.1;

int main()
{

    std::unordered_map<std::string, sf::Color> color_palette{
        {"purple", sf::Color(104,56,108)},
        {"black", sf::Color(24,20,37)},
    };

    ///////sfml window stuff////////////

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Typing RPG");
    window.setFramerateLimit(60);

    sf::Color background_color = color_palette["purple"];

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font\n";
        return -1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);
    sf::Clock clock;

    sf::Text game_over;
    game_over.setFont(font);
    game_over.setCharacterSize(25);
    game_over.setFillColor(sf::Color::White);
    game_over.setString("Fin del Juego...");

    sf::Text disqualified;
    disqualified.setFont(font);
    disqualified.setCharacterSize(25);
    disqualified.setFillColor(sf::Color::White);
    disqualified.setString("Descalificado...");

    float lastTime = 0;
    int frameCount = 0;
    float fps = 0;

    ////////////////////////////////////////////// object creation

    std::vector<flash_effect*> flash_vector;
    std::vector<scrolling_text*> scrolling_text_vector;

    bool show_fuego = 0;
    int time_until_fire = 300;
    int game_state = 0;
    bool pause = 0;

    int difficulty = 5; //the lower the number, the higher the difficulty. Must be highr than 1
    int tolerance = 60;
    int min_tolerance = 3;
    float frames_passed = 0;

    drawable sand(-55,100, "textures/scenario.png", 586, 104);
    drawable sun(-50,-50, "textures/sun.png", 90, 76, 100);
    drawable fuego((SCREEN_WIDTH - 80)*0.5,80, "textures/fuego.png", 80, 46);
    clouds cld(-300,-130,10,60);
    cowboy player(130,120,1);
    cowboy enemy(280,120,-1);
    sf::RectangleShape bar1(sf::Vector2f(SCREEN_WIDTH, 30));
    sf::RectangleShape bar2(sf::Vector2f(SCREEN_WIDTH, 30));

    bar1.setFillColor(color_palette["black"]);
    bar2.setFillColor(color_palette["black"]);

    ////////////////////////////////////////////// start of main game loop

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Enter){
                    pause = !pause;
                }

                if(!pause){
                    if (event.key.code == sf::Keyboard::Z && !game_state){

                        if(time_until_fire < 1){
                            player._state = "won";
                            enemy._state = "lost";
                            game_state = 1;
                            show_fuego = 0;
                            flash_vector.push_back(new flash_effect);
                            scrolling_text_vector.push_back(new scrolling_text(1600, 67, "textures/yee.png", 13));
                        }else{
                            //disqualified
                            show_fuego = 0;
                            player._state = "lost";
                            enemy._state = "idle";
                            game_state = 3; //locked_gamestate_for_game_over;
                        }
                        
                    }
                }
            }

            if(event.type == sf::Event::Resized){
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                resized_window_width = event.size.width;
                resized_window_height = event.size.height;
            }
        }

        //////////////// game logic start

        if(!pause){
            frames_passed++;

            if(!game_state)time_until_fire--;
            if(!time_until_fire) show_fuego = 1;

            //happens whenever the player misses the mark
            if(time_until_fire < -tolerance && game_state != 2){
                flash_vector.push_back(new flash_effect);
                show_fuego = 0;
                player._state = "lost";
                enemy._state = "won";
                game_state = 2; //locked_gamestate_for_game_over;
            }

            if(player._state == "dancing"){
                go_to_camera_x = 70;
                go_to_camera_y = 160;
                go_to_camera_zoom = 2;

            } else{
                go_to_camera_x = 0;
                go_to_camera_y = -25;
                go_to_camera_zoom = 1;
            }

            //restart the game loop after victory
            if(player._state == "idle" && game_state == 1){
                time_until_fire = 60 + rand() % 300;
                game_state = 0;
                enemy._state = "idle";
                tolerance -= tolerance/difficulty;
                if(tolerance < min_tolerance) tolerance = min_tolerance;
            }

            camera_x += (go_to_camera_x - camera_x) * camera_speed;
            camera_y += (go_to_camera_y - camera_y) * camera_speed;
            camera_zoom += (go_to_camera_zoom - camera_zoom) * 0.1;

            // update fps every second

            float currentTime = clock.getElapsedTime().asSeconds();
            frameCount++;

            if (currentTime - lastTime >= 1.0f) {
                fps = frameCount / (currentTime - lastTime);

                lastTime = currentTime;
                frameCount = 0;
            }

            //dramatic bars
            int bar_height = 30;
            bar1.setSize(sf::Vector2f(resized_window_width, bar_height));
            bar2.setSize(sf::Vector2f(resized_window_width, bar_height));

            bar1.setPosition(0,0);
            bar2.setPosition(0,resized_window_height - bar_height);

            fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

            //flash_effect destruction
            flash_conditional_delete(flash_vector, &flash_effect::get_frames, ">", 20);
            //scrolling_text destruction
            drawable_conditional_delete(scrolling_text_vector, &drawable::get_x, "<", -1200);

            //drawing all instances

            window.clear(background_color);

            sun.draw(window);
            cld.draw(window);
            sand.draw(window);

            player.animation();
            player.draw(window);

            enemy.animation();
            enemy.draw(window);


            if(show_fuego){
                fuego._x = (SCREEN_WIDTH - 80)*0.5 + sin(frames_passed*0.2)*5;
                fuego.draw(window);
            }

            window.draw(bar1);
            window.draw(bar2);

            for(auto i: scrolling_text_vector){
                i -> draw(window);
            }

            for(auto i: flash_vector){
                i -> draw(window);
            }

            if(game_state == 2){
                game_over.setPosition(resized_window_width - 180, resized_window_height - 30);
                window.draw(game_over);
            }

            if(game_state == 3){
                disqualified.setPosition(resized_window_width - 180, resized_window_height - 30);
                window.draw(disqualified);
            }

            window.draw(fpsText);
            window.display();
        }

    }

    return 0;
}