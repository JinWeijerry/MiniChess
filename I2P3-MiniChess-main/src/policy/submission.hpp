#pragma once
#include "../state/state.hpp"
#include<vector>


/**
 * @brief Policy class for greedy policy, 
 * your policy class should have get_move method
 */
class AlphaBeta{
public:
  static Move get_move(State *state, int depth);
  static int rec(State *state,int depth,bool self,int a,int b);
};