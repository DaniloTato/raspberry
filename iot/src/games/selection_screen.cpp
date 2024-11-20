#include "../../include/iot.hpp"
#include "../../include/macros.hpp"

bool selection_screen(sf::RenderWindow& window, int& game_selection){

    game_selection = -1;

    std::vector<drawable*> letters;
    int letters_starting_x = 50;
    int letters_starting_y = 50;
    unsigned long frames = 0;
    for(int i = 0; i < 12; i++){
        if(i == 4 || i == 10) continue;
        letters.push_back(new drawable(i*32 + letters_starting_x, 32 + letters_starting_y, "textures/bien_hecho.png", 32, 32, 1, i));
    }

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

            if(game_selection != -1) return 1;

            window.clear(sf::Color::White);

            int j = 0;
            for(auto i: letters){
                i -> _extra_y = (sinf(frames/10.0f + j / 2.0f))*5;
                i -> draw(window);
                j++;
            }

            window.display();
        }

    }

    return 0;
}