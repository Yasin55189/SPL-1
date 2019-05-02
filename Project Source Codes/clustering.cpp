#include <iostream>
#include "clustering.h"
#include <math.h>

using namespace std;

int meanSameMarker = 0;

vector<point> profilesToPointsConverter (vector<profile> profiles)
{
    vector <profile> :: iterator itrProfile;

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

point meanPoint (vector<point> points)
{
    vector <point> :: iterator itr;

    point temp;

    temp.id=-1;

    for(itr=points.begin();itr!=points.end();itr++)
    {
        temp.percentageOfWhiteSpace+=(*itr).percentageOfWhiteSpace;
        temp.percentageOfEmptyLines+=(*itr).percentageOfEmptyLines;
        temp.spacePerSignature+=(*itr).spacePerSignature;
        temp.percentageOfProperIndentation+=(*itr).percentageOfProperIndentation;
        temp.percentageOfSpaceBeforeEqual+=(*itr).percentageOfSpaceBeforeEqual;
        temp.percentageOfSpaceAfterEqual+=(*itr).percentageOfSpaceAfterEqual;
    }

    if(points.size()!=0)
    {
        temp.percentageOfWhiteSpace=temp.percentageOfWhiteSpace/points.size();
        temp.percentageOfEmptyLines=temp.percentageOfEmptyLines/points.size();
        temp.spacePerSignature=temp.spacePerSignature/points.size();
        temp.percentageOfProperIndentation=temp.percentageOfProperIndentation/points.size();
        temp.percentageOfSpaceBeforeEqual=temp.percentageOfSpaceBeforeEqual/points.size();
        temp.percentageOfSpaceAfterEqual=temp.percentageOfSpaceAfterEqual/points.size();
    }

    return temp;
}

bool isSamePoint (point a, point b)
{
    if(a.percentageOfEmptyLines==b.percentageOfEmptyLines
       &&a.percentageOfProperIndentation==b.percentageOfProperIndentation
       &&a.percentageOfSpaceAfterEqual==b.percentageOfSpaceAfterEqual
       &&a.percentageOfSpaceBeforeEqual==b.percentageOfSpaceBeforeEqual
       &&a.percentageOfWhiteSpace==b.percentageOfWhiteSpace
       &&a.spacePerSignature==b.spacePerSignature)
        return true;
    return false;
}

vector <cluster> meanPoints (vector<cluster> clusters)
{
    meanSameMarker = 0;

    vector<cluster> :: iterator itr;

    vector <cluster> temp;

    for(itr=clusters.begin();itr!=clusters.end();itr++)
    {
        cluster tempCluster;
        tempCluster.mean=meanPoint((*itr).clusPoints);
        if(isSamePoint(tempCluster.mean,(*itr).mean))
            meanSameMarker++;

        temp.push_back(tempCluster);
    }

    return temp;
}

double distanceBetweenPoints (point a, point b)
{
    return sqrt(pow(a.percentageOfEmptyLines-b.percentageOfEmptyLines,2)
                +pow(a.percentageOfProperIndentation-b.percentageOfProperIndentation,2)
                +pow(a.percentageOfSpaceAfterEqual-b.percentageOfSpaceAfterEqual,2)
                +pow(a.percentageOfSpaceBeforeEqual-b.percentageOfSpaceBeforeEqual,2)
                +pow(a.percentageOfWhiteSpace-b.percentageOfWhiteSpace,2)
                +pow(a.spacePerSignature-b.spacePerSignature,2));
}

vector <cluster> clustering (vector<point> points, vector<cluster> clusters)
{
    vector<point>::iterator pointIterator;
    vector<cluster>::iterator clusterIterator;

    for(pointIterator=points.begin();pointIterator!=points.end();pointIterator++)
    {
        vector<cluster>::iterator tempIterator;
        double minimum = distanceBetweenPoints(*pointIterator,(clusters.front()).mean);
        tempIterator=clusters.begin();
        for(clusterIterator=clusters.begin();clusterIterator!=clusters.end();clusterIterator++)
        {
            if(distanceBetweenPoints(*pointIterator,(*clusterIterator).mean)<minimum)
            {
                minimum=distanceBetweenPoints(*pointIterator,(*clusterIterator).mean);
                tempIterator=clusterIterator;
            }
        }
        (*tempIterator).clusPoints.push_back(*pointIterator);
    }

    return clusters;
}


//bool isSameClustering (vector<cluster> pre, vector<cluster> now)
//{
//    vector<cluster>::iterator preItr;
//    vector<cluster>::iterator nowItr;
//
//    for(nowItr=now.begin();nowItr!=now.end();nowItr++)
//    {
//        int marker = 0;
//
//        for(preItr=pre.begin();preItr!=pre.end();preItr++)
//        {
//            if(isSamePoint((*nowItr).mean,(*preItr).mean))
//            {
//                marker = 1;
//                break;
//            }
//        }
//
//        if(marker==0)
//            return false;
//    }
//
//    return true;
//}

vector<cluster> kMeans (vector<point> points, int k)
{
    vector<cluster> clusters;
    vector<cluster> temp1;
    for(int i=0; i<k; i++)
    {
        cluster temp;
        temp.mean=points[(points.size()/k)*i];
        clusters.push_back(temp);
    }

    while(meanSameMarker!=k)
    {
        temp1=clustering(points,clusters);
        clusters=meanPoints(temp1);
    }
    clusters=temp1;

    return clusters;
}
