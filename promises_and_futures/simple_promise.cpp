#include <future>
#include <thread>
#include <utility>
#include <string>

// To compile: g++ -std=c++20 -O0 -g3 simple_promise.cpp -o simple_promise.bin
// For the mutable in threadStr, I needed std=c++2b to compile: g++ -std=c++2b -O0 -g3 simple_promise.cpp -o simple_promise.bin

using namespace std::literals;

int main(){
    auto threadFunc = [](std::promise<int> prom){
        try{
            int result{10};
            prom.set_value(result);
        }
        catch(...){
            prom.set_exception(std::current_exception());
        }
    };
    std::promise<int> prom;
    std::jthread t(threadFunc, std::move(prom));

    // Using generalized capture to move a promise into a thread lambda
    std::promise<std::string> promStr;

    // By default, parameters are captured as constants, so we need to specify the lambda as mutable to allow prm to be modified
    auto threadStr = std::jthread([prm = std::move(promStr)] mutable {
        std::this_thread::sleep_for(100ms);
        prm.set_value("Value sucessfully set");
    });
    return 0;
}