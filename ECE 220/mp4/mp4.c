#include <stdlib.h>
#include <stdio.h>
/*
This program combines the given program with the given output. 
Then, the program breaks out of the for loop whenever a value is printed 
to prevent duplicates.
Happy Friday !!!!
*/
int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   	int a, b;
   	printf("Input two numbers: ");
   	scanf("%d %d", &a, &b);
   	if( a <= 0 || b <= 0 ){
     	printf("Inputs should be positive integers\n");
     	return 1;
   	}

   	if( a > b ){
     	printf("The first number should be smaller than or equal to the second number\n");
     	return 1;
   	}
   
      	print_semiprimes(a, b);


   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
	int i;
	for (i = 2; i <= number - 1; i ++){
        	if (number % i == 0){
                	return 0;}
	}
	return 1;
	
	
}
/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
	int n;
	int k;
	int d = 0;
	
	for (n = a; n <= b; n++){
		
		for (k = 2; k <= n-1; k++){
			
			int e = is_prime(k); // Check whether or not k is a prime number.
			int f = n/k;		
			int g = is_prime(f); // Check whether or not n/k is a prime number.
			if ( e == 1 && g == 1 && (n % k == 0))
			// Check whether or not k is a prime factor of n.
			{
							
					printf("%d ", n);
					d = 1;        
					break; //Break after a value is printed.    
}}}
	printf("\n");
	if (d == 1)				
		return 1;
	else 
		return 0;
			
			
}



