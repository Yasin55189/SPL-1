#include <iostream>
#include <queue>
#include "others.h"

using namespace std;

queue<string> cutString (string s)
{
    string temp;
    queue<string> queueTemp;

    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i]==',')
        {
            queueTemp.push(temp);
            temp.clear();
        }
        else
            temp+=s[i];
    }

    queueTemp.push(temp);

    return queueTemp;
}

int strToInt (string s)
{
    int sum=0, exp=1;
    for(int i=s.size()-1;i>=0;i--)
    {
        sum=sum+((int)(s[i])-48)*exp;
        exp=exp*10;
    }

    return sum;
}

double strToRad (string s)
{
    double sum=0, exp=0.1;
    for(int i=0;s[i]!='\0';i++)
    {
        sum=sum+((((int)(s[i]))-48)*exp);
        exp=exp/10;
    }
    return sum;
}

double strToDouble (string s)
{
    string temp1, temp2;

    for(int i=0;s[i]!='\0';i++)
    {
        if(s[i]=='.')
        {
            temp1=temp2;
            temp2.clear();
        }
        else
            temp2+=s[i];
    }

    double num = strToInt(temp1);
    double rad = strToRad(temp2);

    double result = num + rad;

    return result;
}
