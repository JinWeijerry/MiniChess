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
  int val=-99999999;
  Move ans;
  for(auto i:actions){
    int temp=rec(state->next_state(i),depth,false);
    if(temp>=val){
      val=temp;
      ans=i;
    }
  }
  return ans;
}
int MiniMax::rec(State *state,int depth,bool player){
  if(depth==0)return state->evaluate();
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(player){
    int val=-9999999;
    for(auto i:actions){
      int temp=rec(state->next_state(i),depth-1,false);
      if(val<=temp){
        val=temp;
      }
    }
    return val;
  }
  else{
    int val=9999999;
    for(auto i:actions){
      int temp=rec(state->next_state(i),depth-1,true);
      if(val>=temp){
        val=temp;
      }
    }
    return val;
  }

}
