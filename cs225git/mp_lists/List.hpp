/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
/**
 * Default List Constructor.
 * Creates an empty list.
 **/
template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  //if nothing to destroy, return.
  if (head_ == NULL || tail_ == NULL) return;
  // else traverse the whole list and delete each node manually.
  // delete from head to tail.
  else{
    ListNode* tmp;
    while (head_ != tail_){
      tmp = head_;
      head_ = head_ -> next;
      delete tmp;
    }
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  }
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
    head_ = head_ -> prev;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
    head_ = newNode;
  }

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  // Empty list.
  if (head_ == NULL || tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
    head_ -> next = NULL;
    head_ -> prev = NULL;
    length_++;
    return;
  }

  newNode -> next = NULL;
  tail_ -> next = newNode;
  newNode -> prev = tail_;
  tail_ = tail_ -> next;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint == 0){
    //if the split point is zero, there is nothing for me to split from.
    //So, we may return a nullptr
    return start;
  }
  ListNode * curr = start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }


  if (curr != NULL) {
      (curr->prev)->next = NULL;
      curr->prev = NULL;
      return curr;
  }


  return nullptr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  // if there are less than or equal to 2 nodes, we don't need to do anything here.
  if (length_ <= 2) return;
  else
  {
    //initialize the 2nd node to a random node.
      ListNode* tmp = head_ -> next;
      ListNode* tmp_static = head_ -> next -> next;
    while (1){
      (tmp -> prev) -> next = tmp -> next;
      (tmp -> next) -> prev = tmp -> prev;
      //link this node to tail.
      tail_ -> next = tmp;
      tmp -> prev = tail_;
      tmp -> next = nullptr;
      tail_ = tmp;
      //done linkage, now proceed to the other node.
      if (tmp_static -> next == tail_ || tmp_static -> next == nullptr) {
        return;
      }
      tmp = tmp_static -> next;
      tmp_static = tmp -> next;
    }
  }
    return;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
      if (startPoint == endPoint) return;
    //link startPoint to the end.
    //save a copy of the node before startPoint.
      ListNode* start_prev = startPoint -> prev;
      startPoint -> prev = startPoint -> next;
      startPoint -> next = endPoint -> next;
      if (endPoint != tail_){
        endPoint -> next -> prev = startPoint;
      }
      ListNode* curr = startPoint -> prev;
      while (curr != endPoint){
        ListNode* temp;
        temp = curr -> prev;
        curr -> prev = curr -> next;
        curr -> next = temp;
        curr = curr -> prev;
      }
    //link tail to the start.
    endPoint -> next = endPoint -> prev;
    endPoint -> prev = start_prev;
    if (startPoint != head_){
      start_prev -> next = endPoint;
    }
    //swap start and end pointers.
    ListNode* swap = startPoint;
    startPoint = endPoint;
    endPoint = swap;
    return;

  }



/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  ListNode* new_node = head_;
  if (n < 2) return;
  while (new_node != nullptr){
    ListNode* curr_node = new_node;
    int count = n;
    while (count > 1 && curr_node != tail_){
      curr_node = curr_node -> next;
      count--;
    }
    reverse(new_node, curr_node);
    if (curr_node == head_) {
      head_ = new_node;
    }
    if (new_node == tail_) {
      tail_ = curr_node;
    }
    new_node = curr_node -> next;
  }

  return;
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {

    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;

}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* curr_first = first;
  ListNode* curr_second = second;
  ListNode* first_prev = first;
  //insert at head.

  while (curr_first != nullptr && curr_second != nullptr){
    //insert at front of the curr first node if curr_second is smaller than the current_first.
    if (curr_second -> data < curr_first -> data){
      ListNode *temp = curr_second;
      curr_second = curr_second -> next;
      first_prev = curr_first -> prev;
      curr_first -> prev = temp;
      temp -> next = curr_first;
      temp -> prev = first_prev;
      if (curr_second != nullptr){
        curr_second -> prev = nullptr;
      }
      //insert at start of list of the prev of first node is nullptr
      if (first_prev == nullptr){
        first = curr_first -> prev;
        temp -> prev = first_prev;
        continue;
      }
      if (first_prev != nullptr){
        first_prev -> next = temp;
        temp -> prev = first_prev;
      }
      continue;
    }
    else{
      first_prev = curr_first;
      curr_first = curr_first -> next;
    }
  }
  if (curr_first == nullptr && curr_second != nullptr){
    first_prev -> next = curr_second;
    curr_second -> prev = first_prev;
  }

  return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 0) return nullptr;
  if (chainLength == 1) return start;

  ListNode* new_start = start;
  for (int i = 0; i < chainLength/2; i++){
    new_start = new_start -> next;
  }
  ListNode* new_start_prev = new_start -> prev;
  new_start -> prev = nullptr;
  new_start_prev -> next = nullptr;

  ListNode* first_half = mergesort(start, chainLength/2);
  ListNode* second_half = mergesort(new_start, chainLength - chainLength/2);
  return merge(first_half, second_half);

}
