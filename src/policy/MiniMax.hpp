#pragma once
#include "../state/state.hpp"
#include<vector>


/**
 * @brief Policy class for greedy policy, 
 * your policy class should have get_move method
 */
class MiniMax{
public:
  static Move get_move(State *state, int depth);
  static std::pair<int,Move> rec(State *state,int depth,bool player);
};

