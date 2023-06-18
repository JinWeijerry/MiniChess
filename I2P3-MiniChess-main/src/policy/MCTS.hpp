#pragma once
#include "../state/state.hpp"
#include<vector>


/**
 * @brief Policy class for greedy policy, 
 * your policy class should have get_move method
 */
struct node{
        node(State*state){
            s=state;
        }
        int win=0;
        int n=0;
        State *s;
        Move m={{0,0},{0,0}};
        bool check=false;
        node*parent=nullptr;
        std::vector<node*> child;
};
class MCTS{
public:
  static Move get_move(State *state, int depth);
  
};
