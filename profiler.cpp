#include "profiler.h"
#include "others.h"
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

    for(stringItr=listOfFiles.begin();stringItr!=listOfFiles.end();stringItr++)
    {
        string path = directoryPath+ "\\" + *stringItr;

        p.percentageOfWhiteSpace.push_back(percentageOfWhiteSpaceAnalyzer(path));
        p.percentageOfEmptyLines.push_back(percentageOfEmptyLinesAnalyzer(path));
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
    }
    (*itr).numberOfSamples+=listOfFiles.size();
}

void profileSetUp ()
{
    int id;

    cin >> id;

    string directoryPath;

    getline(cin,directoryPath);
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
}

profile tempProfile (string s)
{
    int id = -1;

    double spacePer = percentageOfWhiteSpaceAnalyzer(s);
    double empLinPer = percentageOfEmptyLinesAnalyzer(s);

    profile p;

    p.id = id;

    p.numberOfSamples = 1;

    p.percentageOfWhiteSpace.push_back(spacePer);

    p.percentageOfEmptyLines.push_back(empLinPer);

    return p;
}

void deanonymize ()
{
    string s;
    getline(cin,s);
    getline(cin,s);

    profile temp = tempProfile(s);

    for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
    {
        double meanWhiteSpace = mean ((*itr2).percentageOfWhiteSpace);

        double varWhiteSpace = variance(meanWhiteSpace,(*itr2).percentageOfWhiteSpace);

        double betaDistributionValueWS = betaDistribution(meanWhiteSpace,
                                                        varWhiteSpace,
                                                        temp.percentageOfWhiteSpace.front());




        double meanEmptyLines = mean ((*itr2).percentageOfEmptyLines);

        double varEmptyLines = variance(meanEmptyLines,(*itr2).percentageOfEmptyLines);

        double betaDistributionValueEL = betaDistribution(meanEmptyLines,
                                                        varEmptyLines,
                                                        temp.percentageOfEmptyLines.front());


        double rankSum = betaDistributionValueWS*betaDistributionValueEL;

        proMap[(*itr2).id]=rankSum;
    }

    int ID = matchingRankSum(proMap);

    cout << ID << endl;
}
