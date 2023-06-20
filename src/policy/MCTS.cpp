#include <cstdlib>

#include "../state/state.hpp"
#include "./MCTS.hpp"
#include<math.h>

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
float calculate(node*root){
    if(root->n==0)return 99999999;
    if(root->parent->n==0)return 0.0;
    int w=root->win;
    if(root->s->player)w=root->n-root->win;
    float l=log(root->parent->n);
    if(l<0)l=0;
    return w/root->n+20000*pow(l/root->n,0.5);
}
void backpropagation(node*root,std::pair<int,int> wn){
    if(root==nullptr)return;
    root->win+=wn.first;
    root->n+=wn.second;
    backpropagation(root->parent,wn);
}

node* Select(node *root){
    if(!root->child.size())return root;
    float maxmin=-9999999;
    node *ans=root;
    for(auto i:root->child){
        float val=calculate(i);
        if(val>maxmin){
            maxmin=val;
            ans=i;
        }
    }
    return Select(ans);
}

void expand(node*root){
    if(root->s->game_state==WIN){
        if(!root->s->player){
            backpropagation(root,{1,1});
        }
        else{
            backpropagation(root,{0,1});
        }
        return;
    }
    if(root->s->game_state==DRAW){
        backpropagation(root,{0,1});
        return;
    }
    if(root->s->legal_actions.empty()){
        backpropagation(root,{0,1});
        return;
    }
    for(auto& i:root->s->legal_actions){
        auto temp=new node(root->s->next_state(i));
        temp->m=i;
        temp->parent=root;
        root->child.emplace_back(temp);
    }
}
Move get(State *state, int height){
  node*root=new node(state);
  root->check=true;
  int d=0;
  while (d<=height)
  {
    node* next=Select(root);
    if(next->check){
        expand(next);
        d++;
        continue;
    }
    int step=50;
    auto simulstate=new State(next->s->board);
    next->check=true;
    if(!simulstate->legal_actions.size())
        simulstate->get_legal_actions();
    while(1){
        if(simulstate->game_state==WIN||simulstate->game_state==DRAW){
            break;
        }
        if(!simulstate->legal_actions.size())
            simulstate->get_legal_actions();
        auto simulactions = simulstate->legal_actions;
        if(simulactions.size()!=0){
            simulstate=simulstate->next_state(simulactions[(rand()+d)%simulactions.size()]);
        }
        else{
            break;
        }
        step--;
    }
    if((simulstate->game_state==WIN||simulstate->game_state==DRAW)&&!simulstate->player){
        backpropagation(next,{1,1}); 
    }
    else{
        backpropagation(next,{0,1});
    }
    d++;
  }
  if(!state->legal_actions.size()){
    state->get_legal_actions();
  }
  float maxmin=(!state->player)?-9999999:9999999;
  Move ans=state->legal_actions[state->legal_actions.size()-1];
  for(auto i:root->child){
    if(i->n==0)continue;
    float val=i->win/i->n;
    printf("%d/%d %d,%d->%d,%d\n",i->win,i->n,i->m.first.first,i->m.first.second,i->m.second.first,i->m.second.second);
    if(!state->player){
        if(val>maxmin){
            maxmin=val;
            ans=i->m;
        }
    }
    else{
        if(val<maxmin){
            maxmin=val;
            ans=i->m;
        }
    }
  }printf("\n");
  return ans;
}


Move MCTS::get_move(State *s,int depth){
    return get(s,100000);
}