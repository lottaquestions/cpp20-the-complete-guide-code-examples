#include <concepts>
#include <iostream>
#include <array>
#include <vector>
#include <span>
template<auto Val>
concept LessThan10 = Val < 10;

template<typename T, int Size>
requires LessThan10<Size>
class MyType{
    std::vector<T> innerArray;
    public:
    MyType(std::span<T, Size> arrayIn) {
        innerArray.reserve(Size);
        innerArray.insert(innerArray.end(), std::move_iterator(arrayIn.begin()), std::move_iterator(arrayIn.end()));
    }

    void print(){
        for (auto &elem : innerArray){
            std::cout << elem << "  ";
        }
        std::cout << std::endl;
    }
};

int main(){
    std::vector<int> myVec{1,2,3};
    std::array<int,3> myArr{4,5,6};
    MyType<int,3> myType(std::span<int,3>{myVec});

    myType.print();

    MyType<int,3> myType2(std::span<int,3>{myArr});
    myType2.print();
    return 0;
}