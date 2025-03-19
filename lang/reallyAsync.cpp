#include <type_traits>
#include <future>
#include <iostream>

using namespace std::literals;

// A truly async future:
// To compile: g++ -std=c++20 -O0 -g3 reallyAsync.cpp -o reallyAsync.bin

template<typename F, typename... Ts>
inline std::future<std::invoke_result_t<F,Ts...>> 
reallyAsync(F&& f, Ts&&... params){
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}

int main(){
    auto fut = reallyAsync([](std::string_view person)-> std::string {
        if (person.data()){
            std::cout<< "Hello " << person << std::endl;
        }
        
        return "Greeting said";
    },
    "Lottaquestions");

    while (fut.wait_for(100ms) != std::future_status::ready);
    std::cout << fut.get() << std::endl;

    return 0;
}