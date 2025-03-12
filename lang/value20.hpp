#include <compare>

class Value
{
private:
    long id;
public:
    constexpr Value(long i) noexcept
    : id(i){}
    // Enable use of all equality and relational operators
    auto operator<=>(const Value& rhs) const = default;
};

