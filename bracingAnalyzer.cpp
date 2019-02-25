#include <iostream>
#include <vector>
#include "bracingAnalyzer.h"
#include "code.h"

using namespace std;

vector <braceStyle> braceStyleArray;

vector <int> braceIndentSize;
vector <char> results;

bool isStraight (string line)
{
    int temp = line.find('}');
    if(temp==braceIndentSize.back())
    {
        braceIndentSize.pop_back();
        return true;
    }

    braceIndentSize.pop_back();
    return false;
}

bool isVertical (string line, string preLine)
{
    int tempNow = line.find('{');
    int tempPre = preLine.find_first_not_of(' ');

    if(tempNow==tempPre)
        return true;

    return false;
}

bool isFirst (string line)
{
    int tempNow = line.find('{');
    int tempPre = line.find_first_not_of(' ');

    if(tempNow==tempPre)
        return true;

    return false;
}

double bracingAnalyzer (string fileName)
{
    vector <string> inputCode = readCode(fileName);
    vector <string> :: iterator codeItr;

    for(codeItr=inputCode.begin();codeItr!=inputCode.end();codeItr++)
    {
        if((*codeItr).find('{')!=string::npos)
        {
            int tempBrace = (*codeItr).find('{');

            braceIndentSize.push_back(tempBrace);

            braceStyle temp;
            temp.isFirst = isFirst(*codeItr);
            temp.isVertical = isVertical(*codeItr,*(codeItr-1));

            braceStyleArray.push_back(temp);
        }

        if((*codeItr).find('}')!=string::npos)
        {
            (*((braceStyleArray.end())-1)).isStraight=isStraight(*codeItr);

            braceIndentSize.pop_back();
        }
    }
}
