#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"






map<int,float> value_table={
  {0,0},
  {1,2},//兵
  {2,6},//城堡
  {3,7},//騎士
  {4,8},//主教
  {5,20},//皇后
  {6,10000000}//國王
};

/**
 * @brief evaluate the state
 * 
 * @return int 
 */

bool State::operator==(const State &rhs){
  if(board==rhs.board){
    return true;
  }

  return false;
  
}
bool Board::operator==(const Board &rhs){
  if(rhs.board==board){
    return true;
  }
  else{
    return false;
  }
}

int State::evaluate(){
  /*auto my_board = this->board.board[0];
  auto oppn_board = this->board.board[1];
  int my_score=0;
  int oppo_score=0;

  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((i==2&&j==2)||(i==3&&j==2)){
        if(my_board[i][j]!=0){
          my_score+=4;
        }
        if(oppn_board[i][j]!=0){
          oppo_score+=4;
        }
      }

      else if(((i==2||i==3)&&(j==1 || j==3)) || ((i==1 || i==4)&&(j==1 || j==2|| j==3))){
        if(my_board[i][j]!=0){
          my_score+=1;
        }
        if(oppn_board[i][j]!=0){
          oppo_score+=1;
        }

      }
      my_score+=value_table[my_board[i][j]];
      oppo_score+=value_table[oppn_board[i][j]];
      
        
    
    }
  }
  return my_score-oppo_score;



}*/
  // [TODO] design your own evaluation function

  
  map<int,float> value_table_white={
  {0,0},
  {1,2},//兵
  {2,6},//城堡
  {3,7},//騎士
  {4,8},//主教
  {5,20},//皇后
  {6,10000000}//國王
};

map<int,float> value_table_black={
  {0,0},
  {1,2},//兵
  {2,6},//馬
  {3,7},//主教
  {4,8},//車
  {5,20},//皇后
  {6,10000000}//國王
};
  int direction_bishop[4][2]={{1,1},{1,-1},{-1,-1},{1,1}};//主教
  int direction_rook[4][2]={{1,0},{-1,0},{0,-1},{0,1}};
  

  auto my_board = this->board.board[0];
  auto oppn_board = this->board.board[1];

  

  float my_score=0;
  float oppo_score=0;

  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((i==2&&j==2)||(i==3&&j==2)){
        if(my_board[i][j]!=0){
          my_score+=3;
        }
        if(oppn_board[i][j]!=0){
          oppo_score+=3;
        }
      }

      else if(((i==2||i==3)&&(j==1 || j==3)) || ((i==1 || i==4)&&(j==1 || j==2|| j==3))){
        if(my_board[i][j]!=0){
          my_score+=0.8;
        }
        if(oppn_board[i][j]!=0){
          oppo_score+=0.8;
        }

      }
      switch (my_board[i][j])
      {
      case 1:
        if(j==0 || j==BOARD_W){
          my_score-=0.5;
        }

        if(i==1){
          my_score +=3;
          if(i==0){
            my_score+=11;
          }
        }
        
        break;
      case 3:
        
        break;
      case 4:
        for(int i=0;i<4;i++){
          if((i+direction_bishop[i][0]>=BOARD_H || j+direction_bishop[i][1]>=BOARD_W) || my_board[i+direction_bishop[i][0]][j+direction_bishop[i][1]]!=0){
            
              my_score-=0.8;
            
          }
          
        }
        
        break;
      case 2:
        for(int i=0;i<4;i++){
          if((i+direction_rook[i][0]>=BOARD_H || j+direction_rook[i][1]>=BOARD_W)||my_board[i+direction_rook[i][0]][j+direction_rook[i][1]]!=0){
            
              my_score-=0.8;
            
          }
        }
        
        break;
      case 5:
        for(int i=0;i<4;i++){
          if((i+direction_rook[i][0]>=BOARD_H || j+direction_rook[i][1]>=BOARD_W)||my_board[i+direction_rook[i][0]][j+direction_rook[i][1]]!=0){
            
              my_score-=0.8;
            
          }
        }

        for(int i=0;i<4;i++){
          if((i+direction_bishop[i][0]>=BOARD_H || j+direction_bishop[i][1]>=BOARD_W) || my_board[i+direction_bishop[i][0]][j+direction_bishop[i][1]]!=0){
            
              my_score-=0.8;
            
          }
          
        }
        
        break;
      case 6:
          /*if(i==BOARD_H-1 && j==BOARD_W-1){
            if(my_board[BOARD_H-2][BOARD_W-1] !=0 && my_board[BOARD_H-1][BOARD_W-2]!=0){
              my_score-=2;
            }
            my_score+=1;
          }*/

          
      for(int i=0;i<4;i++){
          if(i+direction_bishop[i][0]<BOARD_H && j+direction_bishop[i][1]<BOARD_W){
            if(my_board[i+direction_bishop[i][0]][j+direction_bishop[i][1]]!=0){
              my_score+=1;
            }
          }
          
        }
        for(int i=0;i<4;i++){
          if(i+direction_rook[i][0]<BOARD_H && j+direction_rook[i][1]<BOARD_W){
            if(my_board[i+direction_rook[i][0]][j+direction_rook[i][1]]!=0){
              my_score+=1;
            }
          }
        }
        


        
        break;
      default:
        break;
      }

      
      switch (oppn_board[i][j])
      {
      case 1:
        if(j==0 || j==BOARD_W){
          oppo_score-=0.5;
        }

        if(i==BOARD_H-2){
          oppo_score +=3;
          if(i==BOARD_H-1){
            oppo_score+=11;
          }
        }
        
        break;
      case 3:
        
        break;
      case 4:
        for(int i=0;i<4;i++){
          if((i+direction_bishop[i][0]>=BOARD_H || j+direction_bishop[i][1]>=BOARD_W)||oppn_board[i+direction_bishop[i][0]][j+direction_bishop[i][1]]!=0){
            
              oppo_score-=0.8;
            
          }
          
        }
        
        break;
      case 2:
        for(int i=0;i<4;i++){
          if((i+direction_rook[i][0]>=BOARD_H || j+direction_rook[i][1]>=BOARD_W)||oppn_board[i+direction_rook[i][0]][j+direction_rook[i][1]]!=0){
            
              oppo_score-=0.8;
            
          }
        }
        
        break;
      case 5:
        for(int i=0;i<4;i++){
          if((i+direction_bishop[i][0]>=BOARD_H || j+direction_bishop[i][1]>=BOARD_W)||oppn_board[i+direction_bishop[i][0]][j+direction_bishop[i][1]]!=0){
            
              oppo_score-=0.8;
            
          }
          
        }
       for(int i=0;i<4;i++){
          if((i+direction_rook[i][0]>=BOARD_H || j+direction_rook[i][1]>=BOARD_W)||oppn_board[i+direction_rook[i][0]][j+direction_rook[i][1]]!=0){
            
              oppo_score-=0.8;
            
          }
        }
        
        break;
      case 6:
        for(int i=0;i<4;i++){
          if(i+direction_bishop[i][0]<BOARD_H && j+direction_bishop[i][1]<BOARD_W){
            if(oppn_board[i+direction_bishop[i][0]][j+direction_bishop[i][1]]!=0){
              oppo_score+=1;
            }
          }
          
        }
        for(int i=0;i<4;i++){
            if(i+direction_rook[i][0]<BOARD_H && j+direction_rook[i][1]<BOARD_W){
              if(oppn_board[i+direction_rook[i][0]][j+direction_rook[i][1]]!=0){
                oppo_score+=1;
              }
            }
          }

        
        
        break;
      default:
        break;
      }

      my_score+=value_table_white[my_board[i][j]];
      oppo_score+=value_table_black[oppn_board[i][j]];


    }
  }

  





  return my_score-oppo_score;
}





/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  //std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}