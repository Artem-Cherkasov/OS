#pragma once
#include <vector>
#include <string>

using namespace std;

void uniqueTransitionsParse(const vector<vector<string>>& matrix, vector<string>& uniqueTransitions);

void outValRecord(ofstream& output, const vector<string>& uniqueTransitions, const char& separator);

void statesRecord(ofstream& output, const vector<string>& uniqueTransitions);

void transitionsRecord(ofstream& output, const vector<vector<string>>& matrix, const vector<string>& uniqueTransitions);