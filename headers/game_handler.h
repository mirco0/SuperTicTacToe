#ifndef GAME_HANDLER
#define GAME_HANDLER


int GAME_init();
void get_GAME_STATE(int a[9][10]);
int GAME_play_move(int index, int sub_index);
int GAME_get_available_cells(int sub_index, int* indexes, int* n_indexes);
int GAME_get_turn();
int GAME_validate_move(int index,int sub_index);

#endif 
