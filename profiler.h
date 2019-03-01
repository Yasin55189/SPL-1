#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct profile
{
    int id;

    int numberOfSamples;

    vector <double> percentageOfWhiteSpace;
    vector <double> percentageOfEmptyLines;
    vector <double> spacePerSignature;
    vector <double> percentageOfProperIndentation;
    vector <double> percentageOfSpaceBeforeEqual;
    vector <double> percentageOfSpaceAfterEqual;
    vector <char> bracingStyle;
};

void readProfiles ();

void writeProfiles ();

void originalSetUp (int,vector<string>,string);

void additionalSetUp (vector<profile>::iterator,vector<string>,string);

void profileSetUp ();

profile tempProfile (string);

void deanonymize ();

#endif // PROFILER_H_INCLUDED
