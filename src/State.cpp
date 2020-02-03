//
// Created by Azarias Boutin
//


#include "State.hpp"
#include "Map.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <bitset>

std::unordered_map<std::string, bool> State::knownStates = {};

State::State():
    m_mainCar(0,0)//Init with 'wrong' values
{

}

State::State(const State &copy):
    m_mainCar(copy.m_mainCar),
    m_cars()
{
    for(const auto & car : copy.m_cars) m_cars.push_back(StateCar(car));
}



void State::applyTo(Map &m)
{
    m.addCar(m_mainCar);
    for(const auto &car : m_cars) m.addCar(car);
}

std::string State::serialize() const
{
    std::stringstream ss;
    ss << m_mainCar.toInt7();

    for(const StateCar &car : m_cars) ss << car.toInt7();
    return ss.str();
}

bool State::isSolutionOf(const Map &m)
{
    //Is solution if the main car is next to the exit
    /*
     * Could be improved in : is the solution
     * if the space between the exit and the main car is free
     */
    MapCar carData = m.getCarData(m_mainCar.code);
    const Point &out = m.exit();
    return carData.originEnd(m_mainCar) == out ||
            carData.otherEnd(m_mainCar) == out;
}

void State::computeNextCarMove(Map &map, StateCar &car, std::vector<int> &moves)
{
    int before = car.origin - 1;
    if(before > 0){
        for(int i = 1; i <= before; ++i) {
            if(map.canMoveCar(car, -i)){
                moves.push_back(-i);
            }
        }
    }
    int after = map.distanceAfter(car);
    if(after > 0){
        for(int i = 1; i <= after; ++i){
            if(map.canMoveCar(car, i)){
                moves.push_back(i);
            }
        }
    }
}

void State::computeNextStates(Map &map, int pred, std::vector<State> &stateQueue, std::unordered_map<int,int> &anc)
{
    applyTo(map);
    std::vector<int> moves;
    computeNextCarMove(map, m_mainCar, moves);
    for(int i : moves){
        m_mainCar.origin += i;
        if(stateCreated(*this)){
            State copy = *this;
            stateQueue.push_back(copy);
            anc[stateQueue.size() -1] = pred;
        }
        m_mainCar.origin -= i;
    }
    for(auto& car : m_cars) {
        moves.clear();
        computeNextCarMove(map, car, moves);
        for(int i : moves){
            car.origin += i;
            if(stateCreated(*this)){
                State copy = *this;
                stateQueue.push_back(copy);
                anc[stateQueue.size() -1] = pred;
            }
            car.origin -= i;
        }
    }
    map.reset();
}

bool State::stateCreated(const State &origin)
{
    std::string encoded = origin.serialize();

    bool &val = knownStates[encoded];
    if(val) return false;
    return (val = true);
}

void State::extractFrom(Map &map)
{
    for(int y = 1; y < map.height() - 1; ++y){
        for(int x = 1; x < map.width() - 1; ++x){
            if(map.at(x ,y) != ' ') {
                StateCar c = map.getCar(x, y);
                if(c.code == 0){
                    m_mainCar = c;
                }else{
                    m_cars.push_back(c);
                }
            }
        }
    }
}
