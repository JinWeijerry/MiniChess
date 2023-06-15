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

Move MiniMax::get_move(State *state, int depth,bool self){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  if(depth==0){
    long unsigned int id=0;
    int minmaxval=(self)?99999:-99999;
    for(long unsigned int i=0;i<actions.size();i++){
        int val=(state->next_state(actions[i]))->evaluate();
        if((self)?val<=minmaxval:val>=minmaxval){
            id=i;
            minmaxval=val;
        }
    }
    return actions[id];
  }
  if(self){
    long unsigned int id=0;
    int minmaxval=-99999;
    for(long unsigned int i=0;i<actions.size();i++){
        int val=(state->next_state(get_move(state->next_state(actions[i]),depth-1,false)))->evaluate();
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
        int val=(state->next_state(get_move(state->next_state(actions[i]),depth-1,true)))->evaluate();
        if(val<=minmaxval){
            id=i;
            minmaxval=val;
        }
    }
    return actions[id];
  }
}