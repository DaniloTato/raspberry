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
        int random_num = rand() % (max_index + 1);

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

#endif