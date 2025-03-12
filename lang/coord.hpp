#include <compare>

struct Coord
{
    double x{};
    double y{};
    double z{};
    auto operator<=>(const Coord&) const = default;
};
