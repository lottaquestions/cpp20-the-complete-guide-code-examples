

struct promise_type{
    std::string _msgOut{}; // Storing value from the coroutine
    std::string _msgIn{}; // Storing value for the coroutine (input)

    void unhandled_exception() noexcept {} // What to do in case of an exception
    Chat get_return_object() { return Chat{this}; } // Coroutine creation.
    std::suspend_always initial_suspend() noexcept { return {}; } // Startup
    std::suspend_always yield_value(std::string msg) noexcept { // Value from co_yield
        _msgOut = std::move(msg);
        return {};
    }

    auto await_transform(std::string) noexcept{ // Value from co_await
        struct awaiter{ // Customized version instead of using suspend_always or suspend_never
            promise_type& pt;
            constexpr bool await_ready() const noexcept { return true; }
            std::string await_resume() const noexcept { return std::move(pt._msgIn); }
            void await_suspend(std::coroutine_handle<>) const noexcept {}
        };

        return awaiter{*this};
    }

    void return_value(std::string msg) noexcept { _msgOut = std::move(msg); } // Value from co_return
    std::suspend_always final_suspend() noexcept { return {}; } // Ending
};
