#include <iostream>
#include <ranges> // For std::ranges::range<T> concept

template<typename T>
class ValueOrCollection
{
private:
    T value;
public:
    ValueOrCollection(T& val) : value(val){}
    ValueOrCollection(T&& val) : value(std::move(val)){}
    void print() const {
        std::cout << value << std::endl;
    }

    void print() const requires std::ranges::range<T>{
        for(auto &elem : value){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

