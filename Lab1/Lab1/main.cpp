#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include "generalFunc.h"
#include "mealyToMooreFunc.h"
#include "mooreToMealyFunc.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments";
        return 1;
    }

    const char delim = ';';
    const char separator = '/';
    const string mealyToMoore = "mealy-to-moore";
    const string mooreToMealy = "moore-to-mealy";

    vector<string> uniqueTransitions = {};
    ifstream input(argv[2]);
    ofstream output(argv[3]);
    vector<vector<string>> matrix;
    string str;

    if (argv[1] == mealyToMoore)
    {
        getline(input, str);

        matrixInit(matrix, input, delim);

        uniqueTransitionsParse(matrix, uniqueTransitions);

        outValRecord(output, uniqueTransitions, separator);

        statesRecord(output, uniqueTransitions);

        transitionsRecord(output, matrix, uniqueTransitions);
    }
    else if (argv[1] == mooreToMealy)
    {
        vector<string> outVal;
        outValParse(input, delim, outVal);

        vector<string> states;
        statesParse(input, delim, states);

        matrixInit(matrix, input, delim);

        pairRecord(output, states, matrix, outVal);
    }
    else
    {
        cout << "Wrong operation name";
        return 1;
    }

    return 0;
}
