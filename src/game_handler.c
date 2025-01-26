#include <game_handler.h>
#include <stdio.h>

#define CROSS_TURN 1
#define CIRCLE_TURN 0

int GAME_STATE[9][10] = {0};

int available_subgrids[9] = {0}; 
int turn;

int GAME_init(){
  //TODO: generalize for nxm
  for(int i = 0; i<9; i++){
    for(int j = 0; j<10; j++){
      GAME_STATE[i][j] = -1;
    }
  }
  return 0;
}

int GAME_play_move(int turn, int grid_index, int sub_index){
  GAME_STATE[grid_index][sub_index] = turn;
  return 0;
}

int GAME_get_available_cells(int gi, int smi, int* indexes, int* n_indexes){
  //TODO: smi not needed
  //se la cella 'gi' è finita => restituisci gli indici di tutte quelle non finite
  int k = 0;
  if(GAME_STATE[gi][9] != -1){
    for(int i = 0; i<9; i++){
      if(GAME_STATE[i][9] == -1)
        indexes[k++] = i;
    }
    *n_indexes = k;
    return 1;
  }
  indexes[0] = gi;
  *n_indexes = 1;
  return 0;
}


void print(){
  for(int i = 0; i<9; i++){
    for(int j = 0; j<9; j++){
      printf("%d ",GAME_STATE[i][j]);
    }
    printf("\n");
  }
}
