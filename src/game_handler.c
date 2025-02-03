#include "game_input.h"
#include <game_handler.h>


#define CROSS 1
#define CIRCLE 0

#define EMPTY_CELL -1
#define TIE -2

int GAME_STATE[9][10] = {0};

//TODO: REMOVE??
int available_subgrids[9] = {0};
int turn = CROSS;
int last_sub_index = -1;

int GAME_init(){
  //TODO: generalize for nxm
  for(int i = 0; i<9; i++){
    for(int j = 0; j<10; j++){
      GAME_STATE[i][j] = EMPTY_CELL;
    }
  }
  return 0;
}

void check_update_board(int index){

  int empty = 0;
  for(int i = 0; i<9; i++){
    if(GAME_STATE[index][i] == EMPTY_CELL){
      empty = 1;
      break;
    }
  }
  if(!empty)
    GAME_STATE[index][9] = TIE;
  
  for(int i = 0; i<9; i+=3){
    if(GAME_STATE[index][i] == EMPTY_CELL) continue;
    if(GAME_STATE[index][i] == GAME_STATE[index][i+1] && GAME_STATE[index][i+1] == GAME_STATE[index][i+2]){
      GAME_STATE[index][9] = GAME_STATE[index][i];
      return;
    }
  }
  
  for(int i = 0; i<3; i++){
    if(GAME_STATE[index][i] == EMPTY_CELL) continue;
    if(GAME_STATE[index][i] == GAME_STATE[index][i+3] && GAME_STATE[index][i+3] == GAME_STATE[index][i+6]){
      GAME_STATE[index][9] = GAME_STATE[index][i];
      return;
    }
  }
  
  if( GAME_STATE[index][2] == GAME_STATE[index][4] && GAME_STATE[index][4] == GAME_STATE[index][6]){
    GAME_STATE[index][9] = GAME_STATE[index][2];
    return;
  }


  if( GAME_STATE[index][0] == GAME_STATE[index][4] && GAME_STATE[index][4] == GAME_STATE[index][8]){
    GAME_STATE[index][9] = GAME_STATE[index][0];
    return;
  }
  
}

int GAME_play_move(int index, int sub_index){
  if(GAME_validate_move(index,sub_index)){
    GAME_STATE[index][sub_index] = turn;
    turn = !turn;
    last_sub_index = sub_index;
    check_update_board(index);
    
    if(GAME_STATE[sub_index][9] != EMPTY_CELL){
      last_sub_index = -1;
    }

    return 1;
  }
  return 0;

}

void get_GAME_STATE(int a[9][10]){
  for(int i = 0; i<9; i++){
    for(int j = 0; j<10; j++){
      a[i][j] = GAME_STATE[i][j];
    }
  }
}

int GAME_get_available_cells(int sub_index, int* indexes, int* n_indexes){
  indexes = available_subgrids;
  SDL_Point new_pos = INPUT_index_nmatrix(sub_index,3);
  int new_index = INPUT_nmatrix_index(new_pos.x,new_pos.y,3);
  
  if(GAME_STATE[new_index][9] == -1){
    indexes[0] = new_index;
    *n_indexes = 1;
    return 1;
  }

  int k = 0;
  for(int i = 0; i<9; i++){
    if(GAME_STATE[i][9] == -1){
      indexes[k++] = i;
    }
  }
  *n_indexes = k;
  return 0;
}

int GAME_get_turn(){
  return turn;
}

int GAME_validate_move(int index, int sub_index){
  if(last_sub_index != index && last_sub_index != -1) return 0;
  if(GAME_STATE[index][sub_index] != EMPTY_CELL) return 0;
  if(GAME_STATE[index][9] >= 0) return 0;
  return 1;
}
