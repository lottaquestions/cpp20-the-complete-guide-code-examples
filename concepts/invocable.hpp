#include <span>
#include <concepts>

/*
   Example code to use the concept std::invocable to check if a passed in type is invocable
*/

// Example that checks if the parameter is invocable directly
class BlockProcessor1
{
public:
    void Process(std::span<const float> input,
                 std::span<float> output,
                 std::invocable < std::span<float>> auto&& processFn);
};

// Example that checks if the template parameter is invocable
class BlockProcessor2
{
public:
    template<std::invocable<std::span<float>> ProcessFn>
    void Process(std::span<const float> input,
                 std::span<float> output,
                 ProcessFn &&);
};
