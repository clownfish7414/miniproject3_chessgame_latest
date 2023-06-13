#include <cstdlib>

#include "../state/state.hpp"
#include "./random.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random::get_move(State *state, int depth){
  if(!state->legal_actions.size())//沒有任何棋步可以走，通常不會
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  return actions[(rand()+depth)%actions.size()];
}