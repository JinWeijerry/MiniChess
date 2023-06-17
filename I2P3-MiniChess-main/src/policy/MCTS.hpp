#pragma once
#include "../state/state.hpp"
#include<vector>


/**
 * @brief Policy class for greedy policy, 
 * your policy class should have get_move method
 */
class node{
    public:
        node(){};
        node(State*s){
            s=s;
        }
        int win=0;
        int n=0;
        State *s=nullptr;
        Move m={{0,0},{0,0}};
        
        node*parent=nullptr;
        std::vector<node*> child;
};
class MCTS{
public:
  static Move get(State *,int) ;
  static Move get_move(State *state, int depth);
  static node* Select(node *);
  static float calculate(node*);
  static void expand(node*);
  static void backpropagation(node*,std::pair<int,int>);
  static void Del(node*root);
};
