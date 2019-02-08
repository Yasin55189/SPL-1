#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include "whiteSpaceAnalyzer.h"
#include "emptyLinesAnalyzer.h"
#include "stat.h"

using namespace std;

struct profile
{
    int id;

    double percentageOfWhiteSpace;
    double varianceOfPercentageOfWhiteSpace;

    double percentageOfEmptyLines;
    double varianceOfPercentageOfEmptyLines;
};

void readProfiles ();

void writeProfiles ();

void profileSetUp ();

profile tempProfile (string);

void deanonymize ();

#endif // PROFILER_H_INCLUDED
