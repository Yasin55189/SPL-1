#include <iostream>
#include "profiler.h"

using namespace std;

int main(void)
{
    readProfiles();

    cout << "1.Create profile\n2.De-anonymize\n3.Exit\n";

    int a;
    cin >> a;

    while(true)
    {
        if(a==1)
        {
            profileSetUp();
        }
        else if(a==2)
        {
            deanonymize();
        }
        else if(a==3)
            break;

        cout << "1.Create profile\n2.De-anonymize\n3.Exit\n";
        cin >> a;
    }

    writeProfiles();

    return 0;
}
