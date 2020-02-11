/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze(){
    new_set = new DisjointSets;
    solved = false;
}

SquareMaze::~SquareMaze(){
    delete new_set;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            delete hashtable[i*width+j];
        }
    }
}
void SquareMaze::makeMaze(int width, int height){
    /* delete the disjoint set if there is something in there. */
    if (new_set != nullptr){
        if (new_set -> size() != 0){
            delete new_set;
            new_set = new DisjointSets;
            new_set -> addelements(width*height);
            look_up.clear();
            walls.clear();
        }
         /* push width * height number of elements into the new_set. */
        else {
        new_set -> addelements(width*height);
    }
    }
    this -> width = width;
    this -> height = height;
    /** push each individual node into the hashtable. 
     *  Handy for solving mazes...
     **/
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            hashtable.insert({i*width+j, new MazeNode(j, i)});
        }
    }
    /** assign each square block into the lookup table with walls set to true.
     * count total number of walls that can be removed.
     *  keep removing walls until no walls can be removed.
     */
    int num_of_walls = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j < width - 1) {
                num_of_walls++;
                look_up.push_back({i*width+j, 0});
            }
            if (i < height - 1) {
                num_of_walls++;
                look_up.push_back({i*width+j, 1});
            }
            walls.push_back(Block(i*width+j));
        }
    }

    while (!look_up.empty()){
        int random = rand() % num_of_walls;
        std::pair<int, int> p = look_up[random];
        if (p.second == 0 && p.first % width < width - 1){
            /* find if the element has already been added to the set.*/
            if (new_set -> find(p.first) != new_set -> find(p.first+1)){
                /* if not, remove the wall and decrement the num_of_walls. */
                int coordinates = p.first;
                std::swap(look_up[random], look_up[look_up.size()-1]);
                look_up.pop_back();
                //find the exact pair in walls. not exactly at index random.
                walls[coordinates].right = false;
                new_set -> setunion(p.first, p.first+1);
                num_of_walls--;
            }
            else {
                std::swap(look_up[random], look_up[look_up.size()-1]);
                look_up.pop_back();
                num_of_walls--;
            }
        }

        else if (p.second == 1 && p.first / width < height - 1) {
            if (new_set -> find(p.first) != new_set -> find(p.first+width)){
                /* if not, remove the wall and decrement the num_of_walls. */
                int coordinates = p.first;
                std::swap(look_up[random], look_up[look_up.size()-1]);
                look_up.pop_back();
                //find the exact pair in walls. not exactly at index random.
                walls[coordinates].down = false;
                new_set -> setunion(p.first, p.first+width);
                num_of_walls--;
            }
            else {
                std::swap(look_up[random], look_up[look_up.size()-1]);
                look_up.pop_back();
                num_of_walls--;
            }
        }
    }
    return;
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if (x == 0 && dir == 2) return false;
    if (x == width - 1 && dir == 0) return false;
    if (y == 0 && dir == 3) return false;
    if (y == height - 1 && dir == 1) return false;
    int idx = y * width + x;
    switch (dir){
        case 0: if (walls[idx].right == true) return false;
                break;
        case 1: if (walls[idx].down == true) return false;
                break;
        case 2: if (walls[idx-1].right == true) return false;
                break;
        case 3: if (walls[idx-width].down == true) return false;
                break;
    }       
    return true;
}



 cs225::PNG* SquareMaze::drawMaze(){

     cs225::PNG* canvas = new cs225::PNG(width*10+1, height*10+1);
      for (int j = 10; j < width*10+1; j++){
        cs225::HSLAPixel & p = canvas -> getPixel(j,0);
        p.h = 0; p.s = 0; p.l = 0; p.a = 1;
      }

    for (int i = 0; i < height*10+1; i++){
      cs225::HSLAPixel & p = canvas -> getPixel(0, i);
      p.h = 0; p.s = 0; p.l = 0; p.a = 1;
    }

    for (const auto& b: walls){
      int y = b.coord / width;
      int x = b.coord % width;
      if (b.right == true){
        for (int k = 0; k <= 10; k++){
          cs225::HSLAPixel & p = canvas -> getPixel((x+1)*10, y*10+k);
          p.h = 0; p.s = 0; p.l = 0; p.a = 1;
        }
      }
      if (b.down == true){
        for (int k = 0; k <= 10; k++){
          cs225::HSLAPixel & p = canvas -> getPixel(x*10+k, (y+1)*10);
          p.h = 0; p.s = 0; p.l = 0; p.a = 1;
        }
      }

    }
     return canvas;
 }

 cs225::PNG* SquareMaze::drawMaze(cs225::PNG* original){
      
      for (int j = 10; j < width*10; j++){
        cs225::HSLAPixel & p = original -> getPixel(j,0);
        if (p.h == 0 && p.s == 0 && p.l == 0 && p.a == 0) continue;
        p.h = rand()%360; p.s = rand()%100/100; p.l = rand()%100/100; p.a = rand()%100/100;
      }

    for (int i = 0; i < height*10; i++){
      cs225::HSLAPixel & p = original -> getPixel(0, i);
      if (p.h == 0 && p.s == 0 && p.l == 0 && p.a == 0) continue;
      p.h = rand()%360; p.s = rand()%100/100; p.l = rand()%100/100; p.a = rand()%100/100;
    }

    for (const auto& b: walls){
      int y = b.coord / width;
      int x = b.coord % width;
      if (b.right == true){
        for (int k = 0; k <= 10; k++){
          cs225::HSLAPixel & p = original -> getPixel((x+1)*10, y*10+k);
          if (p.h == 0 && p.s == 0 && p.l == 0 && p.a == 0) continue;
          p.h = 212.679; p.s = 0.888889; p.l = 0.247059; p.a = 1;
        }
      }
      if (b.down == true){
        for (int k = 0; k <= 10; k++){
          cs225::HSLAPixel & p = original -> getPixel(x*10+k, (y+1)*10);
          if (p.h == 0 && p.s == 0 && p.l == 0 && p.a == 0) continue;
          p.h = 357.143; p.s = 0.502392; p.l = 0.409804; p.a = 1;
        }
      }

    }
    return original;
 }

 cs225::PNG* SquareMaze::drawMazeWithSolution(){
     cs225::PNG* canvas = this -> drawMaze();
     std::pair<int, int> dest = {hashtable[longest_dist_idx] -> x, hashtable[longest_dist_idx] -> y};
     std::pair<int, int> coord = {5,5};
     for (auto idx: sol){
         if (idx == 0){
            for (int i = 0; i <= 10; i++){
                cs225::HSLAPixel &p = canvas -> getPixel(coord.first+i, coord.second);
                p.h = 0; p.s = 1; p.l = 0.5; p.a = 1;
            }
            coord.first += 10;
         }
        else if (idx == 1){
            for (int i = 0; i <= 10; i++){
                cs225::HSLAPixel &p = canvas -> getPixel(coord.first, coord.second+i);
                p.h = 0; p.s = 1; p.l = 0.5; p.a = 1;
            }
            coord.second += 10;
        } 
        else if (idx == 2){
            for (int i = 0; i <= 10; i++){
                cs225::HSLAPixel &p = canvas -> getPixel(coord.first-i, coord.second);
                p.h = 0; p.s = 1; p.l = 0.5; p.a = 1;
            }
            coord.first -= 10;
        }          
        else if (idx == 3){
            for (int i = 0; i <= 10; i++){
                cs225::HSLAPixel &p = canvas -> getPixel(coord.first, coord.second-i);
                p.h = 0; p.s = 1; p.l = 0.5; p.a = 1;
            }
            coord.second -= 10;
        }  
     }
     
     for (int k = 1; k < 10; k++){
         cs225::HSLAPixel &p = canvas -> getPixel(dest.first*10+k, (dest.second+1)*10);
         p.h = 360; p.s = 1; p.l = 1; p.a = 1;
     }
     return canvas;
 }


 void SquareMaze::setWall(int x, int y, int dir, bool exists){
     switch (dir){
         // 0 --> set rightwards.
         case 0: walls[y*width+x].right = exists;
                 break;
         // 1 --> set downwards.
         case 1: walls[y*width+x].down = exists;
                 break;
         // 2 --> set leftwards.
         case 2: walls[y*width+x-1].right = exists;
                 break;
         // 3 --> set upwards.
         case 3: walls[(y-1)*width+x].down = exists;
                 break;
     }
     return;
 }

 std::vector<int> SquareMaze::solveMaze(){
      if (solved == true) return sol;
      /** Mark node at origin as visited.
       * push it onto the queue.
       **/
      hashtable[0] -> visited = true;
     
      q.push(hashtable[0]);
      while (!q.empty()){
          MazeNode* current = q.front();
          int x = current -> x;
          int y = current -> y;
          int dist = current -> dist;
          q.pop();
          /* check each individual node here. */
          if (canTravel(x, y, 0) == true) {
              if (hashtable[y*width+x+1] -> visited == false){
                /* if right node visited yet, make this the child node of the parent node. */
                hashtable[y*width+x+1] -> visited = true;
                hashtable[y*width+x+1] -> parent = current;
                current -> right = hashtable[y*width+x+1];
                hashtable[y*width+x+1] -> dist = dist + 1;
                q.push(hashtable[y*width+x+1]);
              }
          }
          if (canTravel(x, y, 1) == true) {
              if (hashtable[(y+1)*width+x] -> visited == false){
                /* if right node visited yet, make this the child node of the parent node. */
                hashtable[(y+1)*width+x] -> visited = true;
                hashtable[(y+1)*width+x] -> parent = current;
                current -> down = hashtable[(y+1)*width+x];
                hashtable[(y+1)*width+x] -> dist = dist + 1;
                q.push(hashtable[(y+1)*width+x]);
              }
          }
          if (canTravel(x, y, 2) == true) {
                if (hashtable[y*width+x-1] -> visited == false){
                /* if right node visited yet, make this the child node of the parent node. */
                hashtable[y*width+x-1] -> visited = true;
                hashtable[y*width+x-1] -> parent = current;
                current -> left = hashtable[y*width+x-1];
                hashtable[y*width+x-1] -> dist = dist + 1;
                q.push(hashtable[y*width+x-1]);
              }
          }
          if (canTravel(x, y, 3) == true) {
              if (hashtable[(y-1)*width+x] -> visited == false){
                /* if right node visited yet, make this the child node of the parent node. */
                hashtable[(y-1)*width+x] -> visited = true;
                hashtable[(y-1)*width+x] -> parent = current;
                current -> up = hashtable[(y-1)*width+x];
                hashtable[(y-1)*width+x] -> dist = dist + 1;
                q.push(hashtable[(y-1)*width+x]);
              }
          }
      }
    /** after everything has been added to the hashtable.
     *  We may check the last row to see which one has the longest path. 
     **/
        int longest_dist = hashtable[(height-1)* width] -> dist;
        longest_dist_idx = (height-1)* width;
        for (int j = 0; j < width; j++){
            if (hashtable[(height-1)* width + j] -> dist > longest_dist){
                longest_dist = hashtable[(height-1)* width + j] -> dist;
                longest_dist_idx = (height-1)* width + j;
            }
        }
    /** Now we know what path is the longest path, 
     * We may work backwards to figure out what the vector is.
     **/
        MazeNode* next = hashtable[longest_dist_idx];
        while (1){
            if (next -> x == 0 && next -> y == 0) break;
            MazeNode* parent = next -> parent;
            if (parent -> right == next) s.push(0);
            if (parent -> down == next) s.push(1);
            if (parent -> left == next) s.push(2);
            if (parent -> up == next) s.push(3);
            next = parent;
        }
        while (!s.empty()){
            sol.push_back(s.top());
            s.pop();
        }
      return sol;
 }

 
