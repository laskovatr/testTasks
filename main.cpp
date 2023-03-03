#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "geometry.h"
using namespace std;




void splitStr(string s, vector<double>& sepParams)
{
    stringstream ss(s);
    string word;
    while (ss >> word)
    {
        sepParams.push_back(atof(word.c_str()));
    }
}

int main()
{
    string params;
    vector<double> sepParams;
    cout << "Input x1 y1 z1 x2 y2 z2 x3 y3 z3 x y z: ";
    getline(cin, params);
    splitStr(params, sepParams);
    if (sepParams.size() != 12)
    {
        return -1;
    }


    point3d p1(sepParams[0], sepParams[1], sepParams[2]);
    point3d p2(sepParams[3], sepParams[4], sepParams[5]);
    point3d p3(sepParams[6], sepParams[7], sepParams[8]);
    triangle t(p1,p2,p3);
    point3d singlePoint(sepParams[9], sepParams[10], sepParams[11]);
    if (isVisible(t, singlePoint))
    {
        cout << "\nVisible" << endl;
    }
    else
    {
        cout << "\nNot visible" << endl;
    }

    return 0;

}
