#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

#include <vector>
#include <map>
#include <iostream>

using namespace std;

double mean (string s, vector <string> listOfFiles, double (*func) (string));
double variance (string s, double mean, vector <string> listOfFiles, double (*func) (string));
double alphaParameter (double mean, double variance);
double betaParameter (double mean, double variance);
double betaFunction (double mean, double variance);
double betaDistribution (double mean, double variance, double tempMean);
int matchingRankSum (map <int,double> proMap);

#endif // STAT_H_INCLUDED
