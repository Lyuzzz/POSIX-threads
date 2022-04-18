/******************************************************************************************
 * Assignment 2
 * Zhiyu Li		    #821009794			cssc1433
 * 02/25/22
 ******************************************************************************************/
#include "dicttree.h"



/*************************************************************************
 * insert words from outside file to tree
 * @param pointer node, string word, integer position for recursion
 *************************************************************************/
void insertToDic(dictNode *&r, string w, int pos){

    dictNode *node = r;
    char word = w[pos];

//Determine which node the letter here should be in
    if(word >= 'a' && word <= 'z'){
        if(node -> next[word - 'a'] == NULL){
            node -> next[word - 'a'] = new dictNode();

        }

        node = node -> next[word - 'a'];


    }else if (word >= 'A' && word <= 'Z'){
        if(node -> next[word - 'A'] == NULL){
            node -> next[word - 'A'] = new dictNode();
        }

        node = node -> next[word - 'A'];

    }else if( word = 39){
        if(node -> next['A' - word] == NULL){
            node -> next['A' - word] = new dictNode();
        }

        node = node -> next['A' - word];

    }

//after recursion, determine there is an end of word length or not
    if(pos == w.length()-1){
        node -> isWord = true;

        return;
    }

    insertToDic(node, w, pos+1);
}




/*************************************************************************
 * count how many words start with in the tree
 * @param pointer node, pointer node for stop pointing next node and counting words, string word
 *************************************************************************/
void countWords(dictNode *node, dictNode *nodeptr, string p) {
    dictNode *ptr = nodeptr;

    //determine the flag, and counting word by pointing to numOfW
    if(node -> isWord == true){
        ptr -> numOfW++;
    }
    for(int i = 0; i <= 26; i++){
        if(node -> next[i] != nullptr){

            countWords(node->next[i], nodeptr, p);

        }else{
            continue;
        }
    }

}


/*************************************************************************
 * search if the tree contains the word
 * @param pointer ndoe, string word
 * @return true if the word in the tree
 *************************************************************************/
bool searchDic(dictNode *&r, string w){

    dictNode *node = r;
    for(int i = 0; i <= w.length()-1; i++){
        char word = w[i];

        if(word >= 'a' && word <= 'z'){
            if(node -> next[word - 'a'] == NULL){

                return false;
            }
            node = node -> next[word - 'a'];



        }else if (word >= 'A' && word <= 'Z'){
            if(node -> next[word - 'A'] == NULL){

                return false;
            }
            node = node -> next[word - 'A'];

        }else if( word = '\''){
            if(node -> next['A' - word] == NULL){

                return false;
            }

            node = node -> next['A' - word];
        }


    }

    return node -> isWord;



}


/*************************************************************************
 * search the prefix in the tree, and call countWords inside the function
 * @param pointer node, string word or prefix
 * @return number of words in the tree
 *************************************************************************/
int searchPrefix(dictNode *&r, string p){

    dictNode *node = r;
    for(int i = 0; i <= p.length()-1; i++){
        char word = p[i];

        if(word >= 'a' && word <= 'z'){
            if(node -> next[word - 'a'] == NULL){

                return false;
            }
            node = node -> next[word - 'a'];



        }else if (word >= 'A' && word <= 'Z'){
            if(node -> next[word - 'A'] == NULL){

                return false;
            }
            node = node -> next[word - 'A'];

        }else if( word = '\''){
            if(node -> next['A' - word] == NULL){

                return false;
            }

            node = node -> next['A' - word];
        }


    }


//determine if there are prefixes in the tree, and count them up
    dictNode *nodeptr = node;
    if(node -> numOfW == 0){
        countWords(node, nodeptr, p);
    }


    return node ->numOfW;





}

