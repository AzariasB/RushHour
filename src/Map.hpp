//
// Created by Azarias Boutin
//

#ifndef SOKOBAN_MAP_H
#define SOKOBAN_MAP_H

#include <vector>
#include <queue>
#include <string>
#include "Car.hpp"
#include "State.hpp"

/**
 * @brief isStaticValue checks wether the given car
 * is a value that has a special meaning it could be
 *  - x for the border of the map
 *  - z for the map's exit
 *  - space for an empty spot
 * @param data the char to test
 * @return wether the given char as a special meaning for the map
 */
bool isStaticValue(char data);

/**
 * @brief toReadable turns the given car code into a
 * printable character (0 becomes a, 1 becomes b, ...)
 * the static values are kept as is
 * @param value the value to turn into a printable char
 * @return the printable char
 */
char toReadable(int8 value);

/**
 * @brief The Map class contains a 2 dimensionnal
 * vector, with all the data about the basic map
 * (the walls, the empty spaces, and the targets)
 * States can be applied to the map, in order
 * to put the player and the boxes, to calculate
 * the next states
 */
class Map {
public:
    /**
     * @brief Map default empty constructor
     */
    Map();

    /**
     * @brief Map constructor with the width and height,
     * to initiliaze the space of the grid
     * @param width width of the map
     * @param height height of the map
     */
    Map(int width, int height);

    /**
     * @brief isAccessible if the cell in the given direction
     * is accessible, starting from the given origin point
     * @param origin the point to move from
     * @param dir the direction to follow
     * @return if the cell is accessible (if it's empty,
     * or there is a box in it, and this box can be pushed)
     */
    bool isAccessible(const Point &origin, const Point &dir) const;

    /**
     * @brief isValid if the given point is within the boundaries of the map
     * @param p point to check
     * @return wether the point is within the boundaries of the map
     */
    bool isValid(int x, int y) const;

    /**
     * @brief at get the map value at the given coordinates
     * and '@' if the coordinates are invalid(used for debugging purpose)
     * @param x the x coordinate
     * @param y the y coordinate
     * @return the value of the map at the given coordinates
     */
    char at(int x, int y) const;

    /**
     * @brief at port of the other 'at' function, but for a point object
     * @param p the point where to get the data
     * @return the value of the map at the given coordinates
     */
    char at(const Point &p) const;

    /**
     * @brief exit accessor for the map's way out
     * @return the map exit position
     */
    const Point  &exit() const;

    /**
     * @brief getCarData finds the MapCar corresponding
     * to the given code
     * @param code the code of the car to search for
     * @return the mapCar that has the given code
     */
    const MapCar &getCarData(int8 code) const;

    /**
     * @brief canMoveCar on of the main function of this solver
     * checks if the given car can move 'direction' block away
     * from its position
     * the direction parameter can be positive or negative,
     * to be able to move, a car must have a clear path to
     * the point it must move to, if a single car is present
     * on its way, it will be unable to move
     * @param car the car to check for
     * @param direction the direction the car is trying to move toward
     * @return wether the car can move safely toward the given direction
     */
    bool canMoveCar(const StateCar &car, int direction) const;

    /**
     * @brief distanceAfter gets the distance between the end
     * of the car, and the map's border, used to see if a
     * car can move in this direction
     * This function does not check if cars might stop the given
     * car before the order, this is done by the function 'canMoveCar'
     * @param car the car to check
     * @return the distance between the given car and the map's border
     */
    int distanceAfter(const StateCar & car) const;

    /**
     * @brief addCar changes the map to add the given car
     * can throw an exception if a car is already positioned where
     * the new car is placed
     * @param car the car to place
     */
    void addCar(const StateCar &car);

    /**
     * @brief toString string version of the map
     * @return
     */
    std::string toString() const;

    /**
     * @brief setValue used when first initialzing the map
     * this function is a raw setter to create the map and
     * put the cars, it just puts the given car at the given
     * coordinate
     * @param x the x coordinate
     * @param y the y coordinate
     * @param value the value to set
     */
    void setValue(int x, int y, char value);

    /**
     * @brief reset removes all the boxes
     * and the player of the map,
     * only the target, the empty places
     * and the target are left afterward
     */
    void reset();

    /**
     * @brief width accessor to the map's width
     * @return the map's width
     */
    int width() const;

    /**
     * @brief height accessor the the map's height
     * @return the map's height
     */
    int height() const;

    /**
     * @brief getCar only used by the first state
     * search from the given point the car with the given
     * code, also erases (replaces with spaces) the car
     * found, when the car is found, the StateCar is
     * returned, and the associated MapCar is stored inside
     * this map
     * @param x the x starting point of the car
     * @param y the y starting point of the car
     * @return the StateCar found
     */
    StateCar getCar(const int x,  const int y);

private:
    /**
     * @brief setCarValue used when adding a car on the map
     * checks if the spot is empty and throws an exception
     * if it's no
     * @param x the x coordinate to search for
     * @param y the y coordinate to search for
     * @param value the value to set
     */
    void setCarValue(int x, int y, int8 value);

    /**
     * @brief m_map the map itself
     */
    std::vector<std::vector<int8>> m_map;

    /**
     * @brief m_emptyMap an empty map, kept
     * in memory to quickly reset the main
     * map when needed
     */
    std::vector<std::vector<int8>> m_emptyMap;

    /**
     * @brief m_cars quick access to the map's
     * cars, the key is the car's code, and the
     * value is the MapCar
     */
    std::unordered_map<int8, MapCar> m_cars;

    /**
     * @brief m_wayOut the map's exit position
     */
    Point m_wayOut;

    /**
     * @brief m_width the map's width
     */
    int m_width;

    /**
     * @brief m_height the map's height
     */
    int m_height;
};


#endif //SOKOBAN_MAP_H
