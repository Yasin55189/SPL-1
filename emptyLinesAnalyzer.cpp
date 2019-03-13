#include "emptyLinesAnalyzer.h"

#include <iostream>
#include <fstream>

using namespace std;

double percentageOfEmptyLinesAnalyzer (string fileName)
{
    double result;
    int emptyLines=0;
    int total=0;

    ifstream iCod;
    iCod.open(fileName.c_str());
    if(iCod.is_open())
    {
        string s;
        getline(iCod,s);
        while(!iCod.eof())
        {
            total++;
            if(s.size()==0||s.find_first_not_of(' ')==string::npos||s.find_first_not_of('\t')==string::npos)
                emptyLines++;
            getline(iCod,s);
        }
        iCod.close();
    }

    result = (double) (emptyLines * 100.0) / total;

    return result;
}
