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
            if(s.size()==0)
                emptyLines++;
            getline(iCod,s);
        }
    }
    iCod.close();

    result = (double) (emptyLines * 100.0) / total;

    return result;
}
