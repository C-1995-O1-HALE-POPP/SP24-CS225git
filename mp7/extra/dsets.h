/* Your code here! */
#pragma once
#include <vector>
#include <string>
using namespace std;
class DisjointSets{
    public:
        DisjointSets();
        DisjointSets(const DisjointSets& other);
        DisjointSets(const int size);
        void addelements(const int size);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
    private:
        vector<int> set;
};
