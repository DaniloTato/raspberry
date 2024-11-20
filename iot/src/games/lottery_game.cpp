#include "../../include/iot.hpp"
#include "../functions.cpp"
#include "../../include/macros.hpp"

bool next_card(std::vector<card*>& cards, std::vector<int>& selected_icons){
    if(cards.size()) cards.front() -> card_exit();

    if(selected_icons.size()){
        int index = rand() % selected_icons.size();
        cards.push_back(new card(500, -10, selected_icons[index]));
        selected_icons.erase(selected_icons.begin() + index);
    } else{
        go_to_camera_x = -140;
        return 0;
    }

    return 1;
}

int update_selection(int row, int column){
    return 3*row + column;
}

void check_icon(std::vector<int>& pinned, std::vector<int>& selected_icons, int& selection, std::vector<card*>& cards, std::vector<drawable*> icons, 
    std::vector<coin*>& coins, std::vector<scrolling_text*>& scrolling_texts, unsigned int &reaction_time, const int SCORE_TIME_TOLERANCE, 
    unsigned long& score, animated_pointer& clicky, sql::Connection* conn, const int game_id){

    if(!find_in_vector(pinned, selection) && cards.size()){
        if(icons[selection] -> get_frame_x() == cards.front() -> get_symbol_costume()){
            coins.push_back(new coin(icons[selection]->_x + 16, -50, icons[selection]->_y, selection));
            pinned.push_back(selection);
            if (!next_card(cards, selected_icons)){
                scrolling_texts.push_back(new scrolling_text(resized_window_width, 0, "textures/lottery/loteria.png", 10, 2));
            }
            int score_to_add = 100 - (reaction_time/SCORE_TIME_TOLERANCE);
            if(score_to_add > 0) score += score_to_add;

            //mySQL action

                std::string query = "INSERT INTO resultados (Puntuación, ID_Juego, Tipo) VALUES (?, ?, ?)";
                std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
                pstmt->setDouble(1, reaction_time/57.0f);
                pstmt->setInt(2, game_id);
                pstmt->setInt(3, 1); //"tiempo para selección correcta"

                pstmt->executeUpdate();

                int results_id = get_last_id(conn);

                query = "INSERT INTO `paciente_a_resultado` (ID_Paciente, ID_Resultado) VALUES (?, ?)";
                std::unique_ptr<sql::PreparedStatement> pstmt_sk(conn->prepareStatement(query));
                pstmt_sk->setInt(1, patient_id);
                pstmt_sk->setInt(2, results_id);

                pstmt_sk->executeUpdate();

            
            //mySQL action end

            reaction_time = 0;
        } else clicky.shake_it(5);
    } else{
        clicky.shake_it(5);
    }
}

