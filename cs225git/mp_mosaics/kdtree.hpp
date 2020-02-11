/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    //break tie.
    else if (first[curDim] == second[curDim]){
      return first < second;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double cur_dist = 0;
     double pot_dist = 0;
     for (int i = 0; i < Dim; i++){
       cur_dist += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
       pot_dist += (target[i] - potential[i]) * (target[i] - potential[i]);
     }
     if (pot_dist < cur_dist) return true;
     else if (pot_dist == cur_dist) return potential < currentBest;
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (!newPoints.empty()){
      vector<Point<Dim>> new_vec = newPoints;
      // find the median and sort that using quickselect starting from Dimension 0.
      //quickselect(new_vec, 0, new_vec.size()-1, (new_vec.size()-1)/2+1, 0);
      root = Build_tree(new_vec, 0, new_vec.size()-1, 0);
    }
    else root = nullptr;
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::Build_tree(vector<Point<Dim>>& new_vec, int start, int end, int curDim){
  if (start > end) return nullptr;
  if (start == end) {
    KDTreeNode* node = new KDTreeNode(new_vec[start]);
    return node;
  }
  quickselect(new_vec, start, end, (end - start)/2+1, curDim);
  KDTreeNode* base = new KDTreeNode(new_vec[(start + end)/2]);
  base -> left = Build_tree(new_vec, start, (start+end)/2 - 1, (curDim+1)%Dim);
  base -> right = Build_tree(new_vec, (start+end)/2 + 1, end, (curDim+1)%Dim);
  return base;
}

template <int Dim>
void KDTree<Dim>::quickselect(vector<Point<Dim>>& new_vec, int start, int end, int k, int curDim){
  // find the median in dimension x.
  if (k > 0 && k <= end - start + 1){
    int idx = partition(new_vec, start, end, curDim);
    if (idx - start == k - 1) {
      return;
    }
    //search for left and right side of the index.
    else if (idx - start > k - 1) {
      //int newDim = curDim + 1;
      //if (newDim == Dim) newDim = 0;
      return quickselect(new_vec, start, idx - 1, k, curDim);
    }
    else if (idx - start < k - 1) {
      //int newDim = curDim+1;
      //if (newDim == Dim) newDim = 0;
      return quickselect(new_vec, idx+1, end, k-idx+start-1, curDim);
    }
    return;
}

 }

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& new_vec, int start, int end, int curDim){
  Point<Dim> x = new_vec[end];
  int i = start;
  for (int j = start; j <= end - 1; j++){
    if (smallerDimVal(new_vec[j], x, curDim) == true){
      Point<Dim> swap = new_vec[i];
      new_vec[i] = new_vec[j];
      new_vec[j] = swap;
      i++;
    }
  }
  Point<Dim> swap = new_vec[i];
  new_vec[i] = new_vec[end];
  new_vec[end] = swap;
  return i;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   this -> size = other.size;
   this -> root = clone(other.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::clone(KDTreeNode* other){
  if (other == nullptr) return nullptr;
  KDTreeNode* new_node = new KDTreeNode(other);
  new_node -> left = clone(other -> left);
  new_node -> right = clone(other -> right);
  return new_node;
}

template <int Dim>
void KDTree<Dim>::del(KDTreeNode* root){
  if (root == nullptr) return;
  if (root -> left == nullptr && root -> right == nullptr){
    delete root;
    root = nullptr;
    return;
  }
  del(root -> left);
  del(root -> right);
  delete root;
  root = nullptr;
  return;
}



template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  this -> root = rhs.getRoot();
  this -> size = rhs.getSize();
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   del(this -> root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    KDTreeNode* node = findNearestNeighborHelper(query, root, 0);
    return node -> point;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query, KDTreeNode* root, int curDim) const{
  // Basecase: we return node when we hit the leaf.
  if (root == nullptr) return nullptr;
  if (root -> point == query) return root;
  if (root -> left == nullptr && root -> right == nullptr) return root;
  //first we may traverse down the KDTree.
  KDTreeNode* node = root;
  double split_dist = (root -> point[curDim] - query[curDim]) * (root -> point[curDim] - query[curDim]);
  if (smallerDimVal(query, root -> point, curDim)) {
    int newDim = curDim + 1;
    if (newDim == Dim) {
      newDim = 0;
      if (root -> left){
        node = findNearestNeighborHelper(query, root -> left, newDim);
      }
    }
    else {
      if (root -> left){
        node = findNearestNeighborHelper(query, root -> left, newDim);
      }
    }
    //solve for dist between current node.
    //here we may traverse back up.
    //compare query <--> node with query <--> root, update node if necessary.
    //swap node and smallest_dist if necessary.

    if (getDist(query,root -> point) <= getDist(query, node -> point)) {
      if (shouldReplace(query, node -> point, root -> point)){
        node = root;
      }

     }
     if (split_dist <= getDist(query, node -> point)){
       if (root -> right != nullptr){
         KDTreeNode* potential = findNearestNeighborHelper(query, root -> right, newDim);
            if (shouldReplace(query, node -> point, potential -> point)){
             node = potential;
            }
          }
     }


  }

  else {
    int newDim = curDim + 1;
    if (newDim == Dim) {
      newDim = 0;
      if (node -> right){
        node = findNearestNeighborHelper(query, root -> right, newDim);
      }
    }
    else {
      if (node -> right){
        node = findNearestNeighborHelper(query, root -> right, newDim);
      }
    }
    if (getDist(query,root -> point) <= getDist(query, node -> point)) {
      if (shouldReplace(query, node -> point, root -> point)){
        node = root;
      }

       }
       if (split_dist <= getDist(query, node -> point)){
         if (root -> left != nullptr){
           KDTreeNode* potential = findNearestNeighborHelper(query, root -> left, newDim);
              if (shouldReplace(query, node -> point, potential -> point)){
               node = potential;
              }
            }
       }
    }
    return node;
  }


template<int Dim>
double KDTree<Dim>::getDist(const Point<Dim> query, const Point<Dim> p) const{
  double cur_dist = 0;
  for (int i = 0; i < Dim; i++){
    cur_dist += (query[i] - p[i]) * (query[i] - p[i]);
  }
  return cur_dist;
}
