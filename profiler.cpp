#include "profiler.h"
#include "others.h"
#include "whiteSpaceAnalyzer.h"
#include "emptyLinesAnalyzer.h"
#include "stat.h"
#include "bracingAnalyzer.h"
#include "indentationAnalyzer.h"
#include "signatureAnalyzer.h"
#include "spaceSymbolAnalyzer.h"
#include <math.h>
#include <map>
#include <dirent.h>
#include <string>
#include <vector>

using namespace std;

map <int,double> proMap;
map <int,double> :: iterator mapItr;

vector <profile> profiles;
vector <profile> :: iterator itr2;


// copied function from the web
vector<string> open(string path)
{

    DIR*    dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    int i=1;

    while ((pdir = readdir(dir)))
    {
        if(i>2)
        {
            files.push_back(pdir->d_name);
        }
        i++;
    }

    closedir(dir);

    return files;
}

void readProfiles ()
{
    ifstream iPro;
    iPro.open("profiles.csv");
    if(iPro.is_open())
    {
        int id, numberOfSamples;

        string pro;

        getline(iPro,pro);

        while(!iPro.eof())
        {
            if(pro.empty()) break;

            queue<string> singlePro = cutString(pro);

            id=strToInt(singlePro.front());
            singlePro.pop();

            numberOfSamples=strToInt(singlePro.front());
            singlePro.pop();

            profile p;

            p.id=id;
            p.numberOfSamples=numberOfSamples;

            for(int i=0;i<numberOfSamples;i++)
            {
                p.percentageOfWhiteSpace.push_back(strToDouble(singlePro.front()));
                singlePro.pop();
            }

            for(int i=0;i<numberOfSamples;i++)
            {
                p.percentageOfEmptyLines.push_back(strToDouble(singlePro.front()));
                singlePro.pop();
            }

            for(int i=0;i<numberOfSamples;i++)
            {
                p.spacePerSignature.push_back(strToDouble(singlePro.front()));
                singlePro.pop();
            }

            for(int i=0;i<numberOfSamples;i++)
            {
                p.percentageOfProperIndentation.push_back(strToDouble(singlePro.front()));
                singlePro.pop();
            }

            for(int i=0;i<numberOfSamples;i++)
            {
                p.percentageOfSpaceBeforeEqual.push_back(strToDouble(singlePro.front()));
                singlePro.pop();
            }

            for(int i=0;i<numberOfSamples;i++)
            {
                p.percentageOfSpaceAfterEqual.push_back(strToDouble(singlePro.front()));
                singlePro.pop();
            }
/*
            for(int i=0;i<numberOfSamples;i++)
            {
                p.bracingStyle.push_back(singlePro.front()[0]);
                singlePro.pop();
            }
*/

            profiles.push_back(p);

            getline(iPro,pro);
        }
    }
    iPro.close();
}

void writeProfiles ()
{
    ofstream oPro;
    oPro.open("profiles.csv");
    if(oPro.is_open())
    {
        for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
        {
            oPro << (*itr2).id << ',' << (*itr2).numberOfSamples << ',';

            for(vector<double>::iterator itr=(*itr2).percentageOfWhiteSpace.begin();
                itr!=(*itr2).percentageOfWhiteSpace.end();itr++)
            {
                oPro << *itr << ',';
            }

            for(vector<double>::iterator itr=(*itr2).percentageOfEmptyLines.begin();
                itr!=(*itr2).percentageOfEmptyLines.end();itr++)
            {
                oPro << *itr << ',';
            }

            for(vector<double>::iterator itr=(*itr2).spacePerSignature.begin();
                itr!=(*itr2).spacePerSignature.end();itr++)
            {
                oPro << *itr << ',';
            }

            for(vector<double>::iterator itr=(*itr2).percentageOfProperIndentation.begin();
                itr!=(*itr2).percentageOfProperIndentation.end();itr++)
            {
                oPro << *itr << ',';
            }

            for(vector<double>::iterator itr=(*itr2).percentageOfSpaceBeforeEqual.begin();
                itr!=(*itr2).percentageOfSpaceBeforeEqual.end();itr++)
            {
                oPro << *itr << ',';
            }

            for(vector<double>::iterator itr=(*itr2).percentageOfSpaceAfterEqual.begin();
                itr!=(*itr2).percentageOfSpaceAfterEqual.end();itr++)
            {
                oPro << *itr << ',';
            }
/*
            for(vector<char>::iterator itr=(*itr2).bracingStyle.begin();
                itr!=(*itr2).bracingStyle.end();itr++)
            {
                oPro << *itr << ',';
            }
*/
            oPro << '\b' << endl;
        }
    }
    oPro.close();
}

void originalSetUp (int id, vector<string> listOfFiles, string directoryPath)
{
    vector <string> :: iterator stringItr;

    profile p;
    p.id = id;

    string path;

    for(stringItr=listOfFiles.begin();stringItr!=listOfFiles.end();stringItr++)
    {
        path = directoryPath+ "\\" + *stringItr;

        p.percentageOfWhiteSpace.push_back(percentageOfWhiteSpaceAnalyzer(path));

        p.percentageOfEmptyLines.push_back(percentageOfEmptyLinesAnalyzer(path));

        p.spacePerSignature.push_back(signatureAnalyzer(path));

        p.percentageOfProperIndentation.push_back(indentationAnalyzer(path));
        p.percentageOfSpaceBeforeEqual.push_back(percentageOfSpaceSymbolAnalyzer(path,"=",0));
        p.percentageOfSpaceAfterEqual.push_back(percentageOfSpaceSymbolAnalyzer(path,"=",1));

        //p.bracingStyle.push_back(bracingAnalyzer(path));
    }

    p.numberOfSamples=listOfFiles.size();

    profiles.push_back(p);
}

