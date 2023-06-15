#include <cstdlib>

#include "../state/state.hpp"
#include "./MiniMax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
/*
Move MiniMax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int id=0;
  int maxval=0;
  for(long unsigned int i=0;i<actions.size();i++){
    int val=(state->next_state(actions[i]))->evaluate();
    if(val>=maxval){
        id=i;
        maxval=val;
    }
  }
  return actions[id];
}*/
Move MiniMax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  if(depth==0){
    long unsigned int id=0;
    int minmaxval=(state->player)?99999:-99999;
    for(long unsigned int i=0;i<actions.size();i++){
        int val=-(state->next_state(actions[i]))->evaluate();
        if((state->player)?val<=minmaxval:val>=minmaxval){
            id=i;
            minmaxval=val;
        }
    }
    return actions[id];
  }
  if(state->player==0){
    long unsigned int id=0;
    int minmaxval=-99999;
    for(long unsigned int i=0;i<actions.size();i++){
        int val=-(state->next_state(get_move(state->next_state(actions[i]),depth-1)))->evaluate();
        if(val>=minmaxval){
            id=i;
            minmaxval=val;
        }
    }
    return actions[id];
  }
  else{
    long unsigned int id=0;
    int minmaxval=99999;
    for(long unsigned int i=0;i<actions.size();i++){
        int val=-(state->next_state(get_move(state->next_state(actions[i]),depth-1)))->evaluate();
        if(val<=minmaxval){
            id=i;
            minmaxval=val;
        }
    }
    return actions[id];
  }
}