/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
using namespace std;
#include <iostream>

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
  // solve for the hash value of a given key.
  elems++;
  // if the table don't need to be resized, we can just insert it directly.
  if (!shouldResize())  {
    unsigned int hashed = hashes::hash(key, size);
    pair<K,V> some_pair(key, value);
    table[hashed].push_front(some_pair);
  }

  else {
    pair<K,V> some_pair(key, value);
    resizeTable();
    unsigned int hashed = hashes::hash(key, size);
    table[hashed].push_front(some_pair);
  }
  return;
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
     for (size_t idx = 0; idx < size ; idx++){
       for (auto it = table[idx].begin(); it != table[idx].end(); ++it){
         if ((it -> first) == key) {
           table[idx].erase(it);
           break;
         }
       }
     }
    return;
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
  V returned_val = V();
  for (size_t idx = 0; idx < size ; idx++){
    for (auto it = table[idx].begin(); it != table[idx].end(); ++it){
      if ((it -> first) == key) {
        returned_val = it -> second;
        break;
      }
    }
  }
  return returned_val;
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
     list<pair<K, V>>* new_table = new list<pair<K,V>>[findPrime(size*2)];
     for (size_t idx = 0; idx < size; idx++){
       for (auto it = table[idx].begin(); it != table[idx].end(); ++it){
         unsigned int hashed = hashes::hash(it -> first, findPrime(size*2));
         new_table[hashed].push_front(*it);
       }
     }
     //now everything is filled in, we delete the original list and swap.
     delete[] table;
     table = new_table;
     size = findPrime(size*2);
}
