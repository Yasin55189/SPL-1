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

    int numberOfSamples;

    vector <double> percentageOfWhiteSpace;
    vector <double> percentageOfEmptyLines;
};

void readProfiles ();

void writeProfiles ();

void originalSetUp (int,vector<string>,string);

void additionalSetUp (vector<profile>::iterator,vector<string>,string);

void profileSetUp ();

profile tempProfile (string);

void deanonymize ();

#endif // PROFILER_H_INCLUDED
