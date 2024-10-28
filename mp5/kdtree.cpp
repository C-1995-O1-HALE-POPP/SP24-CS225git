/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
// to avoid read lines in VSCode
//#include "kdtree.h"
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    if (first[curDim] > second[curDim]) return false;
    return (first < second); // tie
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,const Point<Dim>& currentBest,const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currentDistance = 0.0;
     double potentialDistance = 0.0;
     for (int i = 0; i < Dim; i++) {
       currentDistance+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
       potentialDistance+=(potential[i]-target[i])*(potential[i]-target[i]);
     }
     if(currentDistance==potentialDistance) return potential<currentBest; //tie
     return potentialDistance<currentDistance;
}
template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::maketree(vector<Point<Dim>>& points,int leftIdx,int rightIdx, int dim){
    if(leftIdx>rightIdx) return NULL; // for leaf nodes
    int median=(leftIdx+rightIdx)/2;
    select(points,leftIdx,rightIdx,median,dim);
    // up till now, points[median] is the median elements, as the root of subtree
    KDTreeNode* subroot=new KDTreeNode(points[median]);
    subroot->left=maketree(points,leftIdx,median-1,(dim+1)%Dim);
    subroot->right=maketree(points,median+1,rightIdx,(dim+1)%Dim);
    return subroot;
}
template<int Dim>
void KDTree<Dim>::select(vector<Point<Dim>>& points,int leftIdx,int rightIdx,int expectedMedianIdx,int dim){
  if(leftIdx>rightIdx) return;
  int median=(leftIdx+rightIdx)/2;
  int medianIdx=partition(points,leftIdx,rightIdx,median,dim);
  if(expectedMedianIdx==medianIdx) return;
  else if(expectedMedianIdx<medianIdx) select(points,leftIdx,medianIdx-1,expectedMedianIdx,dim);
  else select(points,medianIdx+1,rightIdx,expectedMedianIdx,dim);
}
template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points,int leftIdx, int rightIdx, int pivotIndex, int dim){
    Point<Dim> pivotValue=points[pivotIndex];
    swapPoints(points,pivotIndex,rightIdx);
    int storedIdx=leftIdx;
    for(int i=leftIdx; i<rightIdx; i++){
      if(smallerDimVal(points[i],pivotValue,dim)){
        swapPoints(points,storedIdx,i);
        storedIdx++;
      }
    }
    swapPoints(points,storedIdx,rightIdx);
    return storedIdx;
}
template <int Dim>
void KDTree<Dim>::swapPoints(vector<Point<Dim>>& points, int a, int b) {
	   Point<Dim> temp=points[a];
	   points[a]=points[b];
	   points[b]=temp;
}
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyTree(KDTreeNode* subroot){
    if(subroot==NULL) return NULL;
    KDTreeNode* newsubroot=new KDTreeNode(subroot->point);
    newsubroot->left=copyTree(subroot->left);
    newsubroot->right=copyTree(subroot->right);
    return newsubroot;
}
template <int Dim>
void KDTree<Dim>::deleteTree(KDTreeNode* subroot){
    if(subroot==NULL) return;
    if(subroot->left!=NULL)deleteTree(subroot->left);
    if(subroot->right!=NULL)deleteTree(subroot->right);
    delete subroot;
    subroot=NULL;
}
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> points;
    for(size_t i = 0; i < newPoints.size(); ++i){
      points.push_back(newPoints[i]);
    }
    root=maketree(points,0,newPoints.size()-1,0);
    size=newPoints.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
    root=copyTree(other.root);
    size=other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
    if(rhs==this) return *this;
    if(root!=NULL) deleteTree(root);
    root=copyTree(rhs.root);
    size=rhs.size;
    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    if(root!=NULL) deleteTree(root);
    size=0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currentBest=root->point;
    findNearestNeighbor(root,query,currentBest,0);
    return currentBest;
}
template <int Dim>
void KDTree<Dim>::findNearestNeighbor(KDTreeNode* subroot, const Point<Dim>& query,
                                      Point<Dim>& currentBest, int dimension) const{
  if(subroot==NULL) return;
  int nextDim=(dimension+1)%Dim;
  KDTreeNode *nextSubroot, *otherSubroot;
  if(smallerDimVal(query,subroot->point,dimension)){
    if(subroot->left!=NULL) {
      nextSubroot=subroot->left;
      otherSubroot=subroot->right;
    }
    else{
      nextSubroot=subroot->right;
      otherSubroot=NULL;
    }
  }else{
    if(subroot->right!=NULL) {
      nextSubroot=subroot->right;
      otherSubroot=subroot->left;
    }
    else{
      nextSubroot=subroot->left;
      otherSubroot=NULL;
    }
  }
  findNearestNeighbor(nextSubroot,query,currentBest,nextDim);

  if(shouldReplace(query,currentBest,subroot->point)) currentBest=subroot->point;
  double radius=0.0;
  for (int i=0; i<Dim; i++) radius+=(currentBest[i]-query[i])*(currentBest[i]-query[i]);
  double planeDistance=(currentBest[dimension]-query[dimension])
                      *(currentBest[dimension]-query[dimension]);
  if(radius>=planeDistance) findNearestNeighbor(otherSubroot,query,currentBest,nextDim);
}