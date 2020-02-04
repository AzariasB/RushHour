#ifndef CAR_HPP
#define CAR_HPP

#include "Point.hpp"

/**
 * @brief The Orientation enum
 * The car's orientation
 */
enum Orientation {
    VERTICAL,
    HORIZONTAL
};

/**
 * @brief The StateCar struct
 * The state car must be as small as possible to be replicated as much
 * as possible without consumming too much memroy. It contains only the
 * car's code (its id) and its origin.
 * The origin is the left-most part when the car is horizontal, and
 * the top-most part when the car is vertical
 * It can be encoded on 7 bits, assuming the map has no more than 16 cars
 * and the map cannot be bigger than 10x10 (including borders)
 * The StateCar struct is stored for every cars on every State
 */
struct StateCar{

    /**
     * @brief StateCar constructor
     * @param code the car's id, must be unique and not used by other cars
     * @param origin the top-left most part of the car (depending on it's orientation)
     */
    StateCar(int8 code, int8 origin);

    /**
     * @brief toInt7 encodes this StateCar on a 7 bits int
     * The 4 bigger bits encode the car's code (thus cannot be bigger than 15)
     * and the 3 smaller bits encode the car's origin (thus cannot be bigger than 7)
     * @return the encoded car
     */
    int8 toInt7() const;

    /**
     * @brief code the car's unique id,
     * used to retrieve the metadata stored in the map
     */
    int8 code;

    /**
     * @brief origin the car's top-left most point on the map
     * This is the only variable that can change on the map, all the other
     * variables (length, orientation, axis) always remain the same, and
     * are store in the map
     */
    int8 origin;
};

struct MapCar{

    /**
     * @brief MapCar empty constructor for the std::unordered_map
     */
    MapCar();

    /**
     * @brief MapCar the mapCar is all the car's metadata that do not change
     * during the game :
     *  - its length
     *  - its orientation
     *  - its axis
     * These are stored only once during the solving, in the map. To get all
     * the data of a car, one just need to cross a MapCar and it's corresponding
     * StateCar
     * @param code the car's unique id, used to retrieve the corresponding stateCar
     * @param length the length of the car (usually is 2 or 3).
     * The solver cannot process cars of length 1 since they can go both ways
     * (and it seems that the rushHour game doesn't have length-1 cars)
     * @param orientation the car orientation, can be Orizontal or Vertical
     * @param carAxis the x value of the car if the car is vertical,
     * the y value if the car is horizontal
     */
    MapCar(int8 code, int8 length, Orientation orientation, int8 carAxis);

    /**
     * @brief otherEnd the coordinates of the 'end' of the car
     * (the right-bottom part)
     * @param car the StateCar to cross the data with, the origin
     * of the stateCar is needed to determine the car's end
     * @param incr one can increment the end to check if there is something
     * further away of the car
     * @return the coordinate of the end of the car, plus an additional incr box(es)
     */
    Point otherEnd(const StateCar &car, int incr = 0) const;

    /**
     * @brief originEnd the coordinates of the origin of the car
     * (the top-left part)
     * @param car the stateCar to cross the data with
     * @param decr one can decrement the position to check is there is
     * something further away of the car
     * @return the coordinates of the origin of the car, minus an additional decr box(es)
     */
    Point originEnd(const StateCar &car, int decr = 0) const;

    /**
     * @brief code the code of the car
     * needed to cross the data with the StateCar
     */
    int8 code;

    /**
     * @brief length the length of the car
     */
    int8 length;

    /**
     * @brief orientation the car's orientation
     */
    Orientation orientation;

    /**
     * @brief axisValue the x value if the car is vertical
     * and the y value if the car is horizontal
     */
    int8 axisValue;
};


#endif // CAR_HPP
