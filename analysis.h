#include <iostream>

using namespace std;

double percentageOfWhiteSpaceAnalyzer (string fileName)
{
    double result;
    int space=0;
    int total=0;

    ifstream iCod;
    iCod.open(fileName.c_str());
    if(iCod.is_open())
    {
        char c;
        iCod.get(c);
        while(!iCod.eof())
        {
            if(c!='\n')
                total++;
            if(c==' ')
                space++;
            iCod.get(c);
        }
    }
    iCod.close();

    result = (double) (space * 100.0) / total;

    return result;
}
