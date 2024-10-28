/* Your code here! */
#pragma once
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"
#include <stdlib.h>
#include <queue>
#include <stack>
#include <assert.h>
using namespace std;
using namespace cs225;

class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
    private:
        int width_,height_;
        DisjointSets sets;
        vector<int> squares;
};