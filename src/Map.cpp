//
// Created by Azarias Boutin
//


#include "Map.hpp"
#include "Car.hpp"
#include <sstream>
#include <iostream>

bool isStaticValue(char data)
{
    return data == 'z' || data == 'x' || data == ' ';
}

char toReadable(int8 value)
{
    if(isStaticValue(value)) return value;
    return static_cast<char>(value + 'a');
}

std::vector<std::vector<int8>> Map::EMPTY_MAP = {};

Map::Map(){}

Map::Map(int width, int height):
m_map(height),
m_width(width),
m_height(height){
    for(auto &v: m_map)v.resize(m_width, ' ');

    // Creating empty map
    EMPTY_MAP = std::vector<std::vector<int8>>(m_height);
    for(int i = 0; i < m_height; ++i){
        std::vector<int8> target(0);
        if(i == 0 || i == m_height -1) {
            target.resize(m_width, 'x');
        }else {
            target.resize(m_width, ' ');
            target[0] = 'x';
            target[m_width-1] = 'x';
        }
        EMPTY_MAP[i] = target;
    }
}

int Map::width() const
{
    return m_width;
}

int Map::height() const
{
    return m_height;
}

void Map::setValue(int x, int y, char value)
{
    if(!isValid(x, y))return;
    if(isStaticValue(value)){
        m_map[y][x] = value;
        if(value == 'z') {
            m_wayOut = Point(x, y);
            EMPTY_MAP[y][x] = 'z';
        }
    }else {
        m_map[y][x] = value - 'a';
    }
}

const Point& Map::exit() const
{
    return m_wayOut;
}

const MapCar &Map::getCarData(int8 code) const
{
    return m_cars.find(code)->second;
}

char Map::at(int x, int y) const
{
    if(!isValid(x, y)) return '@';
    return m_map[y][x];
}

char Map::at(const Point &p) const
{
    if(!isValid(p.x, p.y)) return '@';
    return m_map[p.y][p.x];
}

void Map::setCarValue(int x, int y, int8 value)
{
    int8& val = m_map[y][x];

    if(val != ' '){
        // Error cell not empty
        throw std::runtime_error(
                    "The impossible happened, two cars collided, on x = " + std::to_string(x) + ", y = "  + std::to_string(y) +
                    "\nExisting value = " + toReadable(val) + " - trying to add " + toReadable(value));
    } else{
        val = value;
    }
}

void Map::addCar(const StateCar &car)
{
    MapCar carData = getCarData(car.code);
    Point start = carData.originEnd(car);
    Point end = carData.otherEnd(car);

    if(carData.orientation == Orientation::VERTICAL){
        for(int y = start.y; y < end.y; ++y){
            setCarValue(carData.axisValue, y, car.code);
        }
    } else {
        for(int x = start.x; x < end.x; ++x){
            setCarValue(x, carData.axisValue, car.code);
        }
    }
}

void Map::reset()
{
    m_map = std::vector<std::vector<int8>>();
    for(const auto& vec : EMPTY_MAP) {
        m_map.push_back(vec);
    }
}

bool Map::canMoveCar(const StateCar &car, int direction) const
{
    const MapCar &mCar = getCarData(car.code);
    int incr = 0;
    if(direction < 0){
        do{
            incr--;
            if(at(mCar.originEnd(car, -incr)) != ' '){
                return false;// Other car already here
            }
        }while(incr != direction);
    } else{
        do{
            if(at(mCar.otherEnd(car, incr)) != ' '){
                return false;// Other car already here
            }
            incr++;
        }while(incr != direction);
    }
    return true;
}

int Map::distanceAfter(const StateCar &car) const
{
    MapCar carData = getCarData(car.code);
    if(carData.orientation == Orientation::VERTICAL){
        return m_width - car.origin - carData.length - 1;
    } else {
        return m_height - car.origin - carData.length - 1;
    }
}

StateCar Map::getCar(const int x, const int y)
{
    char code = m_map[y][x];
    m_map[y][x] = ' ';
    Orientation carOrientation = Orientation::HORIZONTAL;
    int8 carLength = 1;
    if(m_map[y+1][x] == code){
        carOrientation = Orientation::VERTICAL;
        int incr = 1;
        while(m_map[y + incr][x] == code){
            m_map[y+incr][x] = ' ';
            carLength++;
            incr++;
        }
    } else if(m_map[y][x+1] == code) {
        int incr = 1;
        while(m_map[y][x + incr] == code){
            m_map[y][x + incr] = ' ';
            carLength++;
            incr++;
        }
    } else{
        // Error, cars of length one do not exist
        throw std::runtime_error("Can't process cars with length 1");
    }
    // Be able to encode the car code with only 4 bits
    Point carData = carOrientation == Orientation::VERTICAL ? Point(x, y) : Point(y, x);

    m_cars[code] = MapCar(code, carLength, carOrientation, carData.x);
    return StateCar(code, carData.y);
}

std::string Map::toString() const
{
    std::stringstream ss;
    for(const auto & vec : m_map){
        for(auto &chr : vec){
            ss << toReadable(chr);
        }
        ss << "\n";
    }
    return ss.str();
}


bool Map::isValid(int x, int y) const
{
    return x >= 0 && y >= 0 && x < m_width && y < m_height;
}
