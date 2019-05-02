#ifndef BRACINGANALYZER_H_INCLUDED
#define BRACINGANALYZER_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

struct braceStyle
{
    bool isStraight;
    bool isVertical;
    bool isFirst;
};

char bracingAnalyzer (string);
char bracingStyleFinalizer (vector<char>);

#endif
