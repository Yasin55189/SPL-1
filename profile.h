#include <iostream>
#include <vector>
#include <fstream>
#include "analysis.h"

using namespace std;

struct profile
{
    int id;

    double percentageOfWhiteSpace;
    double varianceOfPercentageOfWhiteSpace;
};

vector <profile> profiles;

vector <profile> :: iterator itr2;

void readProfiles ()
{
    ifstream iPro;
    iPro.open("profiles.txt");
    if(iPro.is_open())
    {
        int a;
        double b, c;

        iPro >> a;

        while(!iPro.eof())
        {
            iPro >> b >> c;

            profile p;

            p.id=a;
            p.percentageOfWhiteSpace=b;
            p.varianceOfPercentageOfWhiteSpace=c;

            profiles.push_back(p);

            iPro >> a;
        }
    }
    iPro.close();
}

void writeProfiles ()
{
    ofstream oPro;
    oPro.open("profiles.txt");
    if(oPro.is_open())
    {
        for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
        {
            oPro << (*itr2).id << ' ' << (*itr2).percentageOfWhiteSpace
            << ' ' << (*itr2).varianceOfPercentageOfWhiteSpace << endl;
        }
    }
    oPro.close();
}

void profileSetUp ()
{
    int a;
    double sum=0;
    cin >> a;

    int numberOfCodes = 30;

    string s [numberOfCodes];

    for(int i=0;i<numberOfCodes;i++)
    {
        cin >> s[i];
        sum+=percentageOfWhiteSpaceAnalyzer(s[i]);
    }

    double spacePer = sum / numberOfCodes;

    double SDsum=0;

    for(int i=0;i<numberOfCodes;i++)
    {
        SDsum+=(percentageOfWhiteSpaceAnalyzer(s[i])-spacePer)*(percentageOfWhiteSpaceAnalyzer(s[i])-spacePer);
    }

    double SD = SDsum / numberOfCodes;

    profile p;

    p.id = a;
    p.percentageOfWhiteSpace = spacePer;
    p.varianceOfPercentageOfWhiteSpace=SD;

    profiles.push_back(p);
}

profile tempProfile (string s)
{
    int a = -1;

    double spacePer = percentageOfWhiteSpaceAnalyzer(s);

    profile p;

    p.id = a;
    p.percentageOfWhiteSpace = spacePer;

    return p;
}

