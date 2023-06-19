#include <cstdlib>
#include <climits>
#include <algorithm>
#include "../state/state.hpp"
#include "./alpha_beta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

/*struct bigstate{
    int heuristic;
    Move currentmove;

    bigstate(int heuristic,Move currentmove):heuristic(heuristic),currentmove(currentmove){};

};*/


Move Alpha_Beta::get_move(State*root,int depth,int player){
    if(!root->legal_actions.size())//沒有任何棋步可以走，通常不會
    root->get_legal_actions();
  
    auto actions = root->legal_actions;
    int min_value=INT_MAX;
    int max_value=INT_MIN;
    Move next_move;



    for(auto item:actions){
        if(!player){
            int value=alpha_beta(root->next_state(item),depth-1,INT_MIN,INT_MAX, 0);      
            max_value=max(max_value,value);
            if(max_value==value){
                next_move=item;
            }    
            

        }
        else{
            int value=alpha_beta(root->next_state(item),depth-1,INT_MIN,INT_MAX, 1);      
            min_value=min(min_value,value);
            if(min_value==value){
                next_move=item;
            }    

        }
        
    }
    return next_move;
    
}


int Alpha_Beta::alpha_beta(State *state, int depth,int alpha,int beta,bool maxplayer){
  
    if(!state->legal_actions.size())//沒有任何棋步可以走，通常不會
    state->get_legal_actions();
  
  auto actions = state->legal_actions;


  if(depth==0 || actions.empty()){
    state->value = state->evaluate();
    return state->value;
  }

  


  if(maxplayer){
    int maxvalue=-INT_MAX;
    
    for(auto item:actions){
        int value=alpha_beta(state->next_state(item), depth-1,alpha,beta,false);
        maxvalue=std::max(maxvalue,value);
        alpha=max(alpha,value);
        if(beta<=alpha){
            break;
        }   
    }
    state->value=maxvalue;
    /*if(depth==6){
        return state->evaluate();
        
    }*/

    return maxvalue;
  }

  else{
    int minvalue=INT_MAX;
    
    for(auto item:actions){
        int value=alpha_beta(state->next_state(item), depth-1,alpha,beta,true);
        minvalue=std::min(minvalue,value);
        beta=min(beta,value);
        if(beta<=alpha){
            break;
        }   
    }
    state->value=minvalue;
    /*if(depth==6){
        return state->evaluate();
    }*/
    return minvalue;
  }

  
  
}

/*Move Alpha_Beta::get_want_move(int want_state,State*root){
    for(auto item: root->legal_actions){
        if(want_state==root->next_state(item)->evaluate()){
            return item;
        }
    }
    //return root->legal_actions[0];

}*/






/*==========================================================*/

/*bigstate Minimax::get_move(State *state, int depth,int player){
  
  if(depth==0 || state->game_state==WIN || state->game_state==DRAW){
    return bigstate(state->evaluate(),state);
  }
  
  
  
  if(!state->legal_actions.size())//沒有任何棋步可以走，通常不會
    state->get_legal_actions();
  
  auto actions = state->legal_actions;


  if(player){
    bigstate maxvalue(-1000,state);
    int bigvalue=-1000;
    for(auto item:actions){
        bigstate value=get_move(state->next_state(item), depth-1,0);
        bigvalue=max(maxvalue.heuristic,value.heuristic);
        if(bigvalue==maxvalue.heuristic){

            return maxvalue;
        }
        else{
            maxvalue=value;
            return maxvalue;
        }

        
    }
  }

  else{
    bigstate minvalue(1000,state);
    int smallvalue=1000;
    for(auto item:actions){
        bigstate value=get_move(state->next_state(item), depth-1,1);
        smallvalue=min(minvalue.heuristic,value.heuristic);
        if(smallvalue==minvalue.heuristic){
            return minvalue;
        }
        else{
           minvalue=value;
            return minvalue;
        }   
    }
  }

  return bigstate(0,state);
  
}*/