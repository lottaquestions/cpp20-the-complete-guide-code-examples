#include <algorithm>
#include <cctype>
#include <chrono>
#include <future>
#include <iostream>
#include <iterator>
#include <sstream>
#include <thread>
#include <vector>
#include <set>

// To compile: g++ -std=c++2b -O0 -g3 simple_promise_and_future.cpp -o simple_promise_and_future.bin

using namespace std::chrono_literals;

int main()
{
    std::promise<void> numbers_promise;
    std::promise<void> letters_promise;
    auto numbers_ready = numbers_promise.get_future();
    auto letters_ready = letters_promise.get_future();

    std::istringstream iss_numbers{"10 5 2 6 4 1 3 9 7 8"};
    std::istringstream iss_letters{"A b 53 C,d 83D 4B ca "};
    std::vector<int> numbers;
    std::set<char> letters;

    std::jthread input_data_thread([&]
                                   {
        // Step 1: Emulating I/O operations.
        std::copy(std::istream_iterator<int>{iss_numbers},
                  std::istream_iterator<int>{},
                  std::back_inserter(numbers)); 

        // Notify completion of step 1
        numbers_promise.set_value();

        // Step 2: Emulating further I/O operations
        std::copy_if(std::istreambuf_iterator<char>{iss_letters},
                     std::istreambuf_iterator<char>{}, std::inserter(letters, letters.end()),
                     ::isalpha);

        // Notify completion of step 2
        letters_promise.set_value();

    });
    // Wait for numbers vector to be filled
    numbers_ready.wait();
    std::sort(numbers.begin(), numbers.end());

    // Wait for 1 sec for letters to be available. If this period times out
    // just print out the numbers and then wait for the letters again
    if(letters_ready.wait_for(1s) == std::future_status::timeout){
        for (int num : numbers) std::cout << num << " ";
        numbers.clear();
    }

    // Wait for letters vector to be filled
    letters_ready.wait();

    // Print numbers if they had not been printed yet
    for (int num : numbers) std::cout << num << ' ';
    std::cout << std::endl;
    for (char let : letters) std::cout << let << ' ';
    std::cout << std::endl;

    return 0;

}