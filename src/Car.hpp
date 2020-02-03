#ifndef CAR_HPP
#define CAR_HPP

#include "Point.hpp"

enum Orientation {
    VERTICAL,
    HORIZONTAL
};

struct StateCar{

    StateCar(int8 code, int8 origin);

    int8 toInt7() const;

    int8 code;
    int8 origin;
};

struct MapCar{

    // Needed for the map
    MapCar();

    MapCar(int8 code, int8 length, Orientation orientation, int8 carAxis);

    Point otherEnd(const StateCar &car, int incr = 0) const;

    Point originEnd(const StateCar &car, int decr = 0) const;

    int8 code;
    int8 length;
    Orientation orientation;
    int8 axisValue;
};


#endif // CAR_HPP
