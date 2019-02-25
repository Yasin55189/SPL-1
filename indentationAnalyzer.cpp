#include <iostream>
#include <vector>
#include "indentationAnalyzer.h"
#include "code.h"

using namespace std;

int indentSize;

bool hasProperIndentation (string line)
{
    int temp = line.find_first_not_of(' ');
    if(temp==indentSize)
        return true;
    return false;
}

double indentationAnalyzer (string fileName)
{
    indentSize = 0;
    int braceCounter = 0;

    vector <string> inputCode = readCode(fileName);
    vector <string> :: iterator codeItr;

    int numberOfProperIndentation = 0;

    for(codeItr=inputCode.begin();codeItr!=inputCode.end();codeItr++)
    {
        if(indentSize==-1)
            indentSize=(*codeItr).find_first_not_of(' ');

        if((*codeItr).empty())
        {
            numberOfProperIndentation++;
            continue;
        }

        if(hasProperIndentation(*codeItr))
            numberOfProperIndentation++;

        if((*codeItr).find('{')!=string::npos)
        {
            braceCounter++;

            if(indentSize==0)
                indentSize = -1;
            else
                indentSize = indentSize/(braceCounter-1)*braceCounter;
        }

        if((*codeItr).find('}')!=string::npos)
        {
            braceCounter--;

            if(indentSize!=0)
                indentSize = indentSize/(braceCounter+1)*braceCounter;
        }
    }

    return (double) numberOfProperIndentation * 100.0 / inputCode.size();
}


