#include <string>
#include <coroutine>
#include <utility> // For std::exchange: replaces an object with a new value and returns the old value

struct Chat{
#include "promise_type.hpp"

    using Handle = std::coroutine_handle<promise_type>; // Shortcut for the handle type
    Handle mCoroHdl{};

    explicit Chat(promise_type* p) : mCoroHdl{Handle::from_promise(*p)} {} // Get the handle from the promise
    Chat(Chat&& rhs) : mCoroHdl {std::exchange(rhs.mCoroHdl, nullptr)} {} // Chat is only move-enabled

    ~Chat(){
        if (mCoroHdl){
            mCoroHdl.destroy();
        }
    }

    std::string listen(){
        if (not mCoroHdl.done()){
            mCoroHdl.resume();
        }
        return std::move(mCoroHdl.promise()._msgOut);
    }

    void answer(std::string msg){
        mCoroHdl.promise()._msgIn = msg;
        if (not mCoroHdl.done()){
            mCoroHdl.resume();
        }
    }
};
