#include <stdio.h>
#include <stdlib.h>
/* This program first sets the first element to be 1.
   Then, multiply the coef by(n + 1 - i),
   The for loop will terminate after all numbers are printed.
   Partner: ziyaow2, hz13
 */
int main()
{
  int row;
  unsigned long coef;  
  int col;
  printf("Enter a row index: ");
  scanf("%d",&row);
  
 
	for (col = 0 ; col <= row; col ++)
	{ 
		if (col == 0)
		{	coef = 1;
		  printf("%lu ", coef);	//Print 1 for the first number.
		}
		else
		{
			coef = coef * (row + 1 - col) / col;
			printf("%lu ", coef); //print other characters otherwise
		}
		
	}
	printf("\n");
   return 0;
}
