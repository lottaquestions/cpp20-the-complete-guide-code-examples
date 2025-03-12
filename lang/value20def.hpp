#include <compare>

class Value{
    private:
    long id;
    public:
    constexpr Value(long i) noexcept
    : id{i}{}

    // For equality operators
    bool operator==(const Value& rhs) const{
        return id == rhs.id; // defines equality (== and !=)
    }

    // For relational operators
    auto operator<=>(const Value& rhs) const {
        return id <=> rhs.id; // defins ordering (<, <=, > amd >=)
    }
};