#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include "generalFunc.h"
#include "mooreToMealyFunc.h"

using namespace std;

void outValParse(ifstream& input, const char& delim, vector<string>& outVal)
{
    string str;
    getline(input, str);
    tokenize(str, delim, outVal);
}

void statesParse(ifstream& input, const char& delim, vector<string>& states)
{
    string str;
    getline(input, str);
    tokenize(str, delim, states);
}

void pairRecord(ofstream& output, const vector<string>& states, vector<vector<string>>& matrix, const vector<string>& outVal)
{
    output << ";";
    for (size_t i = 0; i < states.size(); i++)
    {
        output << "a" << i << ";";
    }
    output << endl;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        output << "Z" << i + 1 << ";";
        for (size_t j = 0; j < states.size(); j++)
        {
            auto it = find(states.begin(), states.end(), matrix[i][j]);
            output << "a" << matrix[i][j].erase(0, 1) << "/" << outVal[distance(states.begin(), it)] << ";";
        }
        output << endl;
    }
}