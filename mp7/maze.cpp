/* Your code here! */
#include "maze.h"
#include <iostream>
using namespace std;
using namespace cs225;

const int BREAK_RIGHT=0;
const int BREAK_DOWN=1;

const int NO_WALL=0;
const int DOWN_WALL=1;
const int RIGHT_WALL=2;
const int BOTH_WALL=3;

const int RIGHT=0;
const int DOWN=1;
const int LEFT=2;
const int UP=3;

SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
}
void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;
    squares.resize(width*height, BOTH_WALL);
    sets.addelements(width*height);

    // traversal by suqare, not node
    while(sets.size(0)<width_*height_){
        int x = rand()%height_;
        int y = rand()%width_;
        int wall = rand()%2;
        if(wall == BREAK_RIGHT){
            if(x!=width_-1 && // rightmost node has no right neighbour
               sets.find(y*width_+x)!=sets.find(y*width_+x+1)){
                sets.setunion(y*width_+x, y*width_+x+1);
                setWall(x,y,BREAK_RIGHT,false);
            }
        }else{
            if(y!=height_-1 && // bottommost node has no bottom neighbour
               sets.find(y*width_+x)!=sets.find((y+1)*width_+x)){
                sets.setunion(y*width_+x,(y+1)*width_+x);
                setWall(x,y,BREAK_DOWN,false);
            }
        }
    }
}
bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(width_==0||height_==0) return false;
    switch (dir){
        case RIGHT:
            if(x==width_-1|| 
                squares[y*width_+x]==RIGHT_WALL|| 
                squares[y*width_+x]==BOTH_WALL) return false;
            break;
        case DOWN:
            if(y==height_-1||
                squares[y*width_+x]==DOWN_WALL||
                squares[y*width_+x]==BOTH_WALL) return false;
            break;
        case LEFT:
            if(x==0||
                squares[y*width_+x-1]==RIGHT_WALL||
                squares[y*width_+x-1]==BOTH_WALL) return false;
            break;
        case UP:
            if(y==0||
                squares[(y-1)*width_+x]==DOWN_WALL||
                squares[(y-1)*width_+x]==BOTH_WALL) return false;
    }
    return true;
}
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(width_==0||height_==0) return;
    if(dir==0){         // right
        if(exists){     // create wall
            if(squares[y*width_+x]==RIGHT_WALL||squares[y*width_+x]==BOTH_WALL) return;
            else if(squares[y*width_+x]==DOWN_WALL) squares[y*width_+x]=BOTH_WALL;
            else squares[y*width_+x]=RIGHT_WALL;
        }else{          // break wall
            if(squares[y*width_+x]==DOWN_WALL||squares[y*width_+x]==NO_WALL) return;
            else if(squares[y*width_+x]==RIGHT_WALL) squares[y*width_+x]=NO_WALL;
            else squares[y*width_+x]=DOWN_WALL;
        }
    }else if(dir==1){   // down
        if(exists){     // create wall
            if(squares[y*width_+x]==DOWN_WALL||squares[y*width_+x]==BOTH_WALL) return;
            else if(squares[y*width_+x]==RIGHT_WALL) squares[y*width_+x]=BOTH_WALL;
            else squares[y*width_+x]=DOWN_WALL;
        }else{          // break wall
            if(squares[y*width_+x]==RIGHT_WALL||squares[y*width_+x]==NO_WALL) return;
            else if(squares[y*width_+x]==DOWN_WALL) squares[y*width_+x]=NO_WALL;
            else squares[y*width_+x]=RIGHT_WALL;
        }
    }
}
vector<int> SquareMaze::solveMaze(){
    
    vector<int> length(width_*height_,-1);      // distance to (0,0)
    vector<int> operation(width_*height_,-1);   // last operation to cur
    vector<int> previous(width_*height_,-1);    // last block to cur
    queue<int> q;                               // BFS
    q.push(0);
    length[0]=0;
    while (!q.empty()){
        int cur=q.front();
        q.pop();
        int x=cur%width_;
        int y=cur/width_;
        if(canTravel(x,y,LEFT)&&length[x-1+width_*y]==-1){
            length[x-1+width_*y]=length[cur]+1;
            operation[x-1+width_*y]=LEFT;
            previous[x-1+width_*y]=cur;
            q.push(x-1+width_*y);
        }
        if(canTravel(x,y,RIGHT)&&length[x+1+width_*y]==-1){
            length[x+1+width_*y]=length[cur]+1;
            operation[x+1+width_*y]=RIGHT;
            previous[x+1+width_*y]=cur;
            q.push(x+1+width_*y);
        }
        if(canTravel(x,y,DOWN)&&length[x+width_*(y+1)]==-1){
            length[x+width_*(y+1)]=length[cur]+1;
            operation[x+width_*(y+1)]=DOWN;
            previous[x+width_*(y+1)]=cur;
            q.push(x+width_*(y+1));
        }
        if(canTravel(x,y,UP)&&length[x+width_*(y-1)]==-1){
            length[x+width_*(y-1)]=length[cur]+1;
            operation[x+width_*(y-1)]=UP;
            previous[x+width_*(y-1)]=cur;
            q.push(x+width_*(y-1));
        }
    }

    int maxDist=-1;
    int maxIdx=-1;
    int index=0;
    for(int i=0;i<width_;i++){
        if(length[i+width_*(height_-1)]>maxDist){
            maxDist=length[i+width_*(height_-1)];
            maxIdx=i+width_*(height_-1);
        }
    }
    vector<int> solution;
    stack<int> trace;
    if(maxIdx==-1) return solution;
    while(previous[maxIdx]!=-1){
        trace.push(operation[maxIdx]);
        maxIdx=previous[maxIdx];
    }
    while(!trace.empty()){
        solution.push_back(trace.top());
        trace.pop();
    }
    return solution;

}
PNG* SquareMaze::drawMaze() const{
    PNG* png=new PNG(width_*10+1,height_*10+1);
    // grids
    for(int y=0;y<height_;y++){
        for(int x=0;x<width_;x++){
            int idx=y*width_+x;
            if(squares[idx]==RIGHT_WALL||squares[idx]==BOTH_WALL){
                for(int i=0;i<=10;i++){
                    HSLAPixel* pixel=png->getPixel((x+1)*10, y*10+i);
                    pixel->l=0.0;
                }
            }
            if(squares[idx]==DOWN_WALL||squares[idx]==BOTH_WALL){
                for(int i=0;i<=10;i++){
                    HSLAPixel* pixel=png->getPixel(x*10+i, (y+1)*10);
                    pixel->l=0.0;
                }
            }
        }
    }
    // leftmost
    for(int i=0;i<height_*10+1;i++){
        HSLAPixel* pixel=png->getPixel(0,i);
        pixel->l=0.0;
    }
    // uppermost, except the first block
    for(int i=0;i<width_*10+1;i++){
        if(i>9){
            HSLAPixel* pixel=png->getPixel(i,0);
            pixel->l=0.0;
        }
    }
    // rightlower
    HSLAPixel* pixel=png->getPixel(width_*10,height_*10);
    pixel->l=0.0;

    return png;
}
PNG* SquareMaze::drawMazeWithSolution(){
    PNG* png=drawMaze();
    vector<int> solution=solveMaze();
    HSLAPixel red(0,1,0.5);
    int x=5;
    int y=5;
    HSLAPixel* pixel=png->getPixel(x,y);
    *pixel=red;

    for(int i=0; i<solution.size(); i++){
        switch (solution[i]){
        case UP:
            for(int j=0; j<10; j++){
                y--;
                HSLAPixel* pixel=png->getPixel(x,y);
                *pixel=red;
            }
            break;
        case DOWN:
            for(int j=0; j<10; j++){
                y++;
                HSLAPixel* pixel=png->getPixel(x,y);
                *pixel=red;
            }
            break;
        case LEFT:
            for(int j=0; j<10; j++){
                x--;
                HSLAPixel* pixel=png->getPixel(x,y);
                *pixel=red;
            }
            break;
        case RIGHT:
            for(int j=0; j<10; j++){
                x++;
                HSLAPixel* pixel=png->getPixel(x,y);
                *pixel=red;
            }
            break;
        }
    }
    // break the wall
    HSLAPixel white(0,0,1);
    y=y+5;
    x=x-5;
    for(int i=0; i<9; i++){
        x++;
        HSLAPixel* pixel=png->getPixel(x,y);
        *pixel=white;
    }

    return png;
}