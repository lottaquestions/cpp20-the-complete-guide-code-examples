#include <concepts>
#include <string>
#include <iostream>

// To compile: g++ -std=c++20 -fconcepts-diagnostics-depth=2 HasDefaultValue.cpp -o HasDefaultValue.bin

struct Size{
    using type = float;
    static constexpr auto name = "Size";
    static constexpr type defaultValue = 100.f;
};

struct Title{
    using type = std::string;
    static constexpr auto name = "Title";
    static type defaultValue() {return "My Button";};
};

struct BorderWidth{
    using type = float;
    static constexpr auto name = "BorderWidth";
};

template<typename T>
concept HasDefaultValueFunction = requires {
    T::defaultValue();
};

template<HasDefaultValueFunction T>
auto GetDefaultValue(){
    return T::defaultValue();
}

template<typename T>
concept HasDefaultValue = std::same_as< std::remove_const_t<decltype(T::defaultValue)>, typename T::type>;


template<HasDefaultValue T>
auto GetDefaultValue(){
    return T::defaultValue;
}

template<std::default_initializable T>
requires (!HasDefaultValueFunction<T> && !HasDefaultValue<T>)
auto GetDefaultValue(){
    return typename T::type{};
}

int main(){
    std::cout << GetDefaultValue<Size>() << std::endl;
    std::cout << GetDefaultValue<Title>() << std::endl;
    std::cout << GetDefaultValue<BorderWidth>() << std::endl;
    return 0;
}