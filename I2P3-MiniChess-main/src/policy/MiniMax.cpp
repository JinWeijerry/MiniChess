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
  return rec(state,depth,state->player).second;
}
std::pair<int,Move> MiniMax::rec(State *state,int depth,bool player){
  if(depth==0)return {state->evaluate(),{{0,0},{0,0}}};
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(!player){
    std::pair<int,Move >ans={-9999999,{{0,0},{0,0}}};
    for(auto i:actions){
      auto next=state->next_state(i);
      auto temp=rec(next,depth-1,next->player);
      if(temp.first>=ans.first){
        ans.first=temp.first;
        ans.second=i;
      }
    }
    return ans;
  }
  else{
    std::pair<int,Move >ans={9999999,{{0,0},{0,0}}};
    for(auto i:actions){
      auto next=state->next_state(i);
      auto temp=rec(next,depth-1,next->player);
      if(temp.first<=ans.first){
        ans.first=temp.first;
        ans.second=i;
      }
    }
    return ans;
  }
}
