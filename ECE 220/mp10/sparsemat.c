#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* Fuck this MP.
 * This MP is really complicated and unnecessarily hard.
 * load_tuples translates the tuple list into a sorted linked list.
 * gv_tuples gives the entry value from a given coordinate.
 * set-tuples throws a random node that I have to sort it out myself.
 * save_tuples translates a given linked list to a text file.
 * add_tuples adds two matrices together
 * mult_tuples multiplies two matrices together.
 * Partner: hz13, nayund2
*/
void insertNode(int row, int col, double value, sp_tuples_node** head, sp_tuples* mat);
void deleteNode(int row, int col, double value, sp_tuples_node** head, sp_tuples* mat);

sp_tuples * load_tuples(char* input_file)
{
    /*First we malloc a tuple list */
    sp_tuples* list = (sp_tuples*) malloc (sizeof(sp_tuples));
    list -> tuples_head = NULL;
    /*Then open the txt file */
    FILE* something = fopen(input_file, "r");
    int rows, cols;
    /* Load row number and col number */
    fscanf(something, "%d %d", &rows, &cols);
    list -> m = rows;
    list -> n = cols;
    /*Now read the coordinates and load the head struct.*/
    while (1){
    sp_tuples_node* head = list -> tuples_head;
    int row, col;
    double val;
    int input_no = fscanf(something, "%d %d %lf", &row, &col, &val);
    /*If we cannot read any data from the file, we reach the EOF.*/
    if (input_no == EOF) break;
    /*If there is a zero entry, we may skip this line and read next line.*/
    /*Initialize the head node and load data into it*/
    /*Try to insert node and delete node */
    insertNode(row, col, val, &head, list);
    /*After insertion and deletion, we may move the current ptr */
    }
    return list;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node* head = mat_t -> tuples_head;
    while (head != NULL){
        int i = head -> row;
        int j = head -> col;
        if (i == row && j == col) break;
        head = head -> next;
    }

    return head -> value;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node* head = mat_t -> tuples_head;
    while (head != NULL){
      double k = head -> value;
      if (k == 0) {
        int i = head -> row;
        int j = head -> col;
        deleteNode(i, j, value, &head, mat_t);
        continue;
    }
      if (head -> row == row && head -> col == col && head -> value != value) {
      head -> value = value;
      head = head -> next;
      mat_t -> nz = mat_t -> nz + 1;
      continue;
    }
    /* In all other cases... */
    mat_t -> nz = mat_t -> nz + 1;
    head = head -> next;
  }
    /* The entry does not exist */
    insertNode(row, col, value, &(mat_t -> tuples_head), mat_t);
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  if (mat_t == NULL) return;
  FILE* something = fopen(file_name, "w");
  sp_tuples_node* head = mat_t -> tuples_head;
  if (head == NULL) return;
  /* Traverse the linked list */
  int rows = mat_t -> m;
  int cols = mat_t -> n;
  fprintf(something, "%d %d\n", rows, cols);
  while (head != NULL)
	{
    int row = head -> row;
    int col = head -> col;
    double value = head -> value;
    fprintf(something, "%d %d %lf\n",row, col, value);
    head = head -> next;
  }
  return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  /* Initialize the sum Matrix matC */
  /*Check whether addition is possible, if not possible, return NULL */
  if (matA -> m != matB -> m || matA -> n != matB -> n) return NULL;
  sp_tuples* matC = (sp_tuples*) malloc(sizeof(sp_tuples));
  matC -> tuples_head = NULL;
  matC -> m = matA -> m;
  matC -> n = matA -> n;
  matC -> nz = 0;
  //matC -> tuples_head = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
  matC -> tuples_head = NULL;
  sp_tuples_node* A_head = matA -> tuples_head;
  sp_tuples_node* C_head = matC -> tuples_head;
  while (A_head != NULL){
    /* If value is 0, skip the iteration. */
    if (A_head -> value == 0){
      A_head = A_head -> next;
      continue;
    }
    /* Otherwise, move elements from C to A. */
    insertNode(A_head -> row, A_head -> col, A_head -> value, &(C_head), matC);
    A_head = A_head -> next;
    //C_head = C_head -> next;
  }

  sp_tuples_node* B_head = matB -> tuples_head;
  while (B_head != NULL){
    sp_tuples_node* C_head = matC -> tuples_head;
    /*if value is 0, skip the iteration. */
    if (B_head -> value == 0){
      B_head = B_head -> next;
      continue;
    }
      while (C_head != NULL){
        /* Add the values together if coordinate exists in both matrices. */
        if (B_head -> row == C_head -> row && B_head -> col == C_head -> col){
        C_head -> value = C_head -> value + B_head -> value;
        break;
      }
      C_head = C_head -> next;
    }
    /* If it does not exist, we may insert into the matrix. */
    insertNode(B_head -> row, B_head -> col, B_head -> value, &(matC -> tuples_head), matC);
    /* traverse to the next node. */
    B_head = B_head -> next;
  }

	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
    /* Initialize the product matrix matC */
    if (matA -> n != matB -> m) return NULL;
    sp_tuples* matC = (sp_tuples*) malloc(sizeof(sp_tuples));
    matC -> tuples_head = NULL;
    /* Check whether the matrix multiplication is possible. */
    /* Set matC to be a mA by nB matrix. */
    matC -> n = matB -> n;
    matC -> m = matA -> m;
    sp_tuples_node* A_head = matA -> tuples_head;

    sp_tuples_node* C_head = matC -> tuples_head;
    while (A_head != NULL){
      if (A_head -> value == 0){
        A_head = A_head -> next;
        continue;
      }
      int iA = A_head -> row;
      int jA = A_head -> col;
      sp_tuples_node* B_head = matB -> tuples_head;

      while (B_head != NULL){

        if (B_head -> value == 0){
          B_head = B_head -> next;
          continue;
        }
        int iB = B_head -> row;
        int jB = B_head -> col;
        if (iB == jA){
          double value = gv_tuples(matA, iA, jA) * gv_tuples(matB, iB, jB);
          //printf("I am here!!!!!!!!!!!!!!!");
          sp_tuples_node * headC = matC -> tuples_head;
          for(;headC; headC = headC->next){
            if(headC->row == iA && headC->col == jB){
              headC->value += value;
              break;
            }
          }
          if(!headC)insertNode(iA,jB,value, &C_head, matC);
        }
        B_head = B_head -> next;
      }

      A_head = A_head -> next;
    }
    return matC;

}


