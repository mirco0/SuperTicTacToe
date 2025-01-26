#ifndef GAME_HANDLER
#define GAME_HANDLER

int GAME_play_move(int turn, int grid_index, int sub_index);
int GAME_get_available_cells(int gi, int smi, int* indexes, int* n_indexes);

void print();

#endif 
