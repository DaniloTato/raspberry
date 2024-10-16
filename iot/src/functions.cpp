#include "../include/iot.hpp"

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
void drawable_conditional_delete(std::vector<T*>& pointer_list, int (drawable::*getter)(),
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