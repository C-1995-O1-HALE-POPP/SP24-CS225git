/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;

DisjointSets::DisjointSets(){}
DisjointSets::DisjointSets(const DisjointSets& other){
    set=other.set;
}
DisjointSets::DisjointSets(const int size){
    for(int i=0; i<size; i++) set.push_back(-1);
}
void DisjointSets::addelements(const int size){
    for(int i=0; i<size; i++) set.push_back(-1);
}
int DisjointSets::find(const int elem){
    if(set[elem] < 0) return elem;
    return set[elem] = find(set[elem]);
}
int DisjointSets::size(int elem){
    return -set[find(elem)];
}
void DisjointSets::setunion(int a, int b){
    if (find(a)==find(b)) return;
    int newWeight=set[find(a)]+set[find(b)];
    if(set[find(a)]<=set[find(b)]){
        set[find(b)]=find(a);
        set[find(a)]=newWeight;
    }else{
        set[find(a)]=find(find(b));
        set[find(b)]=newWeight;
    }
}