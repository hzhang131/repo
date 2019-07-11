//
//  main.c
//  my lazy work
//
//  Created by 张洪硕 on 2019/7/10.
//  Copyright © 2019 张洪硕. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <time.h>
int CtoI(char a){
    int con_val = (int) a - (int) '0';
    return con_val;
}

int yearCheck(char a, char b, char c, char d){
    time_t format = time(NULL);
    struct tm *something = localtime(&format);
    if (CtoI(a)*1000 + CtoI(b)*100 + CtoI(c)*10 + CtoI(d) > 1900 + (something -> tm_year))
        return 1;
    else
        return 0;
}

int dateCheck(char a, char b, char c, char d, char e, char f, char g, char h){
    //check same year impossible date.
    time_t format = time(NULL);
    struct tm *something = localtime(&format);
    if (CtoI(e)*1000 + CtoI(f)*100 + CtoI(g)*10 + CtoI(h) == 1900 + (something -> tm_year) && CtoI(a)* 10 + CtoI(b) > something -> tm_mon) return 1;
    if (CtoI(e)*1000 + CtoI(f)*100 + CtoI(g)*10 + CtoI(h) == 1900 + (something -> tm_year) && CtoI(a)* 10 + CtoI(b) == something -> tm_mon && CtoI(c)*10 + CtoI(d) > something -> tm_mday) return 1;
    //check legal month.
    if (CtoI(a)* 10 + CtoI(b) > 12 && CtoI(a)*10 + CtoI(b) <= 0) return 1;
    //check legal day.
    switch(CtoI(a)* 10 + CtoI(b)){
        case 2: if (CtoI(c)*10 + CtoI(d) <= 28 && CtoI(c)*10 + CtoI(d) >= 1)
            return 0;
        else if (CtoI(c)*10 + CtoI(d) == 29 && (CtoI(a)*1000 + CtoI(b)*100 + CtoI(c)*10 + CtoI(d)) % 4 == 0)
            return 0;
        else return 1;
        case 4:
        case 6:
        case 9:
        case 11: if (CtoI(c)*10 + CtoI(d) <= 30 && CtoI(c)*10 + CtoI(d) >= 1)
            return 0;
        else return 1;
        default: if (CtoI(c)*10 + CtoI(d) <= 31 && CtoI(c)*10 + CtoI(d) >= 1)
            return 0;
        else return 1;
    }
}

int main()
{
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
                flag = yearCheck(your_number[6],your_number[7], your_number[8], your_number[9] ) || dateCheck(your_number[10], your_number[11], your_number[12], your_number[13], your_number[6], your_number[7], your_number[8], your_number[9]);
            if  (flag == 0 ) break;
            printf("Your input is invalid, please try again!\n");
            if (yearCheck(your_number[6],your_number[7], your_number[8], your_number[9] ) || dateCheck(your_number[10], your_number[11], your_number[12], your_number[13], your_number[6], your_number[7], your_number[8], your_number[9]))
                printf("Birthdate is not valid.\n");
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
        if (check_bit == (12 - (temp_sum % 11 )) % 11)
            printf("This ID number is valid.\n" );
        else
            printf("This ID number is not valid.\n");
        while (1){
            printf("Would you like to do another ID number check?\n");
            printf("Type y to continue, type q to quit.\n");
            char choice;
            scanf("%s", &choice);
            if (choice == 'N' || choice == 'n') return 0;
            else if (choice == 'Y' || choice == 'y') {
                printf("\n");
                break;
                
            }
        }
    }
    return 0;
    
}

