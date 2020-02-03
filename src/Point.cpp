#include "Point.hpp"

std::ostream &operator<<(std::ostream &out, const Point &p)
{
    return out << "(x=" << (int)p.x << ", y=" << (int)p.y << ")";
}
