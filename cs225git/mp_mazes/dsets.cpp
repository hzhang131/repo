/* Your code here! */
#include "dsets.h"
DisjointSets::DisjointSets(){
    /* Nothing */
}

DisjointSets::~DisjointSets(){
    /* Nothing */
}
void DisjointSets::addelements(int num){
    while (num > 0){
        set.push_back(-1);
        num--;
    }
    return;
}

/** Using path compression algorithm given in lecture.
 *  Directly copied from the Slides.
 * */
int DisjointSets::find(int elem){
    // At root, return the index.
    if (set[elem] < 0) return elem;
    /** If not at the root recurse and on the return update parent
     *  to be the root.
     * */
    else {
        int root = find(set[elem]);
        set[elem] = root;
        return root;
    }
    return -1;
}

void DisjointSets::setunion(int a, int b){
    if (find(a) == find(b)) return;
    int newSize = set[find(a)] + set[find(b)];
    // If a is larger (ie. more negative), then we let the b join the larger set.
    if (set[find(a)] < set[find(b)]){
        set[find(a)] = newSize;
        set[find(b)] = find(a);
    }
    else {
        set[find(a)] = find(b);
        set[find(b)] = newSize;
    }
    return;
}

int DisjointSets::size(int elem){
    int idx = find(elem);
    int size = set[idx] * (-1);
    return size;
}

int DisjointSets::size(){
    return (int) set.size();
}
