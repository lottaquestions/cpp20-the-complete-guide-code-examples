struct CoroTask::promise_type {
    auto get_return_object(){ // Init and return the coroutine interface
        return CoroTask{CoroHdl::from_promise(*this)};
    }

    auto initial_suspend(){           // Initial suspend point:
        return std::suspend_always{}; // Suspend immediately
    }

    void unhandled_exception(){  // Deal with exceptions:
        std::terminate();        // Terminate the program
    }

    void return_void(){}  // Deal with the end or co_return

    auto final_suspend() noexcept {  // Final suspend point:
        return std::suspend_always;  // Suspend immediately
    }
};