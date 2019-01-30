#include <iostream>
#include "profile.h"

using namespace std;

void deanonymize ()
{
    string s;
    cin >> s;

    profile temp = tempProfile(s);

    for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
    {
        if((*itr2).percentageOfWhiteSpace+5>temp.percentageOfWhiteSpace
           &&(*itr2).percentageOfWhiteSpace-5<temp.percentageOfWhiteSpace)
        {
            cout << (*itr2).id << endl;
        }
    }
}
