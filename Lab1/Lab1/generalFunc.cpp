#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include "generalFunc.h"

using namespace std;

void tokenize(string const& str, const char delim, vector<string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void matrixInit(vector<vector<string>>& matrix, ifstream& input, const char& delim)
{
    string str;
    vector<string> matrixString;
    while (getline(input, str))
    {
        tokenize(str, delim, matrixString);
        matrixString.erase(matrixString.begin());
        matrix.push_back(matrixString);
        matrixString = {};
    }
}