#pragma once
#include <vector>
#include <string>

using namespace std;

void tokenize(string const& str, const char delim, vector<string>& out);

void matrixInit(vector<vector<string>>& matrix, ifstream& input, const char& delim);