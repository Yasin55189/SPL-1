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
        int id;
        double space, varSpace, empLin, varEmpLin;

        string pro;

        while(getline(iPro,pro))
        {
            queue<string> singlePro = cutString(pro);


            id=strToInt(singlePro.front());
            singlePro.pop();

            space=strToDouble(singlePro.front());
            singlePro.pop();

            varSpace=strToDouble(singlePro.front());
            singlePro.pop();

            empLin=strToDouble(singlePro.front());
            singlePro.pop();

            varEmpLin=strToDouble(singlePro.front());
            singlePro.pop();


            profile p;

            p.id=id;

            p.percentageOfWhiteSpace=space;
            p.varianceOfPercentageOfWhiteSpace=varSpace;

            p.percentageOfEmptyLines=empLin;
            p.varianceOfPercentageOfEmptyLines=varEmpLin;

            profiles.push_back(p);
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
            oPro << (*itr2).id << ',' << (*itr2).percentageOfWhiteSpace
            << ',' << (*itr2).varianceOfPercentageOfWhiteSpace
            << ',' << (*itr2).percentageOfEmptyLines
            << ',' << (*itr2).varianceOfPercentageOfEmptyLines << endl;
        }
    }
    oPro.close();
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

    double spacePercentage = mean(directoryPath, listOfFiles, &percentageOfWhiteSpaceAnalyzer);
    double emptyLinesPercentage = mean(directoryPath, listOfFiles, &percentageOfEmptyLinesAnalyzer);

    double varianceOfSpacePercentage = variance(directoryPath, spacePercentage,
                                                listOfFiles, &percentageOfWhiteSpaceAnalyzer);
    double varianceOfEmptyLinesPercentage = variance(directoryPath, emptyLinesPercentage,
                                                     listOfFiles, &percentageOfEmptyLinesAnalyzer);

    profile p;

    p.id = id;

    p.percentageOfWhiteSpace = spacePercentage;
    p.varianceOfPercentageOfWhiteSpace=varianceOfSpacePercentage;

    p.percentageOfEmptyLines = emptyLinesPercentage;
    p.varianceOfPercentageOfEmptyLines=varianceOfEmptyLinesPercentage;

    profiles.push_back(p);
}

profile tempProfile (string s)
{
    int id = -1;

    double spacePer = percentageOfWhiteSpaceAnalyzer(s);
    double empLinPer = percentageOfEmptyLinesAnalyzer(s);

    profile p;

    p.id = id;

    p.percentageOfWhiteSpace = spacePer;

    p.percentageOfEmptyLines = empLinPer;

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

        double betaDistributionValue1 = betaDistribution((*itr2).percentageOfWhiteSpace,
                                                        (*itr2).varianceOfPercentageOfWhiteSpace,
                                                        temp.percentageOfWhiteSpace);


        double betaDistributionValue2 = betaDistribution((*itr2).percentageOfEmptyLines,
                                                        (*itr2).varianceOfPercentageOfEmptyLines,
                                                        temp.percentageOfEmptyLines);


        double rankSum = betaDistributionValue1*betaDistributionValue2;

        proMap[(*itr2).id]=rankSum;
    }

    int ID = matchingRankSum(proMap);

    cout << ID << endl;
}
