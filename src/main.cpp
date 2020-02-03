//
// Created by Azarias Boutin
//


#include <iostream>
#include <fstream>
#include <chrono>
#include "State.hpp"
#include "Map.hpp"

Map parseFile(const std::string &mapName)
{
    std::ifstream mapF;
    mapF.open(mapName);
    if(!mapF.is_open()){
        std::cerr << "File not found " << std::endl;
        return Map(0, 0);//;//empty map
    }

    int width = 0;
    int height = 0;
    mapF >> height;
    mapF.ignore();// comma
    mapF >> width;
    mapF.ignore();// \n

    std::string input;
    std::getline(mapF, input);

    std::cout << "Map width = " << width << ", height = " << height << std::endl;

    Map mMap(width, height);
    for(int y = 0; y < height; ++y){//read all columns
        std::getline(mapF, input);
        for(int x = 0; x < width; ++x){// read all lines
            mMap.setValue(x, y, input[x]);
        }
    }

    mapF.close();
    // Map detect objects
    return mMap;
}

int main(int argc, char **argv) {
    if(argc < 2){
        std::cerr << "Must pass filename in parameter\n";
        return -1;
    }

    Map m = parseFile(argv[1]);
    std::vector<State> states;
    states.emplace_back();

    states.back().extractFrom(m);


    int cursor = 0;
    states.reserve(100000);
    std::unordered_map<int,int> anc;
    int finalState = -1;

    auto start = std::chrono::system_clock::now();
    while(cursor < states.size()){
        auto &next = states[cursor];
        if(next.isSolutionOf(m)){
            finalState = cursor;
            break;
        }
        next.computeNextStates(m, cursor, states, anc);
        cursor++;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    std::vector<int> order;
    order.reserve(15);
    if(finalState > -1){
        std::cout << "Found solution !\n";
        while(finalState != 0){
            order.push_back(finalState);
            finalState = anc[finalState];
        }
        order.push_back(0);

        std::cout << "In " << order.size() - 1 << " moves\n";
        std::cout << "Explored " << cursor << " states\n";
        std::cout << "Elapsed seconds : " << elapsedSeconds.count() << "\n";
        std::cout << "[Presse ENTER to see the steps]\n";

        for(int i = order.size() -1; i >= 0; --i){
            State &s = states[order[i]];
            s.applyTo(m);
            std::cout << m.toString();
            std::cin.ignore();
            m.reset();
        }
    } else {
        std::cout << "No solution found :(\n";
    }
    return 0;
}
