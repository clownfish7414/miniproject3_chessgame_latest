#pragma once
#include "../state/state.hpp"

struct bigstate{
    int heuristic;
    State* state;

    bigstate(int heuristic,State* state):heuristic(heuristic),state(state){};

};
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  //static int get_move(State *state, int depth,bool player);
  //static Move get_want_move(int want_state,State*root);
  static Move get_move(State *state,int depth,int player);
  static int minimax(State *state,int depth, bool player);
};