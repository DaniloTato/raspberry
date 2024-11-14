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
void conditional_delete(std::vector<T*>& pointer_list, int (drawable::*getter)(),
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


double avg(const std::vector<double>& vec) {
    double suma = 0;
    for (auto num : vec) {
        suma += num;
    }
    return suma / vec.size();
}

#endif