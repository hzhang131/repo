/* Your code here! */
#pragma once
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <unordered_map>
#include <time.h>
#include <algorithm>
#include <queue>
#include <stack>
class SquareMaze{
    public:
        SquareMaze();
        ~SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        cs225::PNG* drawMaze();
        cs225::PNG* drawMaze(cs225::PNG* original);
        cs225::PNG* drawMazeWithSolution();
        struct Block{
            Block(int coord, bool right = true, bool down = true){
                this -> coord = coord;
                this -> right = right;
                this -> down = down;
            }
            int coord;
            bool right;
            bool down;
        };
        struct MazeNode{
            MazeNode(int x, int y, int dist = 0, MazeNode* left = NULL, MazeNode* right = NULL, MazeNode* up = NULL, 
                     MazeNode* down = NULL, MazeNode* parent = NULL, bool visited = false){
                this -> dist = dist;
                this -> left = left;
                this -> right = right;
                this -> up = up;
                this -> down = down;
                this -> parent = parent;
                this -> visited = visited;
                this -> x = x;
                this -> y = y;
            }
            ~MazeNode(){
                /* Nothing to free.*/
            }
            int x;
            int y;
            int dist;
            MazeNode* left;
            MazeNode* right;
            MazeNode* up;
            MazeNode* down;
            MazeNode* parent;
            bool visited;
        };
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
    private:
        DisjointSets* new_set;
        /** if pair.last == 0 --> Right wall.
         *  if pair.last == 1 --> Down wall.
         *  if pair.first == some random number --> cell at random number.
         **/
        std::vector<std::pair<int, int>> look_up;
        std::vector<Block> walls;
        std::unordered_map<int, MazeNode*> hashtable;
        std::queue<MazeNode*> q;
        std::stack<int> s;
        std::vector<int> sol;
        bool solved;
        int width;
        int height;
        int longest_dist_idx;
};