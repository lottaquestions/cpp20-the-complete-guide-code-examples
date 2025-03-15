#include <iostream>
#include "Chat.hpp"

using namespace std::literals; // Needed for appending s after string literals

Chat Fun(){
    co_yield "Hello!\n"s; // Calls promise_type.yield_value
    std::cout << co_await std::string{}; // Calls promise_type.await_transform
    co_return "Here!\n"s; // Calls promise_type.return_value
}

void Use (){
    Chat chat = Fun(); // Creation of the coroutine
    std::cout << chat.listen(); // Trigger the FSM 
    chat.answer("Where are you?\n"s); // Send data into the coroutine.
    std::cout << chat.listen(); // Wait for more data from the coroutine

}

int main(){
    Use();
    return 0;
}