#include "Car.hpp"

StateCar::StateCar(int8 carCode, int8 carOrigin):
    code(carCode),
    origin(carOrigin)
{

}

int8 StateCar::toInt7() const
{
    return ((code & 0x0f) << 4) | ((origin-1) & 0x07);
}

MapCar::MapCar(int8 carCode, int8 carLength, Orientation carOrientation, int8 carAxis):
    code(carCode),
    length(carLength),
    orientation(carOrientation),
    axisValue(carAxis)
{
}


MapCar::MapCar():
code(0),
length(0),
orientation(Orientation::VERTICAL),
axisValue(0)
{

}

Point MapCar::otherEnd(const StateCar &car, int incr) const
{
    if(orientation == VERTICAL){
        return Point(axisValue, car.origin + length + incr);
    } else {
        return Point(car.origin + length + incr, axisValue);
    }
}

Point MapCar::originEnd(const StateCar &car, int decr) const
{
    if(orientation == VERTICAL) {
        return Point(axisValue, car.origin - decr);
    } else {
        return Point(car.origin - decr, axisValue);
    }
}
