#include <iostream>
#include <vector>
#include "indentationAnalyzer.h"
#include "code.h"

using namespace std;

int indentSize;
int bracingCounter;
int numberOfProperIndentation;

bool hasProperIndentation (string line)
{
    int temp = line.find_first_not_of(' ');
    if(temp==indentSize)
        return true;
    return false;
}

void initialIndentSize (string line)
{
    if(indentSize==-1)
        indentSize = line.find_first_not_of(' ');
}

void sizeAndCounterUpdater (string line)
{
    if(line.find('{')!=string::npos)
    {
        bracingCounter++;

        if(indentSize==0)
            indentSize = -1;
        else
            indentSize = indentSize/(bracingCounter-1)*bracingCounter;
    }

    if(line.find('}')!=string::npos)
    {
        bracingCounter--;

        if(indentSize!=0)
        indentSize = indentSize/(bracingCounter+1)*bracingCounter;
    }
}

double indentationAnalyzer (string fileName)
{
    indentSize=0;
    bracingCounter=0;

    vector <string> inputCode = readCode(fileName);
    vector <string> :: iterator codeItr;

    for(codeItr=inputCode.begin();codeItr!=inputCode.end();codeItr++)
    {
        string line = *codeItr;
        initialIndentSize(line);

        if(line.empty())
        {
            numberOfProperIndentation++;
            continue;
        }

        if(hasProperIndentation(line))
            numberOfProperIndentation++;

        sizeAndCounterUpdater(line);
    }

    return (double) numberOfProperIndentation * 100.0 / inputCode.size();
}
