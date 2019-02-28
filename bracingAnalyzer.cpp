#include <iostream>
#include <vector>
#include "bracingAnalyzer.h"
#include "code.h"

using namespace std;

vector <braceStyle> braceStyleArray;
vector <braceStyle> :: iterator itr;

vector <int> braceIndentSize;

int countA=0,countB=0,countC=0,countD=0;

char style;

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

bool isTypeA (braceStyle brace)
{
    if(brace.isFirst&&brace.isStraight&&brace.isVertical)
        return true;
    return false;
}

bool isTypeB (braceStyle brace)
{
    if(brace.isFirst&&brace.isStraight&&!(brace.isVertical))
        return true;
    return false;
}

bool isTypeC (braceStyle brace)
{
    if(!(brace.isFirst)&&brace.isStraight)
        return true;
    return false;
}

void countingStyles ()
{
    for(itr=braceStyleArray.begin();itr!=braceStyleArray.end();itr++)
    {
        if(isTypeA(*itr))
            countA++;
        else if(isTypeB(*itr))
            countB++;
        else if(isTypeC(*itr))
            countC++;
        else
            countD++;
    }
}

char countStyleAnalyzer ()
{
    if(countA>countB&&countA>countC&&countA>countD)
        return 'A';
    else if (countB>countA&&countB>countC&&countB>countD)
        return 'B';
    else if (countC>countA&&countC>countB&&countC>countD)
        return 'C';
    else
        return 'D';
}

void startingBraceActivities (string line, string preLine)
{
    if(line.find('{')!=string::npos)
    {
        int tempBrace = line.find_first_not_of(' ');

        braceIndentSize.push_back(tempBrace);

        braceStyle temp;
        temp.isFirst = isFirst(line);
        temp.isVertical = isVertical(line,preLine);

        braceStyleArray.push_back(temp);
    }
}

void endingBraceActivities (string line)
{
    if(line.find('}')!=string::npos)
    {
        (*((braceStyleArray.end())-1)).isStraight=isStraight(line);

        braceIndentSize.pop_back();
    }
}

char bracingAnalyzer (string fileName)
{
    vector <string> inputCode = readCode(fileName);
    vector <string> :: iterator codeItr;

    for(codeItr=inputCode.begin();codeItr!=inputCode.end();codeItr++)
    {
        startingBraceActivities(*codeItr,*(codeItr-1));

        endingBraceActivities(*codeItr);
    }

    countingStyles();

    style = countStyleAnalyzer();

    return style;
}
