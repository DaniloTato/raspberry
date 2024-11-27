#include "../include/iot.hpp"

#ifndef FUNCTIONS
#define FUNCTIONS

template <typename S>
bool str_to_comparison(S arg1, std::string comparison, S arg2){
    if (comparison == "=="){
        return (arg1 == arg2);
    } else if (comparison == ">"){
        return (arg1 > arg2);
    } else if (comparison == "<"){
        return (arg1 < arg2);
    } else if (comparison == ">="){
        return (arg1 >= arg2);
    } else if (comparison == "<="){
        return (arg1 <= arg2);
    } else if (comparison == "pass"){
        return 1;
    }

    std::cout << "Invalid middle argument (comparison) in function str_to_comparison" << std::endl;
    exit(-1);
}

template <typename S>
bool find_in_vector(std::vector<S> vec, S target){
    for(auto i:vec){
        if(i == target) return 1;
    }
    return 0;
}

std::vector<int> random_indexes(int result_len, int max_index){
    std::vector<int> res;
    srand(time(0));
    for (int i = 0; i < result_len; i++){
        int random_num = rand() % (max_index);

        if(find_in_vector(res, random_num)){
            random_num = 0;
            while(find_in_vector(res, random_num)){
                random_num++;
            }
        }
        res.push_back(random_num);
    }
    return res;
}

template <typename T>
void flash_conditional_delete(std::vector<T*>& pointer_list, int (flash_effect::*getter)() = &flash_effect::get_frames,
std::string comparison = "pass", int var = 0) {

    for(int i = 0; i < pointer_list.size(); i++){

        bool comp = 1;
        if (comparison != "pass"){
            comp = str_to_comparison((pointer_list[i]->*getter)(), comparison, var);
        }

        if(comp){
            delete pointer_list[i];
            pointer_list.erase(pointer_list.begin() + i);
            i--;
        }

    }
}

template <typename T>
bool conditional_delete(std::vector<T*>& pointer_list, int (drawable::*getter)(),
std::string comparison = "pass", int var = 0) {

    bool deleted_something = false;

    for(int i = 0; i < pointer_list.size(); i++){

        bool comp = 1;
        if (comparison != "pass"){
            comp = str_to_comparison((pointer_list[i]->*getter)(), comparison, var);
        }

        if(comp){
            delete pointer_list[i];
            pointer_list.erase(pointer_list.begin() + i);
            i--;
            deleted_something = true;
        }

    }

    return deleted_something;
}

sf::Image add_border(const sf::Image& originalImage, unsigned int borderThickness) {
    unsigned int width = originalImage.getSize().x;
    unsigned int height = originalImage.getSize().y;

    sf::Image borderedImage;
    borderedImage.create(width + 2 * borderThickness, height + 2 * borderThickness, sf::Color::Transparent);

    borderedImage.copy(originalImage, borderThickness, borderThickness);

    for (unsigned int y = borderThickness; y < height + borderThickness; ++y) {
        for (unsigned int x = borderThickness; x < width + borderThickness; ++x) {
            sf::Color pixelColor = originalImage.getPixel(x - borderThickness, y - borderThickness);
            if (pixelColor.a != 0) {
                int right_limit = borderThickness;
                for (int offsetY = -borderThickness; offsetY <= right_limit; ++offsetY) {
                    for (int offsetX = -borderThickness; offsetX <= right_limit; ++offsetX) {
                        if (offsetX == 0 && offsetY == 0)
                            continue;
                        unsigned int newX = x + offsetX;
                        unsigned int newY = y + offsetY;

                        if (newX >= 0 && newX < borderedImage.getSize().x && newY >= 0 && newY < borderedImage.getSize().y) {
                            if (borderedImage.getPixel(newX, newY).a == 0) {
                                borderedImage.setPixel(newX, newY, sf::Color(255,255,255));
                            }
                        }
                    }
                }
            }
        }
    }

    return borderedImage;
}

sf::Image crop_image(const sf::Image& originalImage, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    sf::Image croppedImage;
    
    croppedImage.create(width, height);
    croppedImage.copy(originalImage, 0, 0, sf::IntRect(x, y, width, height));

    return croppedImage;
}

