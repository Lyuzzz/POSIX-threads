/******************************************************************************************
 * Assignment 2
 * Zhiyu Li		    #821009794			cssc1433
 * 02/25/22
 ******************************************************************************************/
#include "countwords.h"

/*************************************************************************
 * create countwords thread
 * @param pointer ptr
 *************************************************************************/
void* countWordsA(void* ptr){
    // reference to the EXEC_STATUS pointer by parameter
    EXEC_STATUS *st = (EXEC_STATUS*)ptr;
    //allocate memory for numOfCharsProcessedFromFile
    st->numOfCharsProcessedFromFile[TESTFILEINDEX] = new long();

    // initialize variables for streaming file in
    ifstream testFile;
    testFile.open(st ->filePath[TESTFILEINDEX]);
    // If there is a file that cannot stream in
    if(!testFile){
        cout<< "Unable to open <<" << st->filePath[TESTFILEINDEX]<< ">>"<<endl;
    }

    string dictWords;
    string testWord{};
    const char *delimiters = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

    // for stream to a output file
    ofstream outFile("countwords_output.txt");

    // busy waiting the populatetree thread completed
    while(st->taskCompleted[DICTSRCFILEINDEX] == false){

    }
    while(!testFile.eof()){
        while(getline(testFile, testWord)){


            //get the length of each line include the line feed character at the end of each line
            st->numCharText = testWord.length()+1;
            //cast string input to char pointer
            char *testWords = (char*)(testWord.data());
            //delimit all the delimiters
            char *testW = strtok(testWords,delimiters);
            while(testW != nullptr){
                if(searchDic(st->dictRootNode,testW)){
                    //check the minNumOfWordsWithAPrefixForPrinting
                    if( st->minNumOfWordsWithAPrefixForPrinting <= searchPrefix(st->dictRootNode,testW)){
                        outFile<<testW<<" "<< searchPrefix(st->dictRootNode,testW) << endl;
                    }

                    //track the words count
                    st->wordCountInFile[TESTFILEINDEX]++;

                }else{
                    //check the minNumOfWordsWithAPrefixForPrinting
                    if( st->minNumOfWordsWithAPrefixForPrinting <= searchPrefix(st->dictRootNode,testW)){
                        outFile<<testW<<" "<< searchPrefix(st->dictRootNode,testW) << endl;
                    }
                    //track the words count
                    st->wordCountInFile[TESTFILEINDEX]++;
                }



                testW = strtok(NULL, delimiters);
            }

            //get number of chars read in and processed
            *st ->numOfCharsProcessedFromFile[TESTFILEINDEX] += st->numCharText;
            //get the runtime progress
            st -> peText = (double) *st -> numOfCharsProcessedFromFile[TESTFILEINDEX]/ (double)st -> totalNumOfCharsInFile[TESTFILEINDEX];






        }
    }
    //once the pthread completed, make it true;
    st->taskCompleted[TESTFILEINDEX] = true;
    pthread_exit(0);

}