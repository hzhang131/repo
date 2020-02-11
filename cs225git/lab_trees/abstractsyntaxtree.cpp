#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    if (root == nullptr) return 0;
    return eval_helper(root);
}

double AbstractSyntaxTree::eval_helper(AbstractSyntaxTree::Node* subRoot) const{
    std::string stuff = subRoot -> elem;
    if (stuff == "+")
      return eval_helper(subRoot -> left) + eval_helper(subRoot -> right);
    else if (stuff == "-")
      return eval_helper(subRoot -> left) - eval_helper(subRoot -> right);
    else if (stuff == "*")
      return eval_helper(subRoot -> left) * eval_helper(subRoot -> right);
    else if (stuff == "/")
      return eval_helper(subRoot -> left) / eval_helper(subRoot -> right);
    else
      return std::stod(stuff);
}
