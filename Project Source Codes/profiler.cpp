#include "profiler.h"
#include "others.h"
#include "whiteSpaceAnalyzer.h"
#include "emptyLinesAnalyzer.h"
#include "stat.h"
#include "bracingAnalyzer.h"
#include "indentationAnalyzer.h"
#include "signatureAnalyzer.h"
#include "spaceSymbolAnalyzer.h"
#include "clustering.h"
#include <math.h>
#include <map>
#include <dirent.h>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

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

            for(int i=0;i<numberOfSamples;i++)
            {
                p.bracingStyle.push_back(singlePro.front()[0]);
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

            for(vector<char>::iterator itr=(*itr2).bracingStyle.begin();
                itr!=(*itr2).bracingStyle.end();itr++)
            {
                oPro << *itr << ',';
            }

            oPro << endl;
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

        p.bracingStyle.push_back(bracingAnalyzer(path));
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
        (*itr).bracingStyle.push_back(bracingAnalyzer(path));
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

    p.bracingStyle.push_back(bracingAnalyzer(s));

    return p;
}

void deanonymize ()
{
    string s;
    getline(cin,s);
    cout << "Enter anonymous source code's file path: ";
    getline(cin,s);

    profile temp = tempProfile(s);

        map <int,double> proMap;
        map <int,double> :: iterator mapItr;
        multimap<double,int> mm;
        multimap<double,int>::iterator mit;

        for(itr2=profiles.begin();itr2!=profiles.end();itr2++)
        {
            double meanValue = mean ((*itr2).percentageOfWhiteSpace);
            double var = variance(meanValue,(*itr2).percentageOfWhiteSpace);
            double betaDistributionValueWS = betaDistribution(meanValue, var, temp.percentageOfWhiteSpace.front());

            meanValue = mean ((*itr2).percentageOfEmptyLines);
            var = variance(meanValue,(*itr2).percentageOfEmptyLines);
            double betaDistributionValueEL = betaDistribution(meanValue, var, temp.percentageOfEmptyLines.front());


            meanValue = mean ((*itr2).spacePerSignature);
            var = variance(meanValue,(*itr2).spacePerSignature);
            double normalDistributionValueSS = normalDistribution(meanValue, var, temp.spacePerSignature.front());


            meanValue = mean ((*itr2).percentageOfSpaceBeforeEqual);
            var = variance(meanValue,(*itr2).percentageOfSpaceBeforeEqual);
            double normalDistributionValueSBE = normalDistribution(meanValue, var, temp.percentageOfSpaceBeforeEqual.front());

            meanValue = mean ((*itr2).percentageOfSpaceAfterEqual);
            var = variance(meanValue,(*itr2).percentageOfSpaceAfterEqual);
            double normalDistributionValueSAE = normalDistribution(meanValue, var, temp.percentageOfSpaceAfterEqual.front());



            double rankSum = betaDistributionValueWS*betaDistributionValueEL
                            *normalDistributionValueSS;


            if(bracingStyleFinalizer((*itr2).bracingStyle)!=temp.bracingStyle.front())
            {
                rankSum = -1;
            }


            meanValue = mean ((*itr2).percentageOfProperIndentation);
            var = variance(meanValue,(*itr2).percentageOfEmptyLines);
            if(fabs(meanValue-temp.percentageOfProperIndentation.front())>
               2*sqrt(var))
               rankSum = -1;



            proMap[(*itr2).id]=rankSum;
        }

        for(mapItr=proMap.begin();mapItr!=proMap.end();mapItr++)
        {
            mm.insert(make_pair(mapItr->second,mapItr->first));
        }

        map<int,int> mp;
        map<int,int>::iterator it;
        multimap<int,int> mm2;
        multimap<int,int>::iterator mit2;
        vector <point> points = profilesToPointsConverter(profiles);

        point de;

        de.id=temp.id;
        de.percentageOfWhiteSpace=temp.percentageOfWhiteSpace.front();
        de.percentageOfEmptyLines=temp.percentageOfEmptyLines.front();
        de.spacePerSignature=temp.spacePerSignature.front();
        de.percentageOfProperIndentation=temp.percentageOfProperIndentation.front();
        de.percentageOfSpaceBeforeEqual=temp.percentageOfSpaceBeforeEqual.front();
        de.percentageOfSpaceAfterEqual=temp.percentageOfSpaceAfterEqual.front();

        points.push_back(de);

        vector<cluster> clusters = kMeans(points,profiles.size()+1);

        vector<cluster>::iterator itrClus;
        cluster finalClus;
        vector<point>::iterator itrPo;

        int markerfin = 0;

        for(itrClus=clusters.begin();itrClus!=clusters.end();itrClus++)
        {
            for(itrPo=((*itrClus).clusPoints).begin();itrPo!=((*itrClus).clusPoints).end();
            itrPo++)
            {
                if((*itrPo).id==-1)
                {
                    finalClus=*itrClus;
                    markerfin=1;
                    break;
                }
            }
            if(markerfin==1)
            {
                break;
            }
        }

        vector<point> finalPoints = finalClus.clusPoints;

        for(itrPo=finalPoints.begin();itrPo!=finalPoints.end();itrPo++)
        {
            mp[(*itrPo).id]++;
        }

        for(it=mp.begin();it!=mp.end();it++)
        {
            if(it->first==-1)
                continue;
            int samSize;

            for(vector<profile>::iterator iProf=profiles.begin();
            iProf!=profiles.end();iProf++)
            {
                if((*iProf).id==it->first)
                {
                    samSize=(*iProf).numberOfSamples;
                    break;
                }
            }
            mm2.insert(make_pair(it->second/samSize,it->first));
        }



        ofstream ofile;
        ofile.open("results.txt");
        if(ofile.is_open())
        {
            ofile << "Sample source code: " << s << endl << endl;
            ofile << "Rank" << "\t\t" << "Naive Bayes" << "\t\t" << "K Means" << endl;

            mit = mm.end();
            mit--;
            mit2 = mm2.end();
            mit2--;

            for(int i=0; i<3; i++)
            {
                if(i>((int)mm.size()-1))
                    break;

                ofile << " " << setw(2) << i+1 << "                 " << setw(2) <<
                 mit->second << "                    "
                << setw(2) << mit2->second << endl;
                mit--;
                mit2--;
            }
        }
}
