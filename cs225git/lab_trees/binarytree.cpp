/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <vector>

template <typename T>
void BinaryTree<T>::mirror_helper(Node* root){
  if (root == NULL) return;
  Node* temp;
  temp = root -> left;
  root -> left = root -> right;
  root -> right = temp;
  if (root -> left != NULL){
    mirror_helper(root -> left);
  }
  if (root -> right != NULL){
    mirror_helper(root -> right);
  }
  return;
}
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror_helper(root);
    return;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> happytree718(root);
    bool flag = true;
    // there are no current nodes to push for me. So, I can start popping.
    // set current node to top -> right.
    Node* curr = nullptr;
    Node* prev = happytree718.peek();
    while (happytree718.empty() == false){
      curr = happytree718.pop();
      if (curr -> elem < prev -> elem ) {
        flag = false;
      }
      happytree718.add(curr);
      prev = curr;
    }

    return flag;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedHelper(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedHelper(Node* subRoot) const{

  bool flag = true;
  if (subRoot == nullptr) return true;
  if (subRoot -> left == nullptr && subRoot -> right == nullptr) return true;
  else if (subRoot -> left == nullptr && subRoot -> right != nullptr){
    if (subRoot -> elem >= min_val(subRoot -> right)) return false;
    else
    flag = flag && isOrderedHelper(subRoot -> right);
  }
  else if (subRoot -> left != nullptr && subRoot -> right == nullptr){
    if (subRoot -> elem <= max_val(subRoot -> left)) return false;
    else
    flag = flag && isOrderedHelper(subRoot -> left);
  }
  else if (subRoot -> left != nullptr && subRoot -> right != nullptr){
    if (subRoot -> elem <= max_val(subRoot -> left)) return false;
    else if (subRoot -> elem >= min_val(subRoot -> right)) return false;
    else{
      flag = flag && isOrderedHelper(subRoot -> left);
      flag = flag && isOrderedHelper(subRoot -> right);
    }
  }
  return flag;
}

template <typename T>
T BinaryTree<T>::max_val(Node* subRoot) const{
  T value = T();
  Node* curr_root = subRoot;
  while (curr_root != nullptr){
    value = curr_root -> elem;
    curr_root = curr_root -> right;
  }
  return value;
}

template <typename T>
T BinaryTree<T>::min_val(Node* subRoot) const{
  T value = T();
  Node* curr_root = subRoot;
  while (curr_root != nullptr){
    value = curr_root -> elem;
    curr_root = curr_root -> left;
  }
  return value;
}
template <typename T>
void BinaryTree<T>::getPathsHelper(Node* subRoot, std::vector<std::vector<T>>& paths, std::vector<T>& vec) const{

  /*
  InorderTraversal<T> happytree718(subRoot);
  Node* curr = subRoot;
  while (happytree718.empty() == false){
    while (curr != nullptr){
      vec.push_back(curr -> elem);
      curr = curr -> left;
    }
    paths.push_back(vec);
    Node* temp = happytree718.peek();
    Node* curr = happytree718.pop();
    vec.pop_back();
    happytree718.add(temp);
    curr = curr -> right;
  }
  */


  Node* curr = subRoot;
  Node* last_node = nullptr;
  if (curr == nullptr) return;
  vec.push_back(curr -> elem);
  if (curr -> left == nullptr && curr -> right == nullptr){
    paths.push_back(vec);
    last_node = curr;
    return;
  }
  getPathsHelper(curr -> left, paths, vec);
  //empty the vector.
  if (curr -> left != nullptr) vec.pop_back();
  getPathsHelper(curr -> right, paths, vec);
  if (curr -> right != nullptr) vec.pop_back();
  return;
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
    std::vector<T> vec;
    getPathsHelper(root, paths, vec);
    return;
}



/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here

    return 10;
}
