/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"
#include <algorithm>
#include <string> 
using namespace std;


/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict dt,
                                    const string& word_list_fname)
{
    static map<string, bool> look_up;
    vector<std::tuple<std::string, std::string, std::string>> ret;
    vector<string> words;
    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
        words.push_back(word);
    }
    }

    for (const auto& s: words){
        string first = "";
        string second = "";
        if (look_up.find(s) != look_up.end()) continue;
        for (const auto& x: words){
            if (s.substr(1, s.length()) == x) {
                first = x;
                break;
            }
        }
        for (const auto& y: words){
            if (s[0] + s.substr(2, s.length()) == y) {
                second = y;
                break;
            }
        }

        if (first != "" && second != ""){
            if (dt.homophones(s, first) && dt.homophones(s, second)){
                ret.push_back(make_tuple(s, first, second));
                look_up[s] = true; look_up[first] = true; look_up[second] = true;
            }
        }
    }
    return ret;
}
