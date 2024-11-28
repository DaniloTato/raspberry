#include "../../include/iot.hpp"
#include "../functions.cpp"
#include "../../include/macros.hpp"

bool cowboy_game(sf::RenderWindow& window, sql::Connection* conn, circle_transition& transition, sf::RectangleShape& fade){

    camera_x = 0;
    camera_y = -25;
    go_to_camera_x = camera_x;
    go_to_camera_y = go_to_camera_y;

    sf::Color background_color = color_palette["purple"];

    ////////////////////////////////////////////// object creation

    sf::Text game_over;
    game_over.setFont(font);
    game_over.setCharacterSize(10);
    game_over.setFillColor(sf::Color::White);
    game_over.setString("Fin del Juego...");
    
    sf::Text disqualified;
    disqualified.setFont(font);
    disqualified.setCharacterSize(10);
    disqualified.setFillColor(sf::Color::White);
    disqualified.setString("Descalificado...");

    std::vector<double> reaction_times;
    
    //must be deleted when ending the game loop
    std::vector<flash_effect*> flash_vector;
    std::vector<scrolling_text*> scrolling_text_vector;
    //

    bool show_fuego = 0;
    int time_until_fire = 300;
    int game_state = 0;
    int difficulty = 5; /*the lower the number, the higher the difficulty. Must be highr than 1 */
    const int MAX_DIFFICULTY = 10;
    int tolerance = 60;
    int min_tolerance = 3;
    float frames_passed = 0;
    unsigned int duration = 0;
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

    //mySQL action

        int game_id = insert_into_juego(conn, "Tiempo de reacción.", "Cowboy", "Sin notas.");

    //mySQL action end

    ////////////////////////////////////////////// start of main game loop

    while (window.isOpen())
    {
        sf::Event event;

        duration++;

        button1 = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Enter){
                    paused = !paused;
                }

                if (event.key.code == sf::Keyboard::Escape){
                    delete_ptr_vector(flash_vector);
                    delete_ptr_vector(scrolling_text_vector);
                    return 1;
                }
            }
        }

        if (fade.getFillColor().a > 0) fade.setFillColor(sf::Color(0,0,0, fade.getFillColor().a - 8));

        //////////////// game logic start

        if(!paused){
            if (input_m.is_button_pressed("b1") && !game_state){

                if(time_until_fire < 1){
                    player._state = "won";
                    enemy._state = "lost";
                    game_state = 1;
                    show_fuego = 0;
                    flash_vector.push_back(new flash_effect);
                    scrolling_text_vector.push_back(new scrolling_text(1600, 67, "textures/yee.png", 13));
                    double reaction = -time_until_fire/56.0f;
                    reaction_times.push_back(reaction);

                    // mysqlx::Table testingTable = db.getTable("testing");
                    // testingTable.insert("fecha", "puntaje", "juego", "nivel", "tipo")
                    // .values(get_date(), reaction, "viejo_oeste",  MAX_DIFFICULTY - difficulty, "tiempo_de_reacción")
                    // .execute();

                    //mySQL action
                        insert_into_results(conn, reaction, game_id, "tiempo de reacción");
                    //mySQL action end

                }else{
                    //disqualified
                    show_fuego = 0;
                    player._state = "lost";
                    enemy._state = "idle";
                    game_state = 3; //locked_gamestate_for_game_over;
                    frames_passed = 0;

                    // if(reaction_times.size()){
                    //     mysqlx::Table testingTable = db.getTable("testing");
                    //     testingTable.insert("fecha", "puntaje", "juego", "nivel", "tipo")
                    //     .values(get_date(), avg(reaction_times), "viejo_oeste",  MAX_DIFFICULTY - difficulty, "tiempo_de_reacción_promedio_de_la_partida")
                    //     .execute();
                    // }

                    //mySQL action
                        if(reaction_times.size()) insert_into_results(conn, avg(reaction_times), game_id, "tiempo de reacción promedio");
                        insert_game_duration(conn, duration/57, game_id);
                    //mySQL action end
                }
            }

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
                frames_passed = 0;

                // if(reaction_times.size()){
                //     mysqlx::Table testingTable = db.getTable("testing");
                //     testingTable.insert("fecha", "puntaje", "juego", "nivel", "tipo")
                //     .values(get_date(), avg(reaction_times), "viejo_oeste",  MAX_DIFFICULTY - difficulty, "tiempo_de_reacción_promedio_de_la_partida")
                //     .execute();
                // }

                //mySQL action
                    if(reaction_times.size()) insert_into_results(conn, avg(reaction_times), game_id, "tiempo de reacción promedio");
                    insert_game_duration(conn, duration/57, game_id);
                //mySQL action end
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

            //game logic end

            CAMERA_POSITION_UPDATE();
            // update fps every second
            fpsc.calculate_fps();

            //dramatic bars
            int bar_height = 30;
            bar1.setSize(sf::Vector2f(resized_window_width, bar_height));
            bar2.setSize(sf::Vector2f(resized_window_width, bar_height));

            bar1.setPosition(0,0);
            bar2.setPosition(0,resized_window_height - bar_height);

            //flash_effect destruction
            flash_conditional_delete(flash_vector, &flash_effect::get_frames, ">", 20);
            //scrolling_text destruction
            conditional_delete(scrolling_text_vector, &drawable::get_x, "<", -1200);

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
                if (frames_passed == 120) transition.start_transition();
            }

            if(game_state == 3){
                disqualified.setPosition(resized_window_width - 180, resized_window_height - 30);
                window.draw(disqualified);
                if (frames_passed == 120) transition.start_transition();
            }

            transition.draw(window);

            window.draw(fade);

            if(transition.ending()) return 1;

            fpsc.draw(window);
            window.display();
        }

    }

    return 0;
}