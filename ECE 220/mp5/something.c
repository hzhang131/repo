//This program generate four random number between 1 and 8 and the user has 12 chances to guess the right number and order. It will show perfect match and misplace match after each time user enters a list of number
//partner:hz13,xiaobai2



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"




static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


int
set_seed (const char seed_str[])
//initialize the seed and call random function, if the seed is includes something else except number, show invalid message
{

	unsigned int seed;
	char post[2];
	int flag;
	flag = sscanf(seed_str,"%d%1s", &seed, post);
	
	if (flag == 1){
	srand(seed);
	return 1;
} else {

	printf("set_seed: invalid seed\n");
	return 0;
} 

}



void
start_game (int* one, int* two, int* three, int* four)
//points the solution to right memory address and assign random number between 1 to 8 to each solution, and initialize guess number
{
    
  void srand(unsigned int seed);
  int rand();
    //assign number to each memory address
    solution1 = *one = rand()%8+1;
    solution2 = *two = rand()%8+1;
    solution3 = *three = rand()%8+1;
    solution4 = *four = rand()%8+1;
    guess_number = 1;
}


int
make_guess (const char guess_str[], int* one, int* two, 
 int* three, int* four)
//main function which checks how many perfect matches and mismatches exists in the entered list of number. Output how many perfect matches and misplace matches are entered
{

  int a= solution1;
  int b = solution2;
  int c= solution3;
  int d = solution4;
  int x,y,w,z,length,pm = 0,mm = 0;
    char post[2];
    length =  sscanf(guess_str,"%d%d%d%d%1s",&w, &x, &y, &z, post);
    if(w <1 || x <1 || y <1|| z<1 ||w>8 ||x> 8|| y> 8||z> 8|| length!=4){//check the number range is correct
      printf("make_guess:Invalid guess");
      return 0;
 }  //main function checks perfect matches and mismatches
    if(w == a){
      pm = pm + 1;
      w = 0;
      a = -1;
    }
    if(x == b){
      pm = pm + 1;
      x = 0;
      b = -1;
    }
    if(y == c){
      pm = pm + 1;
      y = 0;
      c = -1;
    }
    if(z == d){
      pm = pm + 1;
      z = 0;
      d = -1;
    }
    if(w == b){
      mm = mm + 1;
      w = 0;
      b = -1;
    }
    if(w == c){
      mm = mm + 1;
      w = 0;
      c = -1;
    }
    if(w == d){
      mm = mm + 1;
      w = 0;
      d = -1;
    }
    if(x == a){
      mm = mm + 1;
      x = 0;
      a = -1;
    }
    if(x == c){
      mm = mm + 1;
      x = 0;
      c = -1;
    }
    if(x == d){
      mm = mm + 1;
      x = 0;
      d = -1;
    }
    if(y == a){
      mm = mm + 1;
      y= 0;
      a = -1;
    }
    if(y == b){
      mm = mm + 1;
      y= 0;
      b= -1;
    }
    if(y == d){
      mm = mm + 1;
      y= 0;
      d = -1;
    }
     if(z==a){
      mm = mm + 1;
      z=0;
      a = -1;
    }
    if(z==b){
      mm = mm + 1;
      z=0;
      b= -1;
    }
    if(z==c){
      mm = mm + 1;
      z=0;
      c= -1;
    }
  
   printf("With guess %d, you have %d perfect matches and %d misplaced matches\n", guess_number, pm, mm);
  //output message and increment guess counter
   guess_number++;
	
    
    return 1;
}


