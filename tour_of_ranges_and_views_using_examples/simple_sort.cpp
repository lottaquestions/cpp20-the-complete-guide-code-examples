#include <algorithm> // Most range algorithms are still in algorithm
#include <ranges> // For std::views::take et al
#include <vector>
#include <string>
#include <iostream>

// To compile: g++ -std=c++20 -fconcepts-diagnostics-depth=2 simple_sort.cpp -o simple_sort.bin

namespace rg = std::ranges;

void print( const auto& collection){
    for (const auto& elem : collection){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void printFirst(const auto& collection, int count){
    print(std::views::take(collection, count));
}

int main(){
    std::vector<int> vecColl{25, 42, 2, 0, 122, 5, 7, 76, 38, 4};
    rg::sort(vecColl);
    print(vecColl);
    printFirst(vecColl, 3);

    std::vector<std::string> vecStrColl{"Rio", "Tokyo", "New York", "Berlin"};
    rg::sort(vecStrColl);
    print(vecStrColl);

    int arr[] = {42, 0, 8, 15, 7};
    rg::sort(arr);
    print(arr);

    // Filter even elements, square their value and get the first 3 of the result using pipelines
    auto transV = vecColl
    | std::views::filter([](auto elem){ return elem % 2 == 0 && elem > 0; })
    | std::views::transform([](auto elem){ return elem * elem; })
    | std::views::take(3);

    std::vector<int> resultVector{};
    resultVector.reserve(3);
    for (const auto elem : transV){
        resultVector.emplace_back(elem);
    }
    print(resultVector);

    return 0;
}