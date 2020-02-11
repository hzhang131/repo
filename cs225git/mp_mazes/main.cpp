#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cs225::PNG* input = new cs225::PNG;
    input -> cs225::PNG::readFromFile("test.png"); 
    cs225::HSLAPixel& p = input -> cs225::PNG::getPixel(708,760);
    cout << p.h << " " << p.s << " " << p.l << " " << p.a << " " << endl;
    SquareMaze* sq = new SquareMaze;
    sq -> makeMaze((int) input -> width()/10, (int) input -> height()/10);
    input -> cs225::PNG::resize((int) input -> width(), (int) input -> height());
    cs225::PNG* output = sq -> drawMaze(input);
    output -> cs225::PNG::writeToFile("creative.png");
    delete input;
    return 0;
}