void destroy_tuples(sp_tuples * mat_t){
    if (mat_t == NULL) return;
    sp_tuples_node* head = mat_t -> tuples_head;
    sp_tuples_node* temp;
    while (head != NULL){
      temp = head;
      head = temp -> next;
      free(temp);
    }
    return;
}


/* Below are the list of helper functions I wrote */
void insertNode(int row, int col, double value, sp_tuples_node** head, sp_tuples * mat){

    sp_tuples_node** new_head = &(mat -> tuples_head);
    while((*new_head )!= NULL){
      if ((*new_head) -> row == row && (*new_head) -> col == col){
        if(value == 0){
          sp_tuples_node* temp = *new_head;
          *new_head = temp -> next;
          free(temp);
          mat->nz--;
          return;
        }
        break;
      }
      new_head = &((*new_head) -> next);
    }
    if (value == 0) return;
  /* Acknowledgement: Algorithm suggested by Professor Yih-Chun Hu */
  while (*head != NULL){
    /* Do not insert (terminate the helper function) if there is a duplicate. */
    if ((*head) -> row == row && (*head) -> col == col) return;
    /*if inserted row smaller than head row, insert at head. */
    if ((*head) -> row > row ) break;
    /* if inserted row == target row, but inserted col < head col, insert at head as well. */
    if ((*head) -> row == row && (*head) -> col > col) break;
    head = &((*head) -> next);
  }
  /* traverse the linked list to the right. */
  sp_tuples_node* temp = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
  temp -> row = row;
  temp -> col = col;
  temp -> value = value;
  temp -> next = *head;
  *head = temp;
  if(temp->next == mat->tuples_head) mat->tuples_head = temp;
  if(!mat->tuples_head)mat->tuples_head = temp;
  mat -> nz = mat -> nz + 1;
  return;
}
void deleteNode(int row, int col, double value, sp_tuples_node** head, sp_tuples* mat){
    if (*head == NULL) return;
    while(*head != NULL){
      if ((*head) -> row == row && (*head) -> col == col && (*head) -> value == value) break;
      *head = (*head) -> next;
    }
    sp_tuples_node* temp = *head;
    *head = temp -> next;
    free(temp);
    mat -> nz = mat -> nz - 1;
    return;
}
