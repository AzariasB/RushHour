//
// Created by Azarias Boutin
//


#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <array>
#include "Point.hpp"
#include "Car.hpp"

class Map;
class State;


/**
 * @brief The State class core class of the problem,
 * contains a list of boxes, and the position of the player
 * can be encoded in a 64 bits int to be stored in a map, can apply
 * itself to a map, or generate itself from a map (and clean the map)
 */
class State
{
public:
    /**
     * @brief State empty constructor
     */
    State();

    State(const State &copy);

    /**
     * @brief isSolutionOf wether all the boxes of this states
     * are positionned on the targets of the map
     * @param m the map to test on
     * @return
     */
    bool isSolutionOf(const Map &m);

    /**
     * @brief applyTo puts the boxes and the player into the map
     * @param m the map to fill
     */
    void applyTo(Map &m);

    /**
     * @brief computeNextStates calculates the next states of this state,
     * will check in the four cardinal directions if its possible to move,
     * and if it is, adds the new state ins the vector (used as a queue) and
     * declares the new state as the successor of the 'pred' state
     * @param map the map to use to apply the moves and the states
     * @param pred the index of the predecessor state in the stateQueue vector
     * @param stateQueue a vector containing all the visited states and the states to visit, is used as a queue
     * @param anc the map of the ancestors, the key is the successor, the value is the successor
     */
    void computeNextStates(Map &map, int pred, std::vector<State> &stateQueue, std::unordered_map<int,int> &anc);

    /**
     * @brief extractFrom run through the viable positions of the map,
     * to get the player position and the boxes position,
     * cleans the map to remove all the boxes and the player from it
     * @param map the map to clean
     */
    void extractFrom(Map &map);

    /**
     * @brief toInt64 hash function to encode this state to an int 64
     * @return
     */
    std::string serialize() const;

private:
    /**
     * @brief knownStates a static map to save all the state that
     * where created, the key is the hash of the state,
     * the value (boolean) is wether the state was visited,
     * by default, this boolean is set to false, and when
     * a new state is created, it will be set to true
     */
    static std::unordered_map<std::string, bool> knownStates;

    /**
     * @brief stateExists checks if the given state was already created
     * @param origin the state to check for
     * @return wether the given state was already created
     */
    bool stateCreated(const State &origin);

    void computeNextCarMove(Map &map, StateCar &car, std::vector<int> &moves);


    /**
     * @brief m_ppos position of the player
     */
    StateCar m_mainCar;

    /**
     * @brief m_boxes position of the boxes
     */
    std::vector<StateCar> m_cars;

};

#endif // STATE_HPP
