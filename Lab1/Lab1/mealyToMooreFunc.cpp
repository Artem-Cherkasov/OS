#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include "generalFunc.h"

using namespace std;

void uniqueTransitionsParse(const vector<vector<string>>& matrix, vector<string>& uniqueTransitions)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (find(uniqueTransitions.begin(), uniqueTransitions.end(), matrix[i][j]) == uniqueTransitions.end()) uniqueTransitions.push_back(matrix[i][j]);
        }
    }
}

void outValRecord(ofstream& output, const vector<string>& uniqueTransitions, const char& separator)
{
    vector<string> outVal;
    output << ";";
    for (size_t i = 0; i < uniqueTransitions.size(); i++)
    {
        tokenize(uniqueTransitions[i], separator, outVal);
        output << outVal[1] << ";";
        outVal = {};
    }
}

void statesRecord(ofstream& output, const vector<string>& uniqueTransitions)
{
    output << endl << ";";
    for (size_t i = 0; i < uniqueTransitions.size(); i++)
    {
        output << "S" << i << ";";
    }
}

void transitionsRecord(ofstream& output, const vector<vector<string>>& matrix, const vector<string>& uniqueTransitions)
{
    output << endl;
    vector<string> trans;
    for (size_t i = 1; i <= matrix.size(); i++)
    {
        output << "Z" << i << ";";
        for (size_t j = 0; j < uniqueTransitions.size(); j++)
        {
            tokenize(uniqueTransitions[j], '/', trans);
            trans[0].erase(0, 1);
            auto iter = find(uniqueTransitions.begin(), uniqueTransitions.end(), matrix[i - 1][stoi(trans[0]) - 1]);
            if (iter != uniqueTransitions.end())
            {
                output << "S" << distance(uniqueTransitions.begin(), iter) << ";";
            }
            trans = {};
        }
        output << endl;
    }
}

