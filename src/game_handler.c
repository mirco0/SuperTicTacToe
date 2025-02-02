#include <game_handler.h>

#define CROSS_TURN 1
#define CIRCLE_TURN 0

int GAME_STATE[9][10] = {0};

int available_subgrids[9] = {0}; 
int turn = 0;

int GAME_init(){
  //TODO: generalize for nxm
  for(int i = 0; i<9; i++){
    for(int j = 0; j<10; j++){
      GAME_STATE[i][j] = -1;
    }
  }
  return 0;
}
void check_update_board(int index){
  for(int i = 0; i<9; i+=3){
    if( GAME_STATE[index][i] == GAME_STATE[index][i+1] && GAME_STATE[index][i+1] == GAME_STATE[index][i+2]){
      GAME_STATE[index][9] = GAME_STATE[index][i];
      return;
    }
  }
  
  for(int i = 0; i<3; i++){
    if( GAME_STATE[index][i] == GAME_STATE[index][i+3] && GAME_STATE[index][i+3] == GAME_STATE[index][i+6]){
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
    check_update_board(index);
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

int GAME_get_available_cells(int index, int* indexes, int* n_indexes){
  int k = 0;
  if(GAME_STATE[index][9] != -1){
    for(int i = 0; i<9; i++){
      if(GAME_STATE[i][9] == -1)
        indexes[k++] = i;
    }
    *n_indexes = k;
    return 1;
  }
  indexes[0] = index;
  *n_indexes = 1;
  return 0;
}

int GAME_get_turn(){
  return turn;
}

int GAME_validate_move(int index, int sub_index){
  if(GAME_STATE[index][sub_index] != -1) return 0;
  if(GAME_STATE[index][9] != -1) return 0;
  return 1;
}
