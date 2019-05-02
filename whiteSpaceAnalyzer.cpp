#include "whiteSpaceAnalyzer.h"

#include <iostream>
#include <fstream>

using namespace std;

double percentageOfWhiteSpaceAnalyzer (string fileName)
{
    double result=0;
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
        iCod.close();
    }

    result = (double) (space * 100.0) / total;

    if(result>=0.0&&result<=100.0)
        return result;

    return -1;
}
