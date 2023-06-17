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
Move MCTS::get_move(State *s,int depth){
    return get(s,1);
}
Move MCTS::get(State *state, int height){
  srand(height);
  if(!state->legal_actions.size())
    state->get_legal_actions();
  node*root=new node(state);
  int d=0;
  while (d<=height)
  {
    node* next=Select(root);
    if(next->s->game_state!=WIN){
        return {{2,1},{2,2}};
        expand(next);
        next=next->child[(rand()+height)%next->child.size()];
    }
    return {{1,1},{1,2}};
    int step=50;
    auto simulstate=new State(next->s->board);
    if(!simulstate->legal_actions.size())
        simulstate->get_legal_actions();
    while(step>=0){
        if(simulstate->game_state==WIN){
            break;
        }
        if(!simulstate->legal_actions.size())
            simulstate->get_legal_actions();
        auto simulactions = simulstate->legal_actions;
        simulstate=simulstate->next_state(simulactions[(rand()+step)%simulactions.size()]);
        step--;
    }
    if(simulstate->game_state==WIN&&!simulstate->player){
        backpropagation(next,{1,1}); 
    }
    else{
        backpropagation(next,{0,1});
    }
    delete simulstate;
    d++;
  }
  float maxmin=(!state->player)?-9999999:9999999;
  Move ans={{0,0},{0,0}};
  for(auto i:root->child){
    if(i->n==0)continue;
    float val=i->win/i->n;
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
  }
  //Del(root);
  return ans;
}

node* MCTS::Select(node *root){
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
float MCTS::calculate(node*root){
    if(root->n==0)return 99999999;
    if(root==nullptr)return 0.0;
    if(root->parent->n==0)return 0.0;
    int w=root->win;
    if(root->s->player)w=root->n-root->win;
    float l=log(root->parent->n);
    if(l<0)l=0;
    return w/root->n+pow(2,0.5)*pow(l/root->n,0.5);
}
void MCTS::expand(node*root){
    if(!root->s->legal_actions.size())
        root->s->get_legal_actions();
    for(auto i:root->s->legal_actions){
        auto temp=new node(root->s->next_state(i));
        temp->m=i;
        temp->parent=root;
        root->child.push_back(temp);
    }
}
void MCTS::backpropagation(node*root,std::pair<int,int> wn){
    if(root==nullptr)return;
    root->win+=wn.first;
    root->n+=wn.second;
    backpropagation(root->parent,wn);
}

void MCTS::Del(node*root){
    if(root->child.size()==0){
        return;
    }
    for(long unsigned int i=0;i<root->child.size();i++){
        Del(root->child[i]);
        delete root->child[i]->s;
        delete root->child[i];
    }
    delete root;
}