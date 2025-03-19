#include <utility> // For std::invoke
#include <functional> // For std::forward

template<typename Callable, typename... Args>
void call(Callable&& op, Args&&... args){
    // Call passed callable with all the additionally passed arguments.
    std::invoke(std::forward<Callable>(op), std::forward<Args>(args)...);
}