
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
#include<math.h>
#include <cmath>
#include<pthread.h>
#include "dicttree.h"
#include "shareddatastructure.h"

#ifndef A_02_POPULATETREE_H
#define A_02_POPULATETREE_H





/*************************************************************************
 * create populatetree thread
 * track number of total words and
 * number of chars read in and processed
 *************************************************************************/
void* populateTree(void* ptr);

#endif //A_02_POPULATETREE_H