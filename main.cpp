#include <iostream>
#include "code.h"
#include "deanonymization.h"

using namespace std;

int main(void)
{
    readProfiles();

    cout << "1.Create profile\n2.De-anonymize\n";

    int a;
    cin >> a;

    if(a==1)
    {
        profileSetUp();
    }
    else if(a==2)
    {
        deanonymize();
    }

    writeProfiles();

    return 0;
}
