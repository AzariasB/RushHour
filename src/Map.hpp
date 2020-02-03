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


bool isStaticValue(char data);

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

    char at(int x, int y) const;

    char at(const Point &p) const;

    const Point  &exit() const;

    const MapCar &getCarData(int8 code) const;

    bool canMoveCar(const StateCar &car, int direction) const;

    int distanceAfter(const StateCar & car) const;

    void addCar(const StateCar &car);

    /**
     * @brief toString string version of the map
     * @return
     */
    std::string toString() const;

    void setValue(int x, int y, char value);
    /**
     * @brief reset removes all the boxes
     * and the player of the map,
     * only the target, the empty places
     * and the target are left afterward
     */
    void reset();

    int width() const;

    int height() const;

    StateCar getCar(const int x,  const int y);

private:

    static std::vector<std::vector<int8>> EMPTY_MAP;

    void setCarValue(int x, int y, int8 value);

    /**
     * @brief map the map itself
     */
    std::vector<std::vector<int8>> m_map;

    std::unordered_map<int8, MapCar> m_cars;

    Point m_wayOut;

    int m_width;

    int m_height;
};


#endif //SOKOBAN_MAP_H
