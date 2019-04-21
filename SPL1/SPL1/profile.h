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

    double percentageOfEmptyLines;
    double varianceOfPercentageOfEmptyLines;
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
        double b, c, d, e;

        iPro >> a;

        while(!iPro.eof())
        {
            iPro >> b >> c >> d >> e;

            profile p;

            p.id=a;

            p.percentageOfWhiteSpace=b;
            p.varianceOfPercentageOfWhiteSpace=c;

            p.percentageOfEmptyLines=d;
            p.varianceOfPercentageOfEmptyLines=e;

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
            << ' ' << (*itr2).varianceOfPercentageOfWhiteSpace
            << ' ' << (*itr2).percentageOfEmptyLines
            << ' ' << (*itr2).varianceOfPercentageOfEmptyLines << endl;
        }
    }
    oPro.close();
}

void profileSetUp ()
{
    int a;

    double sum=0;
    double sum1=0;

    cin >> a;

    int numberOfCodes = 30;

    string s [numberOfCodes];

    for(int i=0;i<numberOfCodes;i++)
    {
        cin >> s[i];
        sum+=percentageOfWhiteSpaceAnalyzer(s[i]);
        sum1+=percentageOfEmptyLinesAnalyzer(s[i]);
    }

    double spacePer = sum / numberOfCodes;
    double empLinPer = sum1 / numberOfCodes;

    double SDsum=0;
    double SDsum1=0;

    for(int i=0;i<numberOfCodes;i++)
    {
        SDsum+=(percentageOfWhiteSpaceAnalyzer(s[i])-spacePer)*(percentageOfWhiteSpaceAnalyzer(s[i])-spacePer);
        SDsum1+=(percentageOfEmptyLinesAnalyzer(s[i])-empLinPer)*(percentageOfEmptyLinesAnalyzer(s[i])-empLinPer);
    }

    double SD = SDsum / numberOfCodes;
    double SD1 = SDsum1 / numberOfCodes;

    profile p;

    p.id = a;

    p.percentageOfWhiteSpace = spacePer;
    p.varianceOfPercentageOfWhiteSpace=SD;

    p.percentageOfEmptyLines = empLinPer;
    p.varianceOfPercentageOfEmptyLines=SD1;

    profiles.push_back(p);
}

profile tempProfile (string s)
{
    int a = -1;

    double spacePer = percentageOfWhiteSpaceAnalyzer(s);
    double empLinPer = percentageOfEmptyLinesAnalyzer(s);

    profile p;

    p.id = a;

    p.percentageOfWhiteSpace = spacePer;

    p.percentageOfEmptyLines = empLinPer;

    return p;
}

