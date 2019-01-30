#include <iostream>
#include <vector>
#include <fstream>
#include "analysis.h"

using namespace std;

struct profile
{
    int id;
    double percentageOfWhiteSpace;
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
        double b;

        iPro >> a;

        while(!iPro.eof())
        {
            iPro >> b;

            profile p;

            p.id=a;
            p.percentageOfWhiteSpace=b;

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
            oPro << (*itr2).id << ' ' << (*itr2).percentageOfWhiteSpace << endl;
        }
    }
    oPro.close();
}

void profileSetUp ()
{
    int a;
    double sum=0;
    cin >> a;

    for(int i=0;i<20;i++)
    {
        string s;
        cin >> s;
        sum=percentageOfWhiteSpaceAnalyzer(s);
    }
    double spacePer = sum / 20.0;

    profile p;

    p.id = a;
    p.percentageOfWhiteSpace = spacePer;

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

