

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


vector<point> profileToPointsConverter (vector<profile>);