template <typename T>
void delete_ptr_vector(std::vector<T*>& vec){
    for(auto i : vec){
        delete i;
    }
    vec.clear();
}

std::string get_date() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d");
    return oss.str();
}

std::string time_string(int seconds) {
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;

    std::ostringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << hours << ":" 
               << std::setw(2) << std::setfill('0') << minutes << ":" 
               << std::setw(2) << std::setfill('0') << seconds;

    return timeStream.str();
}


double avg(const std::vector<double>& vec) {
    double suma = 0;
    for (auto num : vec) {
        suma += num;
    }
    return suma / vec.size();
}

int get_last_id(sql::Connection* conn){
    std::string query_last_id = "SELECT LAST_INSERT_ID()";
    std::unique_ptr<sql::PreparedStatement> pstmt_last_id(conn->prepareStatement(query_last_id));
    std::unique_ptr<sql::ResultSet> res(pstmt_last_id->executeQuery());

    if (res->next()){
        return res->getInt(1);
    }
    throw std::runtime_error("Failed to fetch last insert ID.");
}

void add_patient_id(sql::Connection* conn, int patient_id) {
    try {
        // Check if patient exists
        std::string query = "SELECT COUNT(*) FROM paciente WHERE ID_Paciente = ?";
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
        pstmt->setInt(1, patient_id);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        res->next(); // Move to the first (and only) row in the result

        if (res->getInt(1) == 0) {
            // Patient doesn't exist, insert the default patient
            query = "INSERT INTO paciente (ID_Paciente, Nombre, Edad, Diagnóstico, Dirección) "
                    "VALUES (?, 'Default Name', 0, 'Default Diagnosis', 'Default Address')";
            std::unique_ptr<sql::PreparedStatement> pstmt_2(conn->prepareStatement(query));
            pstmt_2->setInt(1, patient_id);
            pstmt_2->executeUpdate();
            std::cout << "new patient id added\n";
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        throw; // Rethrow the exception after logging
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

void insert_into_results(sql::Connection* conn, double puntuacion, int game_id, std::string type){
    std::string query = "INSERT INTO resultados (Puntuación, ID_Juego, Tipo) VALUES (?, ?, ?)";
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
    pstmt->setDouble(1, puntuacion);
    pstmt->setInt(2, game_id);
    pstmt->setString(3, type); //"tiempo para selección correcta"

    pstmt->executeUpdate();

    int results_id = get_last_id(conn);

    query = "INSERT INTO `paciente_a_resultado` (ID_Paciente, ID_Resultado) VALUES (?, ?)";
    std::unique_ptr<sql::PreparedStatement> pstmt_sk(conn->prepareStatement(query));
    pstmt_sk->setInt(1, patient_id);
    pstmt_sk->setInt(2, results_id);

    pstmt_sk->executeUpdate();
}

int insert_into_juego(sql::Connection* conn, std::string proposito, std::string nombre, std::string notas = "Sin notas."){
    std::string query = "INSERT INTO juego (Propósito, Nombre, `Notas adicionales`, Fecha) VALUES (?, ?, ?, ?)";
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
    pstmt -> setString(1,proposito);
    pstmt -> setString(2,nombre);
    pstmt -> setString(3,notas);
    pstmt -> setString(4, get_date());

    pstmt->executeUpdate();

    int game_id = get_last_id(conn);

    query = "INSERT INTO `paciente_a_juego` (ID_Paciente, ID_Juego) VALUES (?, ?)";
    std::unique_ptr<sql::PreparedStatement> pstmt_sk(conn->prepareStatement(query));
    pstmt_sk->setInt(1, patient_id);
    pstmt_sk->setInt(2, game_id);

    pstmt_sk->executeUpdate();

    return game_id;
}

void insert_game_duration(sql::Connection* conn, int seconds, int id_juego){

    std::cout << "id" << id_juego << "\n";
    std::string query = "UPDATE juego SET Duracion = ? WHERE ID_Juego = " + std::to_string(id_juego);
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
    pstmt->setString(1, time_string(seconds));

    pstmt->executeUpdate();
}

#endif