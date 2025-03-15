#include <coroutine>

// Coroutine interface to deal with a simple task
// providing resume() to resume the coroutine
class [[nodiscard]] CoroTask
{
public:
    // Initialize members for state and customization
    struct promise_type; // Defined later in corotaskpromise.hpp
    using CoroHdl = std::coroutine_handle<promise_type>;
private:
    CoroHdl hdl; // Native coroutine handle

public:
     CoroTask(auto h) : hdl(h){} // Store coroutine handle in interface
     ~CoroTask(){
        if(hdl){
            hdl.destroy(); // Destroy coroutine handle
        }
     }
     // Disallow copying or moving
     CoroTask(const CoroTask&) = delete;
     CoroTask& operator=(const CoroTask&) = delete;
     //CoroTask(CoroTask&&) = delete;

     // API to resume the coroutine
     // returns whether there is still something to process
     bool resume() const {
        if(!hdl or hdl.done()){
            return false; // Nothing (more) to process
        }
        hdl.resume(); // Resume blocks until suspended again or the end
        return !hdl.done();
     }
};

#include "corotaskpromise.hpp"

