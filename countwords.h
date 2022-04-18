#include <fstream>
#include <string>
#include <string.h>
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
#include<pthread.h>
#include<math.h>
#include "dicttree.h"
#include "shareddatastructure.h"
#ifndef A_02_COUNTWORDS_H
#define A_02_COUNTWORDS_H

#endif //A_02_COUNTWORDS_H



/*************************************************************************
 * create countwords thread
 *************************************************************************/
void* countWordsA(void* ptr);