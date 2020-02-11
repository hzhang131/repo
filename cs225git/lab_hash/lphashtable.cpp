/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"
#include <iostream>
using namespace std;
template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    elems++;
    if (!shouldResize()){
      unsigned int hashed = hashes::hash(key,size);
      while (should_probe[hashed] == true){
        hashed = (hashed + 1) % size;
      }
      //then we can insert.
      table[hashed] = new pair<K,V>(key,value);
      should_probe[hashed] = true;
    }
    else{
      resizeTable();
      unsigned int hashed = hashes::hash(key,size);
      while (should_probe[hashed] == true){
         hashed = (hashed + 1) % size;
       }
      //then we can insert.
      table[hashed] = new pair<K,V>(key,value);
      should_probe[hashed] = true;
    }

    return;
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
     for (size_t idx = 0; idx < size; idx++){
      if (table[idx] != nullptr){
        if (table[idx] -> first == key){
          delete table[idx];
          table[idx] = nullptr;
          should_probe[idx] = false;
          break;
        }
      }
     }
     return;
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{

    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    size_t index = -1;
    for (size_t i = 0; i < size; i++){
      if (table[i] != nullptr){
        if (table[i] -> first == key){
          index = i;
          break;
        }
      }
    }
    return index;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

     pair<K, V>** new_table = new pair<K, V>*[findPrime(size*2)];
     //clear the should_probe flag.
     delete[] should_probe;
     should_probe = new bool[findPrime(size*2)];
      for (size_t idx = 0; idx < findPrime(size*2); idx++){
        should_probe[idx] = false;
        new_table[idx] = nullptr;
      }

     for (size_t idx = 0; idx < size; idx++){
       //take the original pair from the old table.
       if (table[idx] != nullptr){
         pair<K,V>* temp = table[idx];
         unsigned int hashed = hashes::hash(temp -> first,findPrime(size*2));
          while (should_probe[hashed] == true){
            hashed = (hashed+1) % findPrime(size*2);
         }
         new_table[hashed] = temp;
         should_probe[hashed] = true;
       }
     }

     delete[] table;
     table = new_table;
     size = findPrime(size*2);


     return;
   }
