#include "coord.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

// To compile: /home/nick/Software/gcc13.2/installation/bin/g++-13.2 -std=c++20 -O0 -g3 coord.cpp -o coord.bin
// To run: LD_LIBRARY_PATH=/home/nick/Software/gcc13.2/installation/lib64 ./coord.bin

int main(){
    std::vector<Coord> coll { {0, 5, 5}, {5, 0, 0}, {3, 5, 5}, {3, 0, 0}, {3, 5, 7}};
    std::sort(coll.begin(), coll.end());
    for (const auto& elem : coll){
        std::cout << elem.x << '/' << elem.y << '/' << elem.z << std::endl;
    }
    return 0;
}