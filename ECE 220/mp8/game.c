#include "game.h"
#include <stdbool.h>
#include <stdio.h>

/*
 * This program first makes the game board by initializing the content of the struct.
 * Then moves (or merges) tiles accordingly as users press w, a, s, d key.
 * Finally, the program checks the legality of the move by checking whether there is an empty slot
 * Or there are two neighboring cells that have the same value.
 *
 */



game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    (*mygame).score = 0;  //Initialize the game score to 0.
    (*mygame).rows = rows; //Set row to rows.
    (*mygame).cols = cols; //Set col to cols.
    int i, j;
    for (i = 0; i < rows; i++){
        for (j = 0; j< cols; j++){
          (*mygame).cells[i*cols+j] = -1; //set each element of the game to -1.
          }
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
  (*_cur_game_ptr) -> rows = new_rows;
  (*_cur_game_ptr) -> cols = new_cols;
  (*_cur_game_ptr) -> score = 0; //reset the original score to 0.
   int k, l;
   for (k = 0; k < new_rows; k++){
     for (l = 0; l < new_cols; l++){
       (*_cur_game_ptr) -> cells[k*new_cols+l] = -1; //Set each invididual element to -1.

     }
   }
   return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    bool err1 = row >= cur_game -> rows;
    bool err2 = row < 0;
    bool err3 = col >= cur_game -> cols;
    bool err4 = col < 0;
    bool errall = err1 || err2 || err3 || err4;
    //YOUR CODE STARTS HERE
    if (!errall) //If in bound, returns the pointer.
    return (cur_game -> cells) + row * (cur_game -> cols) + col;
    else  //If out of bound, returns nothing. (Will trigger seg fault.)
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE

  int temp = 0;
  int flag = 0;
  int dump = 0;
  int tar_row;
  int a,b,c,d,e;

  for (a = 0; a < cur_game -> cols; a++){
    for (b = 0; b < cur_game -> rows; b++){

      if (cur_game -> cells[ b * (cur_game -> cols) + a] != -1){
      //Find the first available current row.
      for (tar_row = 0; tar_row < b; tar_row ++){
      //Find the first available target row.
      if (cur_game -> cells[ tar_row * (cur_game -> cols) + a] == -1) break;

     }
     if (tar_row < b){
     flag = 1;  //If cells are altered, set flag to 1.
     cur_game -> cells [tar_row * (cur_game -> cols) + a] = cur_game -> cells [b * (cur_game -> cols) + a];
     cur_game -> cells [b * (cur_game -> cols) + a] = -1;
     }
    }
    }
  }
// Then merge cells.

  for (c = 0; c < cur_game -> cols; c++){

    for (d = 0; d < (cur_game -> rows) - 1; d++){
      if (cur_game -> cells[d * (cur_game -> cols) + c] == cur_game -> cells[(d+1) * (cur_game -> cols) + c] && cur_game -> cells[d * (cur_game -> cols) + c] != -1)
      {
      flag = 1;
      dump = cur_game -> cells[d * (cur_game -> cols) + c] * 2;
      cur_game -> score += dump;
      cur_game -> cells[d * (cur_game -> cols) + c ] = dump;

      for (e = d + 1; e < (cur_game -> rows) - 1 ; e++){
         //content changed, set flag to 1.
        temp = cur_game -> cells[(e+1) * (cur_game -> cols) + c];
        cur_game -> cells[e * (cur_game -> cols) + c] = temp; //merge up.
      }
      cur_game -> cells[((cur_game -> rows) - 1) * (cur_game -> cols) + c] = -1;


    }
    }
  }
  return flag; //If flag unchanged, return 0.

}

//the rest is similar, only the bounds, rows and cols are changed.
int move_s(game * cur_game) //slide down
{
  int temp = 0;
  int flag = 0;
  int dump = 0;
  int tar_row;
  int a,b,c,d,e;

  for (a = 0; a < cur_game -> cols; a++){
    for (b = cur_game -> rows - 1; b >= 0; b--){

      if (cur_game -> cells[ b * (cur_game -> cols) + a] != -1){
      //Find the first available current row.
      for (tar_row = cur_game -> rows - 1; tar_row > b; tar_row --){
      //Find the first available target row.
      if (cur_game -> cells[ tar_row * (cur_game -> cols) + a] == -1) break;

     }
     if (tar_row > b){
     flag = 1;
     cur_game -> cells [tar_row * (cur_game -> cols) + a] = cur_game -> cells [b * (cur_game -> cols) + a];
     cur_game -> cells [b * (cur_game -> cols) + a] = -1;
     }
    }
    }
  }
// Then merge cells.

  for (c = 0; c < cur_game -> cols; c++){

    for (d = cur_game -> rows - 1; d > 0; d--){
      if (cur_game -> cells[d * (cur_game -> cols) + c] == cur_game -> cells[(d - 1) * (cur_game -> cols) + c] && cur_game -> cells[d * (cur_game -> cols) + c] != -1)
      {
      flag = 1;
      dump = cur_game -> cells[d * (cur_game -> cols) + c] * 2;
      cur_game -> score += dump;
      cur_game -> cells[d * (cur_game -> cols) + c] = dump;

      for (e = d - 1; e >= 1 ; e--){
        temp = cur_game -> cells[(e - 1) * (cur_game -> cols) + c];
        cur_game -> cells[e * (cur_game -> cols) + c] = temp;
      }
      cur_game -> cells[0 * (cur_game -> cols) + c] = -1;

    }
    }
  }
  
  return flag;

};

