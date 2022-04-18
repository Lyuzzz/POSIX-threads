/******************************************************************************************
 * Assignment 2
 * Zhiyu Li		    #821009794			cssc1433
 * 02/25/22
 ******************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <streambuf>
#include <vector>
#include <utility>
#include <map>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stdio.h>
#include<pthread.h>
#include <sys/stat.h>
#include <unistd.h>
#include<math.h>
#include <time.h>
#include "dicttree.h"
#include "populatetree.h"
#include "countwords.h"
#include "shareddatastructure.h"

using namespace std;

/*************************************************************************
 * print out bars
 * @param pointer st
 *************************************************************************/
void printBar( EXEC_STATUS *st){


    //to print a hash mark every number of hashmarkInterval
    for(int i = 1; i <= st->hashmarkInterval; i++) {
        if (i == st->hashmarkInterval) {
            cout << '#';

        } else {
            cout << '-';

        }

    }
    cout.flush();

}





/*************************************************************************
 * create main thread
 * @param pointer ptr
 *************************************************************************/
void* mainThread(void* ptr){
    EXEC_STATUS *st = (EXEC_STATUS*)ptr;

//    //determine the percentage that progress needs to reach out
//    int j = st->numOfProgressMarks/st->numofBars;

    // pthread attribute
    pthread_attr_t pthread_attr_default;

    //thread name
    pthread_t thread1, thread2;

    //initialize pthread attribute
    pthread_attr_init(&pthread_attr_default);

    //create populatetree thread
    pthread_create(&thread1,&pthread_attr_default, &populateTree, (void*)st);
//create countwords thread
    pthread_create(&thread1,&pthread_attr_default, &countWordsA, (void*)st);
//    //loop if the progress haven't reach out the 100% yet
//    while(st->peDict < 1.0){
//
//        float progress = st->peDict;
//        //determine the progress percentage of numOfProgressMarks
//        int pos = progress * st->numOfProgressMarks;
//
//        //current position subtract previous position
//        // to determine whether is equals to the progress
//        // percentage of numOfProgressMarks or not
//        if(pos - st->peDict1 == j-1){
//
//            //print out bars
//           printBar(st);
//           //set previous position value
//           st->peDict1 = pos;
//       }
//
//
//
//
//    }
//
//    cout<<endl;
//    // if the task is completed
//    if(st->taskCompleted[DICTSRCFILEINDEX]){
//        cout<<"There are "<<st->wordCountInFile[DICTSRCFILEINDEX]<< " words in "<<st->filePath[DICTSRCFILEINDEX]<<"."<<endl;
//    }
//
//
//
//    //loop if the progress haven't reach out the 100% yet
//    while(st->peText < 1.0){
//
//        float progress = st->peText;
//        //determine the progress percentage of numOfProgressMarks
//        int pos = progress * st->numOfProgressMarks;
//
//        //current position subtract previous position
//        // to determine whether is equals to the progress
//        // percentage of numOfProgressMarks or not
//        if(pos - st->peText1 == j-1){
//
//            //print out bars
//            printBar(st);
//            //set previous position value
//            st->peText1 = pos;
//        }
//
//
//
//
//    }
//
//    cout<<endl;
//    // if the task is completed
//    if(st->taskCompleted[TESTFILEINDEX]){
//
//        cout<<"There are "<<st->wordCountInFile[TESTFILEINDEX]<< " words in "<<st->filePath[TESTFILEINDEX]<<"."<<endl;
//        pthread_exit(0);
//    }


    return 0;

}


