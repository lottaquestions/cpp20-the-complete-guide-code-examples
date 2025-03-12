#include <concepts>
#include <string>
#include <iostream>

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

template<typename T>
auto GetDefaultValue(){
    if constexpr (requires {T::defaultValue();}){
        return T::defaultValue();
    } else {
        return T::defaultValue;
    }
}

int main(){
    std::cout << GetDefaultValue<Size>() << std::endl;
    std::cout << GetDefaultValue<Title>() << std::endl;
}