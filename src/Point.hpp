#ifndef POINT_HPP
#define POINT_HPP

#include <cinttypes>
#include <ostream>

typedef signed char int8;


/**
 * @brief The Point struct
 * usefull class to navigate through
 * the map, has some operators to
 * increment it's x and y value,
 * the two int (x and y) are public
 * and can be modified has the user pleases
 */
struct Point{
    /**
     * @brief Point empty constructor
     */
    Point():x(0),y(0){}

    /**
     * @brief Point constructor with x and y position
     * @param _x x position of the point
     * @param _y y position of the point
     */
    Point(int8 _x, int8 _y) : x(_x), y(_y){}

    /**
     * @brief operator - the difference between this point and the
     * given point
     * @param other point to differ with
     * @return
     */
    Point operator -(const Point &other) const{
        return Point(x - other.x, y - other.y);
    }

    /**
     * @brief operator + the sum of the x and y values of this point
     * and the other
     * @param other the point to sum with
     * @return a new point containing the sum of this point and the given point
     */
    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

    /**
     * @brief operator -= removes the given point to this point
     * @param other
     * @return the point itself
     */
    Point &operator -=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /**
     * @brief operator += adds the given point to this point
     * @param other
     * @return the point itself
     */
    Point &operator +=(const Point &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
     * @brief toInt6 encodes the point into a 6 bits int,
     * used to encode the state in a 64 bits int
     * a 64 bits int is returned in order to be able to do bit shifting
     * and 'or' operators with others 64 bits ints
     * @return the 6 bits encoded point into a 64 bits int
     */
    int64_t toInt6() const
    {
        return 0x3F & (((x-1) & 0x07) |  ( ((y-1) & 0x07) << 3));
    }

    /**
     * @brief operator == if the point is the same as the given point
     * @param other
     * @return wether the x and y coordinates are the same for this point and the other point
     */
    bool operator==(const Point & other) const
    {
        return x == other.x && y == other.y;
    }

    int8 x,y;
};


#endif // POINT_HPP