int main(int argc, char **argv) {

    int ch;

    // initialize the variable root node
    dictNode *root = new dictNode();
    EXEC_STATUS *st = new EXEC_STATUS ();
    st -> dictRootNode = root;



    //get file path for the dictionary vocabulary file
    st->filePath[DICTSRCFILEINDEX] = argv[1];
    //get file path for the test source file
    st->filePath[TESTFILEINDEX] = argv[2];


    //store total number of characters in files,
    // total word count in files by use stat
    struct stat dictSize;
    struct stat testSize;
    stat(st->filePath[DICTSRCFILEINDEX], &dictSize);
    stat(st->filePath[TESTFILEINDEX], &testSize);
    st -> totalNumOfCharsInFile[DICTSRCFILEINDEX] = dictSize.st_size;
    st -> totalNumOfCharsInFile[TESTFILEINDEX] = testSize.st_size;


    //initialize the default value of ProgressMarks, hashmark, minNumOfWordsWithAPrefixForPrinting
    st->numOfProgressMarks = DEFAULT_NUMOF_MARKS;
    st->hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
    st->minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;

    //reach out Optional arguments, and
    // determine whether they are out of range or not
    while((ch = getopt(argc, argv, "p:h:n:")) != -1 ){
        switch(ch){
            case 'p':

                st->numOfProgressMarks = (int)atol(optarg);
                if(st->numOfProgressMarks > DEFAULT_NUMOF_MARKS || st->numOfProgressMarks <  MIN_NUMOF_MARKS){
                    st->numOfProgressMarks = DEFAULT_NUMOF_MARKS;
                }
                break;
            case 'h':
                st->hashmarkInterval = (int)atol(optarg);
                if(st->hashmarkInterval > DEFAULT_HASHMARKINTERVAL || st->hashmarkInterval <= 0 ){
                    st->hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
                }
                break;
            case 'n':
                st->minNumOfWordsWithAPrefixForPrinting = (int)atoi(optarg);
                break;
            default:
                break;
        }
    }

    st->numofBars = st->numOfProgressMarks/st->hashmarkInterval;


    // pthread attribute
    pthread_attr_t pthread_attr_default;

    //main thread
    pthread_t main;

    //initialize pthread attribute
    pthread_attr_init(&pthread_attr_default);

    //create main thread
    pthread_create(&main,&pthread_attr_default, &mainThread, (void*)st);

    int j = st->numOfProgressMarks/st->numofBars;

//loop if the progress haven't reach out the 100% yet
    while(st->peDict < 1.0){

        float progress = st->peDict;
        //determine the progress percentage of numOfProgressMarks
        int pos = progress * st->numOfProgressMarks;

        //current position subtract previous position
        // to determine whether is equals to the progress
        // percentage of numOfProgressMarks or not
        if(pos - st->peDict1 == j-1){

            //print out bars
            printBar(st);
            //set previous position value
            st->peDict1 = pos;
        }




    }

    cout<<endl;
    // if the task is completed
    if(st->taskCompleted[DICTSRCFILEINDEX]){
        cout<<"There are "<<st->wordCountInFile[DICTSRCFILEINDEX]<< " words in "<<st->filePath[DICTSRCFILEINDEX]<<"."<<endl;
    }



    //loop if the progress haven't reach out the 100% yet
    while(st->peText < 1.0){

        float progress = st->peText;
        //determine the progress percentage of numOfProgressMarks
        int pos = progress * st->numOfProgressMarks;

        //current position subtract previous position
        // to determine whether is equals to the progress
        // percentage of numOfProgressMarks or not
        if(pos - st->peText1 == j-1){

            //print out bars
            printBar(st);
            //set previous position value
            st->peText1 = pos;
        }




    }

    cout<<endl;
    // if the task is completed
    if(st->taskCompleted[TESTFILEINDEX]){

        cout<<"There are "<<st->wordCountInFile[TESTFILEINDEX]<< " words in "<<st->filePath[TESTFILEINDEX]<<"."<<endl;
        pthread_exit(0);
    }


    //relieve memory that pointer allocated
    delete(st->numOfCharsProcessedFromFile[DICTSRCFILEINDEX]);
    delete(st->numOfCharsProcessedFromFile[TESTFILEINDEX]);

    sleep(1);
    exit(0);
}