bool lottery_game(sf::RenderWindow& window, sql::Connection* conn, circle_transition& transition){

    unsigned long frames;
    unsigned long duration;

    camera_zoom = 2;
    go_to_camera_zoom = 2;

    camera_x = -50;
    go_to_camera_x = camera_x;

    int selection = 0;
    const int GAME_MODE = 0;

    unsigned long score = 0;
    unsigned int reaction_time = 0;
    const int SCORE_TIME_TOLERANCE = 6;

    int clicky_row = 0;
    int clicky_column = 0;

    sf::Text score_text;
    score_text.setFont(font);
    score_text.setCharacterSize(10);
    score_text.setFillColor(color_palette["blue"]);

    //must be deleted when ending the game loop
    std::vector<drawable*> icons;
    std::vector<card*> cards;
    std::vector<coin*> coins;
    std::vector<scrolling_text*> scrolling_texts;
    std::vector<drawable*> feedback;
    ///////

    std::vector<int> pinned;

    std::vector<int> selected_icons = random_indexes(12,12);

    //mySQL action

        std::string query = "INSERT INTO juego (Propósito, Nombre, `Notas adicionales`) VALUES (?, ?, ?)";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
        pstmt -> setString(1,"Coordinación mano ojo.");
        pstmt -> setString(2,"Lotería");
        pstmt -> setString(3,"Sin notas");

        pstmt->executeUpdate();

        int game_id = get_last_id(conn);

        query = "INSERT INTO `paciente_a_juego` (ID_Paciente, ID_Juego) VALUES (?, ?)";
        std::unique_ptr<sql::PreparedStatement> pstmt_sk(conn->prepareStatement(query));
        pstmt_sk->setInt(1, patient_id);
        pstmt_sk->setInt(2, game_id);

        pstmt_sk->executeUpdate();

    //mySQL action end

    int icon_x = 0;
    int icon_y = 0;
    int line_limit = 3;
    for (int i = 0; i < selected_icons.size(); i++){
        icons.push_back(new drawable(icon_x, icon_y, "textures/lottery/icons.png", 32, 32, 1, selected_icons[i]));
        icon_x += 32;
        if(icon_x >= 32*line_limit) icon_y += 32, icon_x = 0;
    }

    drawable grid(-2,-2,"textures/lottery/grid.png",100,132);
    ui gear(resized_window_width - 100, resized_window_height - 100, "textures/lottery/gear.png", 61,62);
    ui gear2(-61, -62, "textures/lottery/gear.png", 61,62);

    int bar_height = 32;
    sf::RectangleShape purple_bar(sf::Vector2f(SCREEN_WIDTH, bar_height));
    purple_bar.setFillColor(color_palette["purple"]);

    animated_pointer clicky(100,0,"textures/lottery/clicky.png",16,23, 5);

    next_card(cards, selected_icons);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Enter){
                    paused = !paused;
                }

                if (event.key.code == sf::Keyboard::Escape){
                    delete_ptr_vector(icons);
                    delete_ptr_vector(cards);
                    delete_ptr_vector(coins);
                    return 1;
                }

                if (event.key.code == sf::Keyboard::Right){
                    selection++;
                    if(selection >= icons.size()) selection = 0;
                    frames = 0;
                } else if (event.key.code == sf::Keyboard::Left){
                    selection--;
                    if(selection <= -1) selection = icons.size() - 1;
                    frames = 0;
                }

                if (event.key.code == sf::Keyboard::A){

                    if(clicky_column == 0) check_icon(pinned, selected_icons, selection, cards, icons, coins, scrolling_texts, reaction_time, SCORE_TIME_TOLERANCE, score, clicky, conn, game_id);
                    else gear2.animate(7, 0, 3, 1);
                    clicky_column = 0;
                    selection = update_selection(clicky_row, clicky_column);

                } else if (event.key.code == sf::Keyboard::S){

                    if(clicky_column == 1) check_icon(pinned, selected_icons, selection, cards, icons, coins, scrolling_texts, reaction_time, SCORE_TIME_TOLERANCE, score, clicky, conn, game_id);
                    else gear2.animate(7, 0, 3, (clicky_column > 1));
                    clicky_column = 1;
                    selection = update_selection(clicky_row, clicky_column);

                } else if (event.key.code == sf::Keyboard::D){

                    if(clicky_column == 2) check_icon(pinned, selected_icons, selection, cards, icons, coins, scrolling_texts, reaction_time, SCORE_TIME_TOLERANCE, score, clicky, conn, game_id);
                    else gear2.animate(7, 0, 3, 0);
                    clicky_column = 2;
                    selection = update_selection(clicky_row, clicky_column);

                } if (event.key.code == sf::Keyboard::F){

                    clicky_row++;
                    if(clicky_row > 3) clicky_row = 0, gear.animate(7, 0, 3, 1);
                    else gear.animate(7, 0, 3);
                    selection = update_selection(clicky_row, clicky_column);

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
        if(!paused){

            frames++;
            reaction_time++;

            purple_bar.setPosition(0,resized_window_height - bar_height);

            clicky._go_to_x = icons[selection]->_x + 16;
            clicky._go_to_y = icons[selection]->_y + 16;

            go_to_camera_y = (clicky._y) * camera_zoom - resized_window_height * 0.3;

            CAMERA_POSITION_UPDATE();

            conditional_delete(cards,&drawable::get_x,"<",-70);
            //scrolling_text destruction
            if (conditional_delete(scrolling_texts, &drawable::get_x, "<", -1200)){
                transition.start_transition();
            }

            //drawing phase
            window.clear(sf::Color::White);

            grid.draw(window);

            for(int i = 0; i < icons.size(); i++){
                if(i == selection){
                    if(!find_in_vector(pinned, selection)){
                        icons[i] -> _size = 1 + abs(cos(frames*0.05)*0.2);
                    } else icons[i] -> _size = 1;
                } else icons[i] -> _size = 1;

                icons[i] ->draw(window);
            }

            for(auto i: coins){
                if(i -> get_linked_space() == selection) i -> loop_animate(5,0);
                else i -> end_loop_animate();

                i->draw(window);
            }

            clicky.draw(window);

            gear._x = resized_window_width - 150;
            gear._y = resized_window_height - 130;
            gear.draw(window);
            gear2.draw(window);

            purple_bar.setScale(sf::Vector2f(resized_window_width, bar_height));
            window.draw(purple_bar);

            for(auto i: cards){
                i->draw(window); 
            }

            for(auto i: scrolling_texts){
                i->draw(window); 
            }

            score_text.setPosition(resized_window_width - 170, resized_window_height - 22);
            score_text.setString("Puntaje [ " + std::to_string(score) + " ]");
            window.draw(score_text);

            transition.draw(window);

            window.display();

            //end of drawing phase
            //check if the transition has ended so we can end the game
            if(transition.ending()){
                return 1;
            }
        }

    }

    return 0;
}