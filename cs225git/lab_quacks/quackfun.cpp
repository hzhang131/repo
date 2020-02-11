/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    // stub return value (0 for primitive types). Change this!
    // Note: T() is the default value for objects, and 0 for
    // primitive types
    T realsum = T();
    T temp = T();
    if (s.empty() == true) {
      return T();
    }
    else{
      realsum += s.top();
      temp = s.top();
      s.pop();
      realsum += sum(s);
      s.push(temp);
    }
    return realsum;

}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    // @TODO: Make less optimistic
    //queue<char>* copy = new queue<char>(input);
    //push everything onto the stack for a copy.
    stack<char> copy;
    bool flag = true;
    int right_bracket_count = 0;
    int left_bracket_count = 0;
    int input_size = input.size();

    for (int i = 0; i < input_size; i++){
      if (input.front() == ']') right_bracket_count++;
      if (input.front() == '[') left_bracket_count++;
      if (right_bracket_count > left_bracket_count) flag = false;
      input.push(input.front());
      input.pop();
    }
    if (right_bracket_count != left_bracket_count) flag = false;
    return flag;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{

    stack<T> s;
    unsigned segment = 1;
    unsigned total = 1;
    unsigned q_size = q.size();
    T temp = T();

    if (q.size() <= 1) return;

    while (total <= q.size()){
      if (segment % 2 == 1){
        for (unsigned i = 0; i < segment; i++){
          temp = q.front();
          q.pop();
          q.push(temp);
        }
        segment++;
        total += segment;
        continue;
      }

      else {
        //move to stack
        for (unsigned i = 0; i < segment; i++){
          temp = q.front();
          q.pop();
          s.push(temp);
        }

        //move from stack to queue.
        for (unsigned i = 0; i < segment; i++){
          temp = s.top();
          s.pop();
          q.push(temp);
        }

        //move to next segment.
        segment++;
        total += segment;
        continue;
      }
    }
    //pop and then push the leftovers.

    for (unsigned i = 0; i < q_size - (total - segment); i++){
      temp = q.front();
      q.pop();
      s.push(temp);
    }

    for (unsigned i = 0; i < q_size - (total - segment); i++){
      temp = s.top();
      s.pop();
      q.push(temp);
    }
    return;
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T temp_stack = T(); // rename me
    T temp_queue = T(); // rename :)
    if (s.size() == 1) {
      if (s.top() != q.front())
      retval = false;
      return retval;
    }
    temp_stack = s.top();
    s.pop();
    retval = verifySame(s, q);
    temp_queue = q.front();
    q.pop();
    q.push(temp_queue);
    s.push(temp_stack);
    if (q.front() != s.top()){
      retval = false;
      return retval;
    }

    // at last, pop and push last element of queue.
    if (s.size() == q.size()){
    temp_queue = q.front();
    q.pop();
    q.push(temp_queue);
  }
    
    // Your code here
    return retval;
}

}
