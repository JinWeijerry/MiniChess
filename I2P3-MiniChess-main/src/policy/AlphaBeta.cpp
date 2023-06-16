#include <cstdlib>

#include "../state/state.hpp"
#include "./AlphaBeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move AlphaBeta::get_move(State *state, int depth){
  return rec(state,depth,state->player,-999999,999999).second;
}
std::pair<int,Move> AlphaBeta::rec(State *state,int depth,bool player,int alpha,int beta){
  if(depth==0)return {state->evaluate(),{{0,0},{0,0}}};
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(!player){
    int a=alpha;
    int b=beta;
    std::pair<int,Move >ans={a,{{0,0},{0,0}}};
    for(auto i:actions){
      auto next=state->next_state(i);
      auto temp=rec(next,depth-1,next->player,a,b);
      if(a<temp.first){
        a=temp.first;
        ans.second=i;
        ans.first=a;
      }
      if(a>=b){
        break;
      }
    }
    ans.first=a;
    return ans;
  }
  else{
    int a=alpha;
    int b=beta;
    std::pair<int,Move >ans={999999,{{0,0},{0,0}}};
    for(auto i:actions){
      auto next=state->next_state(i);
      auto temp=rec(next,depth-1,next->player,a,b);
      if(b>temp.first){
        b=temp.first;
        ans.second=i;
        ans.first=b;
      }
      if(a>=b){
        break;
      }
    }
    ans.first=b;
    return ans;
  }
}
