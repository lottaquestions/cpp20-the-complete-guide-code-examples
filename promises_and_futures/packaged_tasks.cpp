#include <iostream>
#include <future> // For std::packaged_task
#include <cmath> // For std::pow
#include <functional> // For std::bind
#include <thread> // For std::jthread

// To compile: g++ -std=c++2b -O0 -g3 packaged_tasks.cpp -o packaged_tasks.bin

int main(){
    // Using a thread
    std::packaged_task<int(int, int)> task1 (std::pow<int, int>);
    std::jthread t(std::move(task1), 2, 10);

    // Using a lambda function
    std::packaged_task<int(int,int)> task2([](int a, int b){
        return std::pow(a,b);
    });

    task2(2, 10);

    // Binding to a function
    std::packaged_task<int()> task3(std::bind(std::pow<int,int>, 2, 10));
    task3();

    std::cout << "task2 result = " << task2.get_future().get() << std::endl;
    std::cout << "task3 result = " << task3.get_future().get() << std::endl;

    return 0;
}