#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <utility>
#include <climits>

#include "../config.hpp"
using namespace std;


typedef std::pair<size_t, size_t> Point;
typedef std::pair<Point, Point> Move;





class Board{
  public:
    char board[2][BOARD_H][BOARD_W] = {{
      //white
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    }, {
      //black
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }};

    bool operator==(const Board &rhs);
};



enum GameState {
  UNKNOWN = 0,
  WIN,
  DRAW,
  NONE
};


class State{
  public:
    int value;
    //You may want to add more property for a state
    GameState game_state = UNKNOWN;
    Board board;
    int player = 0; //拿白色先手
    std::vector<Move> legal_actions;
    

    
    State(){};
    State(int player): player(player){};
    State(Board board): board(board){};
    State(Board board, int player): board(board), player(player){};
    
    int evaluate();
    State* next_state(Move move);
    void get_legal_actions();
    std::string encode_output();
    std::string encode_state();
    bool operator==(const State &rhs);

};

#endif