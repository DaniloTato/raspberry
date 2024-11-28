#include "../../include/iot.hpp"
#include "../../include/macros.hpp"

bool selection_screen(sf::RenderWindow& window, int& game_selection, sf::RectangleShape& fade){

    game_selection = -1;

    std::vector<drawable*> letters;
    int letters_starting_x = 15;
    int letters_starting_y = 150;
    unsigned long frames = 0;
    int frames_sice_selection = 0;
    float fade_oppacity = 0;

    for(int i = 0; i < 28; i++){
        if(i == 9 || i == 19 || i == 22) continue;
        letters.push_back(new drawable(i*16 + letters_starting_x, 16 + letters_starting_y, "textures/esperando_seleccion.png", 16, 16, 1, i));
    }

    drawable logo((resized_window_width - 233)*0.5,70,"textures/neurobox_logo.png", 233, 61);
    drawable squares(-130, -70, "textures/square_texture.png", 512, 700, 2);
    drawable icon((resized_window_width - 64)*0.5, 500 + (resized_window_height - 64)*0.5, "textures/game_icons.png", 64, 64);
    icon._size = 2;
    icon._size_position_mode = 1;

    while (window.isOpen())
    {
        frames++;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Num1){
                game_selection = 0;
            }
            if (event.key.code == sf::Keyboard::Num2){
                game_selection = 1;
            }
            if (event.key.code == sf::Keyboard::Num3){
                game_selection = 2;
            }
        }

        //////////////// game logic start

        if(!paused){

	    gpioWrite(PIN_LED_END, 0);

            if(game_selection != -1) {
                if(!frames_sice_selection){
                    int number_of_frames[3] = {5,7,24};
                    icon.loop_animate(number_of_frames[game_selection], game_selection);
                }
                frames_sice_selection++;
                go_to_camera_y = 500;
                if(frames_sice_selection > 100) fade_oppacity += 8;
                if(fade_oppacity > 255) fade_oppacity = 255;

		gpioWrite(PIN_BUZZER, 1);

                if(frames_sice_selection > 130) {
		    gpioWrite(PIN_LED_START, 1);
                    gpioWrite(PIN_BUZZER, 0);
		    return 1;
		}
            }

            fade.setSize(sf::Vector2f(resized_window_width, resized_window_height));
            fade.setFillColor(sf::Color(0,0,0,fade_oppacity));
            fade.setPosition(sf::Vector2f(0,0));

            CAMERA_POSITION_UPDATE();

            logo._x = (resized_window_width - 233)*0.5;
            logo._size_position_mode = 1;
            logo._size = 1 + cos(frames/50.0f)*0.05;

            window.clear(sf::Color::White);

            squares.draw(window);

            icon.draw(window);

            int j = 0;
            for(auto i: letters){
                i -> _extra_y = (sinf(frames/10.0f + j / 2.0f))*5;
                i -> draw(window);
                j++;
            }

            logo.draw(window);

            window.draw(fade);
            window.display();
        }

    }

    return 0;
}
