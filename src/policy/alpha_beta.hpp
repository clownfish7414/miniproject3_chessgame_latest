#pragma once
#include "../state/state.hpp"
#include <set>



struct bigstate{
    int heuristic;
    State* state;

    bigstate(int heuristic,State* state):heuristic(heuristic),state(state){};

};



/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alpha_Beta{
public:
  //static int get_move(State *state, int depth,int alpha,int beta,bool player);
  //static Move get_want_move(int want_state,State*root);
  static int alpha_beta(State *state, int depth,int alpha,int beta,bool player);
  static Move get_move(State *state,int depth,int player);
};