#include <future>
#include <iostream>
#include <syncstream> // For std::osyncstream for atomic writes to output streams
#include <vector>
#include <thread>

// It provides the guarantee that all output made to the same final 
// destination buffer (std::cout in the examples above) will be free 
// of data races and will not be interleaved or garbled in any way, 
// Defined this way because it will be launched across multiple threads.
// Another alternative for the same thread would have been:
//    std::osyncstream synced_out(std::cout); // synchronized wrapper for std::cout
#define sync_cout std::osyncstream(std::cout)

int main(){
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::shared_future<int> shared_fut = fut.share();

    std::vector<std::jthread> threads;

    for (int i = 0; i < 5 ; ++i){
        threads.emplace_back([shared_fut, i](){
            sync_cout << "Thread " << i << ": Result = " << shared_fut.get() << std::endl;
        });
    }
    prom.set_value(5);
    return 0;
}