#include "include/iot.hpp"
#include "src/drawable.cpp"
#include "src/clouds.cpp"
#include "src/cowboy.cpp"

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

    float lastTime = 0;
    int frameCount = 0;
    float fps = 0;

    ////////////////////////////////////////////// object creation

    bool show_fuego = 0;
    int fuego_x_pos = 195;
    int time_until_fire = 300;

    int tolerance = 120;
    float frames_passed = 0;

    drawable sand(-55,100, "textures/scenario.png", 586, 104);
    drawable sun(-50,-50, "textures/sun.png", 90, 76, 100);
    drawable fuego(fuego_x_pos,80, "textures/fuego.png", 80, 46);
    clouds cld(-300,-130,10,60);
    cowboy player(130,120,1);
    sf::RectangleShape bar1(sf::Vector2f(SCREEN_WIDTH, 30));
    sf::RectangleShape bar2(sf::Vector2f(SCREEN_WIDTH, 30));

    bar1.setFillColor(color_palette["black"]);
    bar2.setFillColor(color_palette["black"]);

    ////////////////////////////////////////////// start of main game loop

    while (window.isOpen())
    {
        frames_passed++;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Z){
                    player._state = "won";
                }
            }

            if(event.type == sf::Event::Resized){
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                resized_window_width = event.size.width;
                resized_window_height = event.size.height;
            }
        }

        time_until_fire--;
        if(!time_until_fire) show_fuego = 1;
        if(time_until_fire < -tolerance) show_fuego = 0, player._state = "lost";

        if(player._state == "dancing"){
            go_to_camera_x = 70;
            go_to_camera_y = 160;
            go_to_camera_zoom = 2;

        } else{

            go_to_camera_x = 0;
            go_to_camera_y = -25;
            go_to_camera_zoom = 1;

            if(player._state == "idle" && (player._last_frame_state != "idle")) time_until_fire = 300;
        }

        camera_x += (go_to_camera_x - camera_x) * camera_speed;
        camera_y += (go_to_camera_y - camera_y) * camera_speed;
        camera_zoom += (go_to_camera_zoom - camera_zoom) * 0.1;

        // Update FPS every second

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

        window.clear(background_color);

        sun.draw(window);
        cld.draw(window);
        sand.draw(window);

        player.animation();
        player.draw(window);


        if(show_fuego){
            fuego._x = fuego_x_pos + sin(frames_passed*0.2)*5;
            fuego.draw(window);
        }

        window.draw(bar1);
        window.draw(bar2);

        window.draw(fpsText);
        window.display();

    }

    return 0;
}