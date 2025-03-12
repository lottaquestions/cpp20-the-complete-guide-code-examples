#include <concepts>
#include <iostream>
#include <tuple>
#include <vector>

struct TestClass;

template<typename T>
concept CanHalf = requires(T t){
    {t / T(2)} -> std::same_as<T>;
};

template<CanHalf T>
requires std::integral<T>
constexpr auto Half(T x){
    return x/T(2) + (x % T(2));
}

template<CanHalf T>
constexpr auto Half(T x){
    return x/T(2);
}

struct TestClass{
    int x{0};
};

TestClass operator/(const TestClass& left, const TestClass& right){
    return TestClass(left.x/right.x);
}

int main(){
    
    const std::tuple<int, float> testVals{10, 3.2,};
    
    std::apply([](auto&&... args) { 

        ((std::cout << Half(args) << ' '), ...);
    }, testVals);
    TestClass objTest{18};
    std::cout<< Half(objTest).x << std::endl;

    return 0;
}
