#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <streambuf>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#ifndef A_02_DICTTREE_H
#define A_02_DICTTREE_H


using namespace std;

#define NUMOfCHARS 27 /* a-z plus ' */




//struct of nodes
struct dictNode{
// isWord is true if the node represents the
// last character of a word
    bool isWord;
    int numOfW;

// Collection of nodes that represent subsequent characters in
// words. Each node in the next dictNode*
// array corresponds to a particular character that continues
// the word if the node at the array index is NOT NULL:
// e.g., if next[0] is NOT NULL, it means ‘a’ would be
// one of the next characters that continues the current word;
// while next[0] being NULL means there are no further words
// with the next letter as ‘a’ along this path.
    struct dictNode *next[NUMOfCHARS];

    dictNode(){
        isWord = false;
        numOfW = 0;
        for(int i = 0; i <= 26; i++){
            next[i] = NULL;
        }
    }

};


/*************************************************************************
 * insert words from outside file to tree
 *************************************************************************/
void insertToDic(dictNode *&r, string w, int pos);


/*************************************************************************
 * count how many words start with in the tree
 *************************************************************************/
void countWords(dictNode *node, dictNode *nodeptr, string p);


/*************************************************************************
 * search if the tree contains the word
 *************************************************************************/

bool searchDic(dictNode *&r, string w);


/*************************************************************************
 * search the prefix in the tree, and call countWords inside the function
 *************************************************************************/
int searchPrefix(dictNode *&r, string p);





#endif //A_02_DICTTREE_H
