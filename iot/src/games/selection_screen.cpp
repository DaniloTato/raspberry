#include "../../include/iot.hpp"
#include "../../include/macros.hpp"

bool selection_screen(sf::RenderWindow& window, int& game_selection){

    game_selection = -1;

    std::vector<drawable*> letters;
    int letters_starting_x = 15;
    int letters_starting_y = 150;
    unsigned long frames = 0;
    int frames_sice_selection = 0;
    
    for(int i = 0; i < 28; i++){
        if(i == 9 || i == 19 || i == 22) continue;
        letters.push_back(new drawable(i*16 + letters_starting_x, 16 + letters_starting_y, "textures/esperando_seleccion.png", 16, 16, 1, i));
    }

    drawable logo((resized_window_width - 233)*0.5,70,"textures/neurobox_logo.png", 233, 61);
    drawable squares(-130, -70, "textures/square_texture.png", 512, 256, 2);

    while (window.isOpen())
    {
        frames++;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::Resized){
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                resized_window_width = event.size.width;
                resized_window_height = event.size.height;
            }
        }

        //////////////// game logic start

        if(!paused){

            if(game_selection != -1) {
                frames_sice_selection++;
                go_to_camera_y = 500;
                if(frames_sice_selection > 120) return 1;
            }

            CAMERA_POSITION_UPDATE();

            logo._x = (resized_window_width - 233)*0.5;
            logo._size_position_mode = 1;
            logo._size = 1 + cos(frames/50.0f)*0.05;

            window.clear(sf::Color::White);

            squares.draw(window);

            int j = 0;
            for(auto i: letters){
                i -> _extra_y = (sinf(frames/10.0f + j / 2.0f))*5;
                i -> draw(window);
                j++;
            }

            logo.draw(window);
            window.display();
        }

    }

    return 0;
}