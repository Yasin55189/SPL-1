#include <iostream>

using namespace std;

vector <profile> :: iterator itrProfile;

vector<point> profileToPointsConverter (vector<profile> profiles)
{
    vector<point> points;

    for(itrProfile=profiles.begin();itrProfile!=profiles.end();itrProfile++)
    {
        for(int i=0; i<(*itrProfile).numberOfSamples; i++)
        {
            point tempPoint;
            
            tempPoint.id=(*itrProfile).id;

            tempPoint.percentageOfEmptyLines=(*itrProfile).percentageOfEmptyLines.back();
            tempPoint.percentageOfProperIndentation=(*itrProfile).percentageOfProperIndentation.back();
            tempPoint.percentageOfSpaceAfterEqual=(*itrProfile).percentageOfSpaceAfterEqual.back();
            tempPoint.percentageOfSpaceBeforeEqual=(*itrProfile).percentageOfSpaceBeforeEqual.back();
            tempPoint.percentageOfWhiteSpace=(*itrProfile).percentageOfWhiteSpace.back();
            tempPoint.spacePerSignature=(*itrProfile).spacePerSignature.back();

            (*itrProfile).percentageOfEmptyLines.pop_back();
            (*itrProfile).percentageOfProperIndentation.pop_back();
            (*itrProfile).percentageOfSpaceAfterEqual.pop_back();
            (*itrProfile).percentageOfSpaceBeforeEqual.pop_back();
            (*itrProfile).percentageOfWhiteSpace.pop_back();
            (*itrProfile).spacePerSignature.pop_back();

            points.push_back(tempPoint);
        }
    }

    return points;
}
