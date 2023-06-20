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
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  int alpha=-999999;
  int beta=999999;
  Move ans=actions[0];
  for(auto i:actions){
    auto next=state->next_state(i);
    int temp=rec(next,depth,next->player,alpha,beta);
    if(!state->player){
        if(alpha<temp){
          alpha=temp;
          ans=i;
        }
        if(alpha>=beta){
            break;
        }
    }
    else{
        if(beta>temp){
            beta=temp;
            ans=i;
        }
        if(alpha>=beta){
            break;
        }
    }
  }
  return ans;
}
int AlphaBeta::rec(State *state,int depth,bool player,int alpha,int beta){
  if(state->game_state==WIN){
    if(state->player)return -999999;
    else return 999999;
  }
  if(depth==0||state->game_state==DRAW)return state->evaluate();
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(!player){
    int a=alpha;
    int b=beta;
    for(auto i:actions){
      auto next=state->next_state(i);
      auto temp=rec(next,depth-1,next->player,a,b);
      if(a<temp){
        a=temp;
      }
      if(a>=b){
        break;
      }
    }
    return a;
  }
  else{
    int a=alpha;
    int b=beta;
    for(auto i:actions){
      auto next=state->next_state(i);
      auto temp=rec(next,depth-1,next->player,a,b);
      if(b>temp){
        b=temp;
      }
      if(a>=b){
        break;
      }
    }
    return b;
  }
}
