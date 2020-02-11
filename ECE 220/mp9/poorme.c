#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{  // Your code here. Make sure to replace following line with your own code.
    maze_t* maze = (maze_t* ) malloc(sizeof(maze_t));
    FILE *in_file = fopen(fileName, "r"); //"Read" file to in_file.

    fscanf(in_file, "%d %d", &(maze -> height), &(maze -> width)); //Reads the row and col info from file.
    int rows = maze -> height;
    int cols = maze -> width;
    maze -> cells = (char** ) malloc(rows * sizeof(char*));
    int i, j;
    for (i = 0; i < rows; i++){
      maze -> cells[i] = (char* ) malloc(cols * sizeof(char)); //Initialize to 2d array.
    }

    char temp;

    for (i = 0; i < rows; i++){
      for (j = 0; j < cols; j++){
        fscanf(in_file, "%c", &temp); //Put elements into the array.
        if (temp == '\n') fscanf(in_file, "%c", &temp);
        if (feof(in_file) == temp) break;
        if (temp == 'S') {
          maze-> startRow = i;
          maze -> startColumn = j;
        }
        if (temp == 'E'){
          maze -> endRow = i;
          maze -> endColumn = j;
        }
          maze -> cells[i][j] = temp;
      }
    }

    fclose(in_file);
    return maze;


}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.

   int i;
    int rows = maze -> height;
    for (i = 0; i < rows; i++){
      free(maze -> cells[i]);
    }
    free(maze -> cells);
    free(maze);
    return;

}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
   int i, j;
    for (i = 0; i < maze -> height; i++){
      for (j = 0; j < maze -> width; j++){
        printf("%c", maze -> cells[i][j]);
      }
      printf("\n");
    }
  return;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

    return 0;
}