void additionalSetUp (vector<profile>::iterator itr, vector<string> listOfFiles, string directoryPath)
{
    vector <string> :: iterator stringItr;

    for(stringItr=listOfFiles.begin();stringItr!=listOfFiles.end();stringItr++)
    {
        string path = directoryPath+ "\\" + *stringItr;

        (*itr).percentageOfWhiteSpace.push_back(percentageOfWhiteSpaceAnalyzer(path));
        (*itr).percentageOfEmptyLines.push_back(percentageOfEmptyLinesAnalyzer(path));
        (*itr).spacePerSignature.push_back(signatureAnalyzer(path));
        (*itr).percentageOfProperIndentation.push_back(indentationAnalyzer(path));
        (*itr).percentageOfSpaceBeforeEqual.push_back(percentageOfSpaceSymbolAnalyzer(path,"=",0));
        (*itr).percentageOfSpaceAfterEqual.push_back(percentageOfSpaceSymbolAnalyzer(path,"=",1));
        //(*itr).bracingStyle.push_back(bracingAnalyzer(path));
    }
    (*itr).numberOfSamples+=listOfFiles.size();
}

void profileSetUp ()
{
    int id;

    cout << "Enter programmer ID: ";

    cin >> id;

    string directoryPath;

    getline(cin,directoryPath);
    cout << "Enter folder path: ";
    getline(cin,directoryPath);

    vector <string> listOfFiles = open (directoryPath);
    vector <string> :: iterator stringItr;

    int flag = 0;

    for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
    {
        if((*itr2).id==id)
        {
            additionalSetUp(itr2,listOfFiles,directoryPath);
            flag = 1;
        }
    }

    if(flag==0)
    {
        originalSetUp(id,listOfFiles,directoryPath);
    }

    cout << "Profile successfully created!" << endl;
}

profile tempProfile (string s)
{
    profile p;

    p.id = -1;

    p.numberOfSamples = 1;

    p.percentageOfWhiteSpace.push_back(percentageOfWhiteSpaceAnalyzer(s));

    p.percentageOfEmptyLines.push_back(percentageOfEmptyLinesAnalyzer(s));

    p.spacePerSignature.push_back(signatureAnalyzer(s));

    p.percentageOfProperIndentation.push_back(indentationAnalyzer(s));

    p.percentageOfSpaceBeforeEqual.push_back(percentageOfSpaceSymbolAnalyzer(s,"=",0));

    p.percentageOfSpaceAfterEqual.push_back(percentageOfSpaceSymbolAnalyzer(s,"=",1));

    //p.bracingStyle.push_back(bracingAnalyzer(s));

    return p;
}

void deanonymize ()
{
    string s;
    getline(cin,s);
    cout << "Enter anonymous source code's file path: ";
    getline(cin,s);

    profile temp = tempProfile(s);

    for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
    {
        double meanValue = mean ((*itr2).percentageOfWhiteSpace);
        double var = variance(meanValue,(*itr2).percentageOfWhiteSpace);
        double betaDistributionValueWS = betaDistribution(meanValue, var, temp.percentageOfWhiteSpace.front());

        meanValue = mean ((*itr2).percentageOfEmptyLines);
        var = variance(meanValue,(*itr2).percentageOfEmptyLines);
        double betaDistributionValueEL = betaDistribution(meanValue, var, temp.percentageOfEmptyLines.front());
/*
        meanValue = mean ((*itr2).spacePerSignature);
        var = variance(meanValue,(*itr2).spacePerSignature);
        double normalDistributionValueSS = normalDistribution(meanValue, var, temp.spacePerSignature.front());

        meanValue = mean ((*itr2).percentageOfProperIndentation);
        var = variance(meanValue,(*itr2).percentageOfProperIndentation);
        double betaDistributionValuePI = betaDistribution(meanValue, var, temp.percentageOfProperIndentation.front());

        meanValue = mean ((*itr2).percentageOfSpaceBeforeEqual);
        var = variance(meanValue,(*itr2).percentageOfSpaceBeforeEqual);
        double betaDistributionValueSBE = betaDistribution(meanValue, var, temp.percentageOfSpaceBeforeEqual.front());

        meanValue = mean ((*itr2).percentageOfSpaceAfterEqual);
        var = variance(meanValue,(*itr2).percentageOfSpaceAfterEqual);
        double betaDistributionValueSAE = betaDistribution(meanValue, var, temp.percentageOfSpaceAfterEqual.front());

*/

        double rankSum = betaDistributionValueWS*betaDistributionValueEL
                        /**betaDistributionValuePI*betaDistributionValueSAE
                        *betaDistributionValueSBE*normalDistributionValueSS*/;

        //cout << "***" << rankSum << endl << betaDistributionValueEL << endl;
/*
        if(bracingStyleFinalizer((*itr2).bracingStyle)!=temp.bracingStyle.front())
        {
            rankSum = -1;
        }
*/

        proMap[(*itr2).id]=rankSum;
    }

    int ID = matchingRankSum(proMap);

    cout << "Deanonymized programmer ID: " << ID << endl;
}
