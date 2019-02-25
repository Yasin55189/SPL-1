#ifndef BRACINGANALYZER_H_INCLUDED
#define BRACINGANALYZER_H_INCLUDED

#include <iostream>

using namespace std;

struct braceStyle
{
    bool isStraight;
    bool isVertical;
    bool isFirst;
};

bool isStraight (string);
bool isVertical (string,string);
bool isFirst (string);
double bracingAnalyzer (string);

#endif
