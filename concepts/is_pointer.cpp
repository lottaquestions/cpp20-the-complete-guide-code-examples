#include <concepts>
#include <iostream>

// g++ -std=c++20 -fconcepts-diagnostics-depth=2 is_pointer.cpp -o is_pointer.bin

template<typename T>
requires (!std::is_pointer_v<T>)
T maxValue(T a, T b){
    return a > b ? a : b;
}

template<typename T>
concept IsPointer = std::is_pointer_v<T>;

template<typename T>
requires (!IsPointer<T>) // Negated concepts need parens 
T maxValue2(T a, T b){
    return a > b ? a : b;
}

template<typename T>
requires IsPointer<T> // Non-negated concepts do not need parens
auto maxValue2(T a, T b){
    return maxValue2(*a, *b);
}

// Using a concept as a type constraint
template<IsPointer T>
auto maxValue3(T a, T b){
    return maxValue2(*a, *b);
}

// Using a concept with auto parameters
auto maxValue4(const IsPointer auto a, const IsPointer auto b){
    return maxValue2(*a, *b);
}

// Using a trailing requires clause to do additional constraint checking on parameters.
auto maxValue5(const IsPointer auto a, const IsPointer auto b) requires std::equality_comparable_with<decltype(*a), decltype(*b)> {
    return maxValue2(*a, *b);
}

// Another trailing requires that uses a standard library concept
auto maxValue6(const IsPointer auto a, const IsPointer auto b) requires std::totally_ordered_with<decltype(*a), decltype(*b)>{
    return maxValue2(*a, *b);
}

// Concept with multiple constraints
template<typename T>
concept IsPointer2 = requires (T p) {
    *p;                            // operator* has to be valid
    p == nullptr;                  // has to be comparable against nullptr
    {p < p} -> std::same_as<bool>; // operator< yields a boolean
};

auto maxValue7(const IsPointer2 auto a, const IsPointer2 auto b){
    return maxValue2(*a, *b);
}

// Constraining a templated function with an ad-hoc constraint (unnamed concept)
template<typename T>
requires requires (T p){ *p; } // requires clause calling a requires expression, hence the double requires requires
auto maxValue8(T a, T b){
    return maxValue2(*a, *b);
}


int main(){
    int a {10}, b{30};
    std::cout << "The maximum value between " << a << " and " << b << " is " << maxValue(a,b) << std::endl;
    std::cout << "The maximum value between " << a << " and " << b << " is " << maxValue2(a,b) << std::endl;
    //Below will fail to compile
    //std::cout << maxValue(&a,&b) << std::endl;
    std::cout << "The maximum value between contents of " << &a << " and contents of " << &b << " is " << maxValue2(&a,&b) << std::endl;

    // The templated functions can be called recursively as shown in the example below, since the both the pointer and non-pointer
    // versions of maxValue2 are instantiated, and the pointer version dereferences what has been passed to it then calls maxValue2
    // again.
    int *ap = &a;
    int *bp = &b;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue2(&ap,&bp) << std::endl;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue3(&ap,&bp) << std::endl;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue4(&ap,&bp) << std::endl;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue5(&ap,&bp) << std::endl;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue6(&ap,&bp) << std::endl;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue7(&ap,&bp) << std::endl;
    std::cout << "The maximum value between contents of " << &ap << " and contents of " << &bp << " is " << maxValue8(&ap,&bp) << std::endl;
    
    return 0;
}