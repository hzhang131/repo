//
//  main.c
//  something
//
//  Created by 张洪硕 on 2019/7/12.
//  Copyright © 2019 张洪硕. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "check.h"

int main()
{
    char choice;
    while(1){
        int check_bit;
        int temp_sum = 0;
        char your_number[18];
        while(1){
            printf("Please put in your ID number: \n");
            scanf("%s", your_number);
            int j, flag = 0;
            for (j = 0; j <= 16; j++){
                if (your_number[j] < '0' || your_number[j] > '9')
                    flag = 1;
            }
            if ((your_number[17] < '0' || your_number[17] > '9') && your_number[17] != 'X' ) flag = 1;
            if (flag == 0)
                flag = yearCheck(your_number[6],your_number[7], your_number[8], your_number[9] ) || dateCheck(your_number[10], your_number[11], your_number[12], your_number[13], your_number[6], your_number[7], your_number[8], your_number[9]) || ProvinceCheck(your_number[0], your_number[1]);
            if  (flag == 0 ) break;
            printf("Your input is invalid, please try again!\n");
            if (yearCheck(your_number[6],your_number[7], your_number[8], your_number[9] ) || dateCheck(your_number[10], your_number[11], your_number[12], your_number[13], your_number[6], your_number[7], your_number[8], your_number[9]))
                printf("Birthdate is not valid.\n");
            if (ProvinceCheck(your_number[0], your_number[1]) == 1)
                printf("Province is not valid.\n");
        }
        
        
        //solve for temp_sum
        const int length = 16;
        int i;
        for (i = 0; i<= length; i++){
            temp_sum +=  (CtoI(your_number[i])) * (((int) pow(2, 18-i-1)) % 11);
        }
        if (CtoI(your_number[17]) > 0 && CtoI(your_number[17]) < 10)
            check_bit = CtoI(your_number[17]);
        else
            check_bit = 10;
        if (check_bit == (12 - (temp_sum % 11 )) % 11){
            printf("This ID number is valid.\n" );
            printf("The owner of this ID is from %s\n", prov_name);
        }
        else
            printf("This ID number is not valid.\n");
        while (1){
            printf("Would you like to do another ID number check?\n");
            printf("Type y to continue, type q to quit.\n");
            
            scanf("%s", &choice);
            if (choice == 'q' || choice == 'Q') break;
            else if (choice == 'Y' || choice == 'y') {
                printf("\n");
                break;
                
            }
        }
        if (choice == 'q' || choice == 'Q') break;
    }
    return 0;
    
}
