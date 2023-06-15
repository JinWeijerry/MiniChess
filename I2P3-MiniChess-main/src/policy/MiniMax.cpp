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
Move MiniMax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int id=0;
  int maxval;
  for(int i=0;i<actions.size();i++){
    int val=(state->next_state(actions[i]))->evaluate();
    if(val>maxval){
        id=i;
        maxval=val;
    }
  }
  return actions[id];
}