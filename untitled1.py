#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  4 17:45:10 2018

@author: zhanghongshuo
"""

a = []
row = int(input("Enter a row index: "))
for col in range(0 , row+1):
    if (col == 0):
        coef = '1'
        
        
        a.append(coef)
        
        
    else:
        coef = float(coef)
        coef = coef * (row + 1 - col) / col
        coef = int (coef)
        coef = str(coef)
        a.append(coef)
        

print(" ".join(a))



