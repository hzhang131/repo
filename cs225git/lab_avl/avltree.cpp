/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include "avltree.h"
 using namespace std;
 template <class K, class V>

 int AVLTree<K, V>::get_height_helper(Node* root){
   if (root == nullptr) return 0;
   int max_left = get_height_helper(root -> left);
   int max_right = get_height_helper(root -> right);
   if (max_left > max_right) return max_left + 1;
   else return max_right + 1;
 }
template <class K, class V>
 void AVLTree<K, V>::updateHeight(Node* root){
   if (root == nullptr) return;
   root -> height = get_height_helper(root);
   updateHeight(root -> left);
   updateHeight(root -> right);
 }
template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::get_iop(Node*& subtree){
   if (subtree == nullptr) return subtree;
   else if (subtree -> right == nullptr) return subtree;
   return get_iop(subtree -> right);
 }

 template <class K, class V>
 typename AVLTree<K, V>::Node*& AVLTree<K, V>::get_ios(Node*& subtree){
    if (subtree == nullptr) return subtree;
    else if (subtree -> left == nullptr) return subtree;
    return get_ios(subtree -> left);
  }

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* next = t -> right;
    t -> right = next -> left;
    next -> left = t;
    t = next;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* next = t -> left;
    t -> left = next -> right;
    next -> right = t;
    t = next;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //calculate the height factor.
    if (subtree == nullptr) return;
    int balance = get_height_helper(subtree -> right) - get_height_helper(subtree -> left);
    if (balance == -2 ){
      int l_balance = get_height_helper(subtree -> left -> right) - get_height_helper(subtree -> left -> left);
      if (l_balance == -1) rotateRight(subtree);
      else rotateLeftRight(subtree);
    }
    else if(balance == 2){
      int r_balance = get_height_helper(subtree -> right -> right) - get_height_helper(subtree -> right -> left);
      if (r_balance == 1) rotateLeft(subtree);
      else rotateRightLeft(subtree);
    }
    updateHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr){
      subtree = new Node(key, value);
    }
    else if (key < subtree -> key){
      insert(subtree -> left, key, value);
      rebalance(subtree);
    }
    else if (key > subtree -> key){
      insert(subtree -> right, key, value);
      rebalance(subtree);
    }

    subtree -> height = 1;
    if (get_height_helper(subtree -> left) > get_height_helper(subtree -> right)){
      subtree -> height += get_height_helper(subtree -> left);
    }
    else {
      subtree -> height += get_height_helper(subtree -> right);
    }
    return;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
  
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //swap current pointer with the IOP
            Node*& new_ref = get_iop(subtree -> left);
            swap(new_ref, subtree);
            delete new_ref;
            new_ref = nullptr;

        } else {
            /* one-child remove */
            // your code here
            //Try in-order predecessor.
            if (get_iop(subtree -> left)){
              Node*& new_ref = get_iop(subtree -> left);
              swap(new_ref, subtree);
              delete new_ref;
              new_ref = nullptr;
            }
            //Try in-order successor.
            else if (get_ios(subtree -> right)){
              Node*& new_ref = get_ios(subtree -> right);
              swap(new_ref, subtree);
              delete new_ref;
              new_ref = nullptr;
            }
        }
        // your code here
        if (subtree != nullptr){
          subtree -> height = 1;
          if (get_height_helper(subtree -> left) > get_height_helper(subtree -> right)){
            subtree -> height += get_height_helper(subtree -> left);
          }
          else {
            subtree -> height += get_height_helper(subtree -> right);
          }
        }
    }
}
