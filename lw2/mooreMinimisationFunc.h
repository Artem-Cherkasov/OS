#pragma once
#include "generalFunc.h"
#include "stdafx.h"

int parseMooreMachine(
	std::ifstream& input,
	std::vector<std::string>& transitions,
	std::vector<std::string>& primarySignals,
	std::vector<std::string>& primaryStates);

void initMooreMinimisationMap(
	std::unordered_map<int, MachineClass>& minimisationMap,
	const int& primaryStatesCountSize,
	const std::vector<std::string> signals,
	std::vector<std::string>& uniqueSignals,
	const int& stringCounter);

void minimiseMooreMachine(
	std::vector<std::string>& uniqueSignals,
	std::unordered_map<int, MachineClass>& minimisationMap,
	const int& primaryStatesCountSize,
	const std::vector<std::string> transitions,
	std::vector<std::string>& newTransitions,
	const int& stringCounter);

void generateOutputMooreStates(
	std::ofstream& output,
	std::unordered_map<int, MachineClass>& minimisationMap,
	std::vector<int>& uniqueMachineClasses,
	std::vector<std::string>& primaryStates);

void generateOutputMooreTransitions(
	std::ofstream& output,
	const int& stringCounter,
	std::unordered_map<int, MachineClass>& minimisationMap,
	std::vector<int>& uniqueMachineClasses, 
	std::vector<std::string>& primaryStates,
	std::vector<std::string>& transitions);