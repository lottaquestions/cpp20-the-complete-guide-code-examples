#include <iostream>
#include <compare>
#include <algorithm> // For for_each

// To compile: g++ -std=c++20 -fconcepts-diagnostics-depth=2 sentinel1.cpp -o sentinel1.bin

struct NullTerm{
    bool operator==(auto pos) const{
        return *pos == '\0'; // End is where iterator points to '\0'
    }
};

int main(){
    const char* rawString = "hello world";
    // Iterate over the range of the begin of rawString and its end
    for(auto pos = rawString ; pos != NullTerm{}; ++pos){
        std::cout << " " << *pos;
    }
    std::cout << std::endl;

    // Call range algorithm with iterator and sentinel
    std::ranges::for_each(rawString,
                          NullTerm{}, // End is null terminator
                          [](char c)
                          { std::cout << ' ' << c; });
    std::cout << std::endl;

    // Alternatively we can use a subrange with the raw string and a null terminator
    std::ranges::subrange rawStringRange{rawString, NullTerm{}};
    std::ranges::for_each(rawStringRange,
        [](char c)
        { std::cout << ' ' << c; });
    std::cout << std::endl;
    return 0;
}
