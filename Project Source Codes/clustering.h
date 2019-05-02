#include <vector>
#include "profiler.h"

using namespace std;



struct point
{
    int id;

    double percentageOfWhiteSpace;
    double percentageOfEmptyLines;
    double spacePerSignature;
    double percentageOfProperIndentation;
    double percentageOfSpaceBeforeEqual;
    double percentageOfSpaceAfterEqual;
    //char bracingStyle;
};

struct cluster
{
    point mean;
    vector <point> clusPoints;
};


vector<point> profilesToPointsConverter (vector<profile>);
vector<cluster> kMeans (vector<point>, int);
