#pragma once
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void outValParse(ifstream& input, const char& delim, vector<string>& outVal);

void statesParse(ifstream& input, const char& delim, vector<string>& states);

void pairRecord(ofstream& output, const vector<string>& states, vector<vector<string>>& matrix, const vector<string>& outVal);