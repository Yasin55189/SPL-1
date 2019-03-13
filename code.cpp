#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector <string> inputCode;

vector <string> readCode (string fileName)
{
    inputCode.clear();
    ifstream iCod;
    iCod.open(fileName.c_str());
    if(iCod.is_open())
    {
        string s;
        getline(iCod,s);
        while(!iCod.eof())
        {
            inputCode.push_back(s);
            getline(iCod,s);
        }
        iCod.close();
    }

    return inputCode;
}
