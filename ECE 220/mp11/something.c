/* malloc the parent node. */
if (par == NULL) par = (node_t*) malloc(sizeof(node_t));
/* malloc the current node. */
node_t* pointer = (node_t*) malloc(sizeof(node_t));
/* Base case: build the bottom nodes. */
if (n == num_modules - 1){
  /* Malloc and set the bottom left node. */

  pointer -> parent = par;
  pointer -> left = pointer -> right = NULL;
  pointer -> cutline = UNDEFINED_CUTLINE;
  pointer -> module = modules + n;
  par -> left = pointer;
  /* Malloc and set the bottom right node. */
  node_t* ptr = (node_t*) malloc(sizeof(node_t));
  ptr -> parent = par;
  ptr -> left = ptr -> right = NULL;
  ptr -> cutline = UNDEFINED_CUTLINE;
  ptr -> module = modules + n - 1;
  par -> right = ptr;

  return pointer;
}
/* Build the next parent node. */
pointer -> module = NULL;
pointer -> cutline = V;
pointer -> parent = par;
/* Recursive case: Build next parent node.*/
if (!par){
  /*Build right child. */
  node_t* ptr = (node_t*) malloc(sizeof(node_t));
  ptr -> parent = par;
  ptr -> left = ptr -> right = NULL;
  ptr -> module = modules + n - 1;
  ptr -> cutline = UNDEFINED_CUTLINE;
  par -> right = ptr;
  /* Build left child (future parent node). */
  par -> left = pointer;
}
  /* Recursively call the slicing tree function. */
  return init_slicing_tree(pointer, n+1);

  int get_total_resource(node_t* ptr)
  {
    int total = 0;
    if ((ptr -> cutline) != UNDEFINED_CUTLINE){
      /* Traverse the left branches.. */
      get_total_resource (ptr -> left);
      /* Analyze current node. */
      if ((ptr -> cutline) == UNDEFINED_CUTLINE)
      total += ptr -> module -> resource;
      /*Traverse the right branches. */
      get_total_resource (ptr -> right);
    }
    return total;
  }



  node_t* init_slicing_tree(node_t* par, int n) {

    assert(n >= 0 && n < num_modules);


    if (par == NULL)
    par = (node_t*)malloc(sizeof(node_t));

   /* malloc a new node */
    node_t *ptr = (node_t *)malloc(sizeof(node_t));

   /* base case which we assign the data to the left and right nodes */
    if (n == num_modules - 1){

  /* assign the data for the last module */
   ptr->module = &(modules[n]);
   ptr->cutline = UNDEFINED_CUTLINE;
   ptr->parent = par;
   ptr->left = NULL;
   ptr->right = NULL;

   par->left = ptr;


   node_t *ptr_right = (node_t *)malloc(sizeof(node_t));


   ptr_right->module = &(modules[n-1]);
   ptr_right->cutline = UNDEFINED_CUTLINE;
   ptr_right->parent = par;
   ptr_right->left = NULL;
   ptr_right->right = NULL;


   par->right = ptr_right;

   return ptr;
   }


   ptr->module = NULL;
   ptr->cutline = V;
   ptr->parent = par;

   if(par != NULL){
   /* malloc a new node for ptr's right child */
   node_t *right = (node_t *)malloc(sizeof(node_t));


   right->module = &(modules[n-1]);
   right->cutline = UNDEFINED_CUTLINE;
   right->parent = par;
   right->left = NULL;
   right->right = NULL;

   par->left = ptr;

  }
    init_slicing_tree(ptr, n+1);
    return ptr;
  }
  /*

  int get_total_resource(node_t* ptr)
  {
    // TODO:
      /* initialize sum to be zero */
  int sum = 0;
      /* find the base case*/
      if ((ptr->cutline) == UNDEFINED_CUTLINE){
          return ptr->module->resource;
  }
      /* recursively call the functions until all the resources are summed */
      if ((ptr->cutline) != UNDEFINED_CUTLINE){
          sum += get_total_resource(ptr->left);
          sum += get_total_resource(ptr->right);
  }
  return sum;
  }

*/







  */

  void postfix_traversal(node_t* ptr, int* nth, expression_unit_t* expression) {

    /* Base case ... */
    if (!ptr) return;
    if (ptr -> left != NULL) postfix_traversal(ptr -> left, nth, expression);
    if (ptr -> right != NULL) postfix_traversal(ptr -> right, nth, expression);

    else if (ptr -> module != NULL) {
      expression[*nth].module = ptr -> module;
      expression[*nth].cutline = UNDEFINED_CUTLINE;
    }
    else {
      expression[*nth].cutline = ptr -> cutline;
      expression[*nth].module = NULL;
    }
    *nth = *nth + 1;
    /* Below are the recursive cases. */

    return;
    // TODO:
  }

  int is_in_subtree(node_t* a, node_t* b) {
    // TODO: (remember to modify the return value appropriately)
    /* If they are the same node, then a should be in b's subtree and vice versa. */
    if (a == b) return 1;
    /* If a is an internal node AND */
    /* If the left child or the right child of node a points to node b, then it is in the subtree. */
    if (is_internal_node(a)) return (is_in_subtree(a, b -> right) || is_in_subtree(a, b -> left));
    return 0;
  }
