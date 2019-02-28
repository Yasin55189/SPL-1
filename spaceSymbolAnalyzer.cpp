#include <iostream>
#include <vector>
#include "spaceSymbolAnalyzer.h"
#include "code.h"

using namespace std;

int numberOfSymbol;
int numberOfSpace;

vector <int> indexFinder (string line, string symbol)
{
    vector <int> indexVec;

    int index = 0;

    while(line.find(symbol,index)!=string::npos)
    {
        indexVec.push_back(line.find(symbol,index));

        index = (line.find(symbol,index)) + 1;
    }

    return indexVec;
}

void spaceFinder (string line, vector <int> indexVec, string symbol, int direction)
{
    vector <int> :: iterator indexItr;

    if(direction==0)
    {
        for(indexItr=indexVec.begin();indexItr!=indexVec.end();indexItr++)
        {
            int index = *indexItr;

            if(line[index-1]==' ')
                numberOfSpace++;
        }
    }
    else
    {
        for(indexItr=indexVec.begin();indexItr!=indexVec.end();indexItr++)
        {
            int index = *indexItr;

            if(line[index+symbol.length()]==' ')
                numberOfSpace++;
        }
    }
}

double percentageOfSpaceSymbolAnalyzer (string fileName, string symbol, int direction)
{
    numberOfSymbol=0;
    numberOfSpace=0;

    vector <string> inputCode = readCode(fileName);
    vector <string> :: iterator codeItr;

    for(codeItr=inputCode.begin();codeItr!=inputCode.end();codeItr++)
    {
        string line = *codeItr;

        if(line.find(symbol)==string::npos)
            continue;

        vector <int> indexVec;

        indexVec = indexFinder(line,symbol);

        spaceFinder(line,indexVec,symbol,direction);

        numberOfSymbol = numberOfSymbol + indexVec.size();
    }

    return (double) (numberOfSpace/numberOfSymbol) * 100.0;
}


