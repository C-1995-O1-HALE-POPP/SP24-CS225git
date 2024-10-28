/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;
dsets::dsets(const int size){
    for(int i=0; i<size; i++) set.push_back(-1);
}
void dsets::addElements(const int size){
    for(int i=0; i<size; i++) set.push_back(-1);
}
int dsets::find(const int elem){
    if(set[elem] < 0) return elem;
    return set[elem] = find(set[elem]);
}
void dsets::setunion(int a, int b){
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