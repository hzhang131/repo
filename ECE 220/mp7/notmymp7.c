#include "sudoku.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
/* INTRO PARA
The program use backtracking recursion to solve sudokus.
I implement 5 functions
The first function is_val_in_row checked if there are repeated values
from 1 to 9 in the same row;
The second function is_val_in_col checked the same thing within the
same columns;
The third function is_val_in_3x3_zone checked the same thing within
a 3x3 scope;
The fourth function is_val_valid check if any repeated value within
three different kind of scopes

*/
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int k = 0;
  for(k=0; k<9; k++){
    if(sudoku[i][k] == val)
    return 1;
  }
  // BEG TODO

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  int q = 0;
  for(q=0; q<9; q++){
    if(sudoku[q][j] == val)
    return 1;
  }
  // BEG TODO

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int c = int(i/3);
  int d = int(j/3);
  int x;
  int y;
  for(x=c*3; x<c*3+3; x++){
    for(y=d*3; y<d*3+3; y++){
      if(sudoku[x][y] == val) return 1;

    }
  }
  // BEG TODO

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val, i, sudoku) == 0 && is_val_in_col(val, j, sudoku)== 0 && is_val_in_3x3_zone(val, i, j, sudoku) == 0)
  return 1;


  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int r ;//= 0;
    int w ;//= 0;

  for(r=0; r<9; r++){
    for(w=0; w<9; w++){

      printf("%d\n", w);
    if(!sudoku[r][w])
      break;
    }
    if(!sudoku[r][w])
      break;
  }
  if(r*9+w == 80)
    return 1;
  else {
    for (int num=1; num<=9; num++){
      printf("%d, %d\n", r, w);
      if(is_val_valid(num, r, w, sudoku)){
	sudoku[r][w] = num;
	if(solve_sudoku(sudoku)){
	  return 1;
	}
      }
    }
    sudoku[r][w] = 0;
  }
  return 0;
  // END TODO.
}

/*
int solve_sudoku(int sudoku[9][9]) {
  int i, j, num, k, l;
  int flag = 1;
  // BEG TODO.
  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (sudoku[i][j] == 0 && flag == 1)
      {flag = 0;
      k = i;
      l = j;} //Stop checking if we find an unfilled cell.
      }
    }


  if (flag == 1)
  return 1;//Base case: returns true if all cells are filled.

  if (sudoku[k][l] == 0)
      {
        for (num = 1; num <= 9; num++){
          if (is_val_valid(num, k, l, sudoku)){
            sudoku[k][l] = num;
            // If it is valid, we may (temporarily) fill in the number.
            if (solve_sudoku(sudoku)) return 1;
              // Calls recursively to see whether filling in more cells (legally) will completely fill in the board.
            sudoku[k][l] = 0;
            //If not, that means the guess is illegal.

        }
        }
      }


  return 0;
  // END TODO.
} */


// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
