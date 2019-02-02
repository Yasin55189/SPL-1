#include <iostream>
#include "profile.h"
#include <map>
#include <math.h>

using namespace std;

map <int,double> proMap;
map <int,double> :: iterator mapItr;

void deanonymize ()
{
    string s;
    cin >> s;

    profile temp = tempProfile(s);

    for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
    {
        double a = (((1-((*itr2).percentageOfWhiteSpace/100))/((*itr2).varianceOfPercentageOfWhiteSpace/10000))
        -(1/((*itr2).percentageOfWhiteSpace/100)))*
        (((*itr2).percentageOfWhiteSpace/100)*((*itr2).percentageOfWhiteSpace/100));

        double b = a*((1/((*itr2).percentageOfWhiteSpace/100))-1);

        double betaFunc =((pow(2*3.1416,0.5))*(pow(a,a-0.5)*pow(b,b-0.5)))/pow((a+b),a+b-0.5);

        double betaDis = (pow(temp.percentageOfWhiteSpace/100,a-1)*pow(1-temp.percentageOfWhiteSpace/100,b-1))
        /betaFunc;



        a = (((1-((*itr2).percentageOfEmptyLines/100))/((*itr2).varianceOfPercentageOfEmptyLines/10000))
        -(1/((*itr2).percentageOfEmptyLines/100)))*
        (((*itr2).percentageOfEmptyLines/100)*((*itr2).percentageOfEmptyLines/100));

        b = a*((1/((*itr2).percentageOfEmptyLines/100))-1);

        betaFunc = ((pow(2*3.1416,0.5))*(pow(a,a-0.5)*pow(b,b-0.5)))/pow((a+b),a+b-0.5);

        double betaDis1 = (pow(temp.percentageOfEmptyLines/100,a-1)*pow(1-temp.percentageOfEmptyLines/100,b-1))/betaFunc;



        double rankSum = betaDis*betaDis1;

        proMap[(*itr2).id]=rankSum;
    }

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

    cout << deAnoID << endl;
}
