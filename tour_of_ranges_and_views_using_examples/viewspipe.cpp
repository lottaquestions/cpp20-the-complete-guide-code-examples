#include <iostream>
#include <vector>
#include <map>
#include <ranges>

// To compile: g++ -std=c++20 -fconcepts-diagnostics-depth=2 viewspipe.cpp -o viewspipe.bin

int main() {
    namespace vws = std::views;

    // Map of composers, mapping their name to their year of birth
    std::map<std::string, int> composers{
        {"Bach", 1685},
        {"Mozart", 1756},
        {"Beethoven", 1770},
        {"Tchaikovsky", 1840},
        {"Chopin", 1810},
        {"Vivaldi", 1678}
    };

    // Iterate over the names of the first 3 composers born since 1700
    for (const auto &elem : composers | vws::filter([](const auto &curElem)
                                                    { return curElem.second >= 1700; }) 
                                      | vws::take(3) 
                                      | vws::keys // keys i.e. names only
    ){
        std::cout << "- "<< elem << std::endl;
    }
    return 0;
}