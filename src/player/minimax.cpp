#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <cassert>
#include <cstdint>


#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/minimax.hpp"

//
//在makefile的時候找到player random.cpp會去對policy裡面同名的cpp
State* root;

/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) {//可以參考這個去改
  // Keep updating the output until getting killed.
  int depth=1;
  while(true) {
    depth+=1;
    
    //int want_state=Minimax::get_move(root, 4, 1-root->player);
    //Move move=Minimax::get_want_move(want_state,root);
    Move move=Minimax::get_move(root,depth,root->player);
    
    
    

    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    
  }
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);
  //輸出現在棋盤狀況

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
