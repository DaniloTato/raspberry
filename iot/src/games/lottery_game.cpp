#include "../../include/iot.hpp"
#include "../functions.cpp"

bool lottery_game(sf::RenderWindow& window){

    camera_zoom = 2;
    go_to_camera_zoom = 2;

    camera_x = -50;
    go_to_camera_x = camera_x;

    int selection = 0;

    std::vector<drawable*> icons;

    std::vector<int> selected_icons = random_indexes(12,12);

    int icon_x = 0;
    int icon_y = 0;
    int line_limit = 3;
    for (int i = 0; i < selected_icons.size(); i++){
        icons.push_back(new drawable(icon_x, icon_y, "textures/lottery/icons.png", 32, 32, 1, selected_icons[i]));
        icon_x += 32;
        if(icon_x >= 32*line_limit) icon_y += 32, icon_x = 0;
    }

    drawable grid(-2,-2,"textures/lottery/grid.png",100,132);

    animated_pointer clicky(100,0,"textures/lottery/clicky.png",16,23, 5);

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

                if (event.key.code == sf::Keyboard::Escape){
                    return 1;
                }

                if (event.key.code == sf::Keyboard::Right){
                    selection++;
                    if(selection >= icons.size()) selection = 0;
                } else if (event.key.code == sf::Keyboard::Left){
                    selection--;
                    if(selection <= -1) selection = icons.size() - 1;
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

            clicky._go_to_x = icons[selection]->_x + 16;
            clicky._go_to_y = icons[selection]->_y + 16;

            go_to_camera_y = (clicky._y) * camera_zoom - resized_window_height * 0.3;

            CAMERA_POSITION_UPDATE();

            std::cout << camera_y << " " << clicky._y << "\n";

            window.clear(sf::Color::White);

            for(auto i: icons){
                i->draw(window); 
            }

            grid.draw(window);
            clicky.draw(window);
            window.display();
        }

    }

    return 0;
}