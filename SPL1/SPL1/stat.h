#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

#include <vector>
#include <map>
#include <iostream>

using namespace std;

double mean (vector <double> vec);
double variance (double mean,vector <double> vec);
double alphaParameter (double mean, double variance);
double betaParameter (double mean, double variance);
double betaFunction (double mean, double variance);
double betaDistribution (double mean, double variance, double tempMean);
double normalDistribution (double mean, double variance, double tempMean);
int matchingRankSum (map <int,double> proMap);

#endif // STAT_H_INCLUDED
