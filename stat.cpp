#include <iostream>
#include <math.h>
#include "stat.h"
#include <vector>
#include <map>

using namespace std;

double mean (string s, vector <string> listOfFiles, double (*func) (string))
{
    double sum = 0;

    vector <string> :: iterator stringItr;

    for(stringItr=listOfFiles.begin();stringItr!=listOfFiles.end();stringItr++)
    {
        string path = s+ "\\" + *stringItr;

        sum+=func(path);
    }

    double meanPercentage = sum / 30;

    return meanPercentage;
}

double variance (string s, double mean, vector <string> listOfFiles, double (*func) (string))
{
    double squaredSumOfDifferences=0;

    vector <string> :: iterator stringItr;

    for(stringItr=listOfFiles.begin();stringItr!=listOfFiles.end();stringItr++)
    {
        string path = s+ "\\" + *stringItr;

        squaredSumOfDifferences+=(func(path)-mean)
        *(func(path)-mean);
    }

    double varianceOfPercentage = squaredSumOfDifferences/30;

    return varianceOfPercentage;
}

double alphaParameter (double mean, double variance)
{
    return (((1-(mean/100))/(variance/10000))
        -(1/(mean/100)))*
        ((mean/100)*(mean/100));
}

double betaParameter (double mean, double variance)
{
    return (alphaParameter(mean,variance))*((1/(mean/100))-1);
}

double betaFunction (double mean, double variance)
{
    double a = alphaParameter(mean,variance);
    double b = betaParameter(mean,variance);
    return ((pow(2*3.1416,0.5))*(pow(a,a-0.5)*pow(b,b-0.5)))/pow((a+b),a+b-0.5);
}

double betaDistribution (double mean, double variance, double tempMean)
{
    double a = alphaParameter(mean,variance);
    double b = betaParameter(mean,variance);
    double betaFunctionValue = betaFunction(mean,variance);
    return (pow(tempMean/100,a-1)*pow(1-(tempMean/100),b-1))/betaFunctionValue;
}

int matchingRankSum (map <int,double> proMap)
{
    map <int,double> :: iterator mapItr;

    double maximum=0;
    int deAnoID=0;

    for(mapItr=proMap.begin();mapItr!=proMap.end();mapItr++)
    {
        if(mapItr->second>maximum)
        {
            maximum=mapItr->second;
            deAnoID=mapItr->first;
        }
    }

    return deAnoID;
}


