/******************************************************************************************
 * Assignment 2
 * Zhiyu Li		    #821009794			cssc1433
 * 02/25/22
 ******************************************************************************************/

#include "populatetree.h"

/*************************************************************************
 * create populatetree thread
 * @param pointer ptr
 *************************************************************************/
void* populateTree(void* ptr) {
    // reference to the EXEC_STATUS pointer by parameter
    EXEC_STATUS *st = (EXEC_STATUS *) ptr;
    //allocate memory for numOfCharsProcessedFromFile
   st->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = new long();

   // initialize variables for streaming file in
    ifstream dictFile;
    dictFile.open(st->filePath[DICTSRCFILEINDEX]);
    string dictWords;
    // If there is a file that cannot stream in
    if(!dictFile){
        cout<< "Unable to open <<" << st->filePath[DICTSRCFILEINDEX]<< ">>"<<endl;
    }

    //insert the word from outside file into a variable.
    while (!dictFile.eof()) {
        while (getline(dictFile, dictWords)) {

            //get the length of each line include the line feed character at the end of each line
            st->numCharDict = dictWords.length() + 1;
            insertToDic(st->dictRootNode, dictWords, 0);

            //track the words count
            st->wordCountInFile[DICTSRCFILEINDEX]++;

            //get number of chars read in and processed
            *st->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] += st->numCharDict;


            //get the runtime progress
            st->peDict = (double) *st->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] /
                         (double) st->totalNumOfCharsInFile[DICTSRCFILEINDEX];


        }

    }

    //once the pthread completed, make it true;
    st->taskCompleted[DICTSRCFILEINDEX] = true;
    pthread_exit(0);


}