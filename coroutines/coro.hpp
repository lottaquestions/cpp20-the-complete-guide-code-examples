#include <iostream>
#include "corotask.hpp"

CoroTask coro(int max){
    std::cout << "  CORO " << max << " start\n";
    for (int val = 1; val <= max; ++val){
        std::cout << "  CORO " << val << "/" << max << std::endl;
        co_await std::suspend_always{};  // SUSPEND
    } 

    std::cout << "  CORO " << max << " start\n";
}