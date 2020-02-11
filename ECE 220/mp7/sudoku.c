#include "sudoku.h"
#include <stdio.h>
#include <stdbool.h>
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.

/* These functions first check whether or not a given cell is filled.
 * Then the solve_sudoku function checks whether a guess is legal by conducting
 * recursive calls. If all cells are filled in successfully, we may return true.
 *
 *
 *
 *
 *
 *
 *
 */
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int j;
  for (j = 0; j < 9; j++){

  if (sudoku[i][j] == val)
  return 1;
  //If val already exists in this row, return 1.
  }
  // BEG TODO
  return 0;
  //Otherwise, return 0.
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  int k;
  for (k = 0; k < 9; k++)
  {
    if (sudoku[k][j] == val)
    return 1;
    //If val already exists in this row, return 1.
  }
  // BEG TODO
  return 0;
  // Otherwise, return 0.
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int k;
  int l;
  for (k = int(i/3)*3; k < int(i/3)*3+3; k ++){
      for (l = int(j/3)*3; l < int(j/3)*3+3; l ++){
        if (sudoku[k][l] == val)
        return 1; //cast the row # and the col # to locate which 3 by 3 matrix to check.
      }

    }

  // BEG TODO
  return 0;
  //If val does not exist in this 3 by 3 zone, return 0.
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  bool matrix = (0 == is_val_in_3x3_zone(val, i, j, sudoku)); //not filled in given matrix.
  bool col = (0 == is_val_in_col(val, j, sudoku)); // not filled in given column.
  bool row = (0 == is_val_in_row(val, i, sudoku)); // not filled in given row.
  if (matrix && col && row)
  return 1;
  // If none of the three checks hold, that means we may insert another number.
  // BEG TODO
  return 0;
  //Otherwise, return 0.
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
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
}

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
