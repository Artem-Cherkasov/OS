#pragma once
#include "generalFunc.h"
#include "stdafx.h"

int parseMealyMachine(
	std::ifstream& input,
	std::vector<std::string>& primaryStatesCount,
	std::vector<std::string>& transitions,
	std::vector<std::string>& signals);

void initMealyMinimisationMap(
	std::unordered_map<int, MachineClass>& minimisationMap,
	const int& primaryStatesCountSize,
	const std::vector<std::string> signals,
	std::vector<std::string>& uniqueSignals,
	const int& stringCounter);

void minimiseMealyMachine(
	std::vector<std::string>& uniqueSignals,
	std::unordered_map<int, MachineClass>& minimisationMap,
	const int& primaryStatesCountSize,
	const std::vector<std::string> transitions,
	std::vector<std::string>& signals,
	const int& stringCounter);

void generateOutputMealyStates(
	std::ofstream& output,
	std::unordered_map<int, MachineClass>& minimisationMap,
	std::vector<int>& uniqueMachineClasses);

void generateOutputMealyTransitions(
	std::ofstream& output,
	std::unordered_map<int, MachineClass>& minimisationMap,
	std::vector<std::string>& primarySignals,
	const int& stringCounter,
	std::vector<int>& uniqueMachineClasses,
	const int& primaryStatesCountSize,
	std::vector<std::string>& transitions);