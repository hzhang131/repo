/* Your code here! */
#pragma once
#include <iostream> 
#include <vector> 
using namespace std;

class DisjointSets {
    public:
        DisjointSets();
        ~DisjointSets();
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        int size();
     private:
        vector<int> set;
};