int move_a(game * cur_game) //slide left
{

  int temp = 0;
  int flag = 0;
  int dump = 0;
  int tar_col;
  int a,b,c,d,e;

  for (a = 0; a < cur_game -> rows; a++){
    for (b = 0; b < cur_game -> cols; b++){

      if (cur_game -> cells[ a * (cur_game -> cols) + b] != -1){
      //Find the first available current col.
      for (tar_col = 0; tar_col < b; tar_col ++){
      //Find the first available target col.
      if (cur_game -> cells[ a * (cur_game -> cols) + tar_col] == -1) break;

     }
     if (tar_col < b){
     flag = 1;
     cur_game -> cells [a * (cur_game -> cols) + tar_col] = cur_game -> cells [a * (cur_game -> cols) + b];
     cur_game -> cells [a * (cur_game -> cols) + b] = -1;
     }
    }
    }
  }

// Then merge cells.


  for (c = 0; c < cur_game -> rows; c++){
    for (d = 0; d < (cur_game -> cols) - 1; d++){
      if (cur_game -> cells[c * (cur_game -> cols) + d] == cur_game -> cells[c * (cur_game -> cols) + d + 1] && cur_game -> cells[c * (cur_game -> cols) + d] != -1)
      {
      flag = 1;
      dump = cur_game -> cells[c * (cur_game -> cols) + d] * 2;
      cur_game -> score += dump;
      cur_game -> cells[c * (cur_game -> cols) + d] = dump;
      for (e = d + 1; e < (cur_game -> cols) - 1; e++){
        temp = cur_game -> cells[c * (cur_game -> cols) + (e+1)];
        cur_game -> cells[c * (cur_game -> cols) + e] = temp;
      }
      cur_game -> cells[ c * (cur_game -> cols) + ((cur_game -> cols) - 1)] = -1;

    }
    }
  }
      return flag;


};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

    int temp = 0;
    int flag = 0;
    int dump = 0;
    int tar_col;
    int a,b,c,d,e;

    for (a = 0; a < cur_game -> rows; a++){
      for (b = cur_game -> cols - 1; b >= 0; b--){

        if (cur_game -> cells[ a * (cur_game -> cols) + b] != -1){
        //Find the first available current row.
        for (tar_col = cur_game -> cols - 1; tar_col > b; tar_col --){
        //Find the first available target row.
        if (cur_game -> cells[ a * (cur_game -> cols) + tar_col] == -1) break;

       }
       if (tar_col > b){
       flag = 1;
       cur_game -> cells [a * (cur_game -> cols) + tar_col] = cur_game -> cells [a * (cur_game -> cols) + b];
       cur_game -> cells [a * (cur_game -> cols) + b] = -1;
       }
      }
      }
    }
  // Then merge cells.


    for (c = 0; c < cur_game -> rows; c++){

      for (d = cur_game -> cols - 1; d >= 0; d--){
        if (cur_game -> cells[c * (cur_game -> cols) + d] == cur_game -> cells[c * (cur_game -> cols) + d - 1] && cur_game -> cells[c * (cur_game -> cols) + d] != -1)
        {
        flag = 1;
        dump = cur_game -> cells[c * (cur_game -> cols) + d] * 2;
        cur_game -> score += dump;
        cur_game -> cells[c * (cur_game -> cols) + d ] = dump;

        for (e = d - 1; e >= 1 ; e--){

          temp = cur_game -> cells[c * (cur_game -> cols) + e - 1];
          cur_game -> cells[c * (cur_game -> cols) + e] = temp;
        }
        cur_game -> cells[c * (cur_game -> cols) + 0] = -1;

      }
      }
    }

    return flag;

};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE


    int i, j, k;
    for (i = 0; i < (cur_game -> cols)*(cur_game -> rows); i++){
      if (cur_game -> cells[i] == -1)
      return 1; // If there is any empty slot, return 1.
    }

    for (j = 0; j < (cur_game -> rows); j++){
      for (k = 1; k < (cur_game -> cols); k++){
        bool exp1 = cur_game -> cells[j * (cur_game -> cols) + (k-1) ] == cur_game -> cells[j * (cur_game -> cols) + k ] ;
        if (exp1) return 1; // Or if there are any pair of neighboring cells that have the same value, return 1.
      }

    }

    int l, m;
    for (l = 0; l < (cur_game -> cols); l++){
      for (m = 1; m < (cur_game -> rows); m++){
        bool exp2 = cur_game -> cells[(m - 1) * (cur_game -> cols) + l ] == cur_game -> cells[m * (cur_game -> cols) + l ] ;
        if (exp2) return 1;
      }
    }
    return 0; //else return 0.

}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance

	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance

	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  %d   ", *cell_ptr);

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
