//
//  check.h
//  something
//
//  Created by 张洪硕 on 2019/7/12.
//  Copyright © 2019 张洪硕. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
char *prov_name;
typedef struct cities{
    char citycode[2];
    char *cityname;
    char *dists;
} city;

typedef struct provinces{
    char provcode[2];
    char *provname;
    city *cities; //need to malloc manually.
} prov;


typedef struct dists{
    char distcode[2];
    char *distname;
} dist;

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

int ProvinceCheck(char a, char b){
    int flag = 1;
    FILE *region = fopen("storage.txt", "r");
    prov province[31];
    int i;
    for (i = 0; i <= 30; i++){
        province[i].provname = (char*) malloc(sizeof(char) * 50);
        fscanf(region, "%s %s", province[i].provcode, province[i].provname);
    }
    
    fclose(region);
    
    int provno = CtoI(a)* 10 + CtoI(b);
    
    for (i = 0; i <= 30; i++){
        int checkno = CtoI(province[i].provcode[0])*10 + CtoI(province[i].provcode[1]);
        if (provno == checkno){
            flag = 0;
            prov_name = province[i].provname;
            break;
        }
        
    }
    for (i = 0; i<= 30; i++){
        free(province[i].provname);
    }
    return flag;
}

int CityCheck(char a, char b){
    int flag = 1;
    return flag;
}

int DistCheck(char a, char b){
    int flag = 1;
    return flag;
}
