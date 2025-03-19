#include "invoke.hpp"
#include <iostream>
#include <vector>

void print(const std::vector<int>& coll){
    std::cout << "Elems: ";
    for(const auto& elem : coll){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> vals{0, 8, 15, 42, 13, -1, 0};
    call([&vals]{
        std::cout << "size: " << vals.size() << std::endl;
    });
    call(print, vals);
    call(&decltype(vals)::pop_back, vals);
    call(print,  vals);

    call(&decltype(vals)::clear, vals);
    call(print, vals);

    call<void(decltype(vals)::*)(std::size_t)>(&decltype(vals)::resize, vals, 5);
    call<void(decltype(vals)::*)(const int&)>(&decltype(vals)::push_back, vals, 32);
    call(print, vals);

    return 0;
}