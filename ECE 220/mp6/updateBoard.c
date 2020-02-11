/* countLiveNeighbor checks the elements around the chosen location.
 * If the edge elements are out of bound, then they are ignored.
 *
 * updateBoard calls countLiveNeighbor to check the # of live neighbors,
 * then saves a copy to another array while modifying the current board
 * based on the previous copy.
 *
 * aliveStable first saves another copy of the original board to an array
 * calls updateBoard to modify the COPY of the board.
 * Finally, the function checks for any discrepancies.
 *
 *
 *
 *                       _oo0oo_
 *                      o8888888o
 *                      88" . "88
 *                      (| -_- |)
 *                      0\  =  /0
 *                    ___/`---'\___
 *                  .' \\|     |// '.
 *               / \\|||  :  |||// \
 *               / _||||| -:- |||||- \
 *               |   | \\\  -  /// |   |
 *               | \_|  ''\---/''  |_/ |
 *               \  .-\__  '-'  ___/-. /
 *             ___'. .'  /--.--\  `. .'___
 *          ."" '<  `.___\_<|>_/___.' >' "".
 *         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *         \  \ `_.   \_ __\ /__ _/   .-` /  /
 *     =====`-.____`.___ \_____/___.-`___.-'=====
 *                       `=---='
 *
 *
 *     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *           南无阿弥陀佛， 善哉， 善哉， 善善哉！
 *
 *
 *
 *
 *
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */


int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

int i;
int counter = 0;
int temp_row = row;
int temp_col = col;

for (i = 0; i < 9; i++){
  //First element Within range.
  if (temp_row - 1 == row + 2)
  continue;
  if (temp_row - 1 >= 0 && temp_row - 1 < boardRowSize && temp_col - 1 >= 0 && temp_col - 1 < boardColSize)
  {

    if (board[(temp_row - 1) * boardColSize + temp_col - 1] == 1 && (temp_row-1 != row || temp_col-1 != col)){

      if (temp_col - 1 == col + 1){ //If on the right edge, swtich to next row.

        counter = counter + 1;
        temp_row = temp_row + 1;
        temp_col = col;

        continue;
      }
      else{
      // Otherwise, switch to another column.
      counter = counter + 1;
      temp_col = temp_col + 1;

      continue;
      }
    }}

  if (temp_col - 1 == col + 1){
    temp_row = temp_row + 1;
    temp_col = col;
    //If on the right edge, swtich to next row.
  }

  else
  temp_col = temp_col + 1;
  //Otherwise, switch to the next column.

  }


 return counter;
      }
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {


 int j;
  int k;
  int m;
  int alive_count;//# of neighbors alive.
  int newArray[boardColSize * boardRowSize];//Creates a garbage with the same length.

  for (m = 0; m < boardColSize * boardRowSize; m++ ){
    newArray[m] = board[m];
    //Save a copy of the original board to newArray without modifying the original board.
  }

  for (j = 0; j < boardRowSize; j++){
    for (k = 0; k < boardColSize; k++){
      alive_count = countLiveNeighbor(newArray, boardRowSize, boardColSize, j, k);
      if (newArray[j * boardColSize + k] == 1){
        if (alive_count == 2 || alive_count == 3)
        {board[j * boardColSize + k] = 1; //Remains alive.
         }
        else
        {board[j * boardColSize + k] = 0; // Alive to dead.
        }
      }

      else
      {
        if(alive_count == 3)
        {board[j * boardColSize + k] = 1;
      } //Death to alive.
        else
        {board[j * boardColSize + k] = 0; //Remains dead.
         }
      }
    }

  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
   int Array1[boardRowSize * boardColSize];
   int a;
   int c;
  int flag = 1;
   for (a = 0; a < boardRowSize * boardColSize; a++){
      Array1[a] = board[a]; //copy board to Array1.
    }
    updateBoard(Array1, boardRowSize, boardColSize);
    //Change the board duplicate WITHOUT modifying the original board.
   for (c = 0; c < boardRowSize * boardColSize; c++){
      if (Array1[c] != board[c])
      flag = 0; //If one of the elements differ, flag set to zero.
      else
      continue;
    }
    return flag; //Flag presets to 1, if not modified, then board is unchanged.

 }
