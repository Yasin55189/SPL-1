#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct profile
{
    int id;
    double percentageOfWhiteSpace;
    double percentageOfWhiteSpaceInSignature;
    double percentageOfProperIndentation;
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
        double b,c,d;

        iPro >> a;

        while(!iPro.eof())
        {
            iPro >> b >> c >> d;

            profile p;

            p.id=a;
            p.percentageOfWhiteSpace=b;
            p.percentageOfWhiteSpaceInSignature=c;
            p.percentageOfProperIndentation=d;

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
            oPro << (*itr2).id << ' ' << (*itr2).percentageOfWhiteSpace << ' '
            << (*itr2).percentageOfWhiteSpaceInSignature
            << ' '
            << (*itr2).percentageOfProperIndentation << endl;
        }
    }
    oPro.close();
}

