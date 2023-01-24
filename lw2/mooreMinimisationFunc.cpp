#include "generalFunc.h"

const char delim = ';';
const char separator = '/';

int parseMooreMachine(
	std::ifstream& input,
	std::vector<std::string>& transitions,
	std::vector<std::string>& primarySignals,
	std::vector<std::string>& primaryStates)
{
	std::string str = "";
	std::getline(input, str);
	tokenize(str, delim, primarySignals);
	std::getline(input, str);
	tokenize(str, delim, primaryStates);

	int stringCounter = 0;
	std::vector<std::string> tmpVect;
	while (getline(input, str))
	{
		stringCounter++;
		tokenize(str, delim, tmpVect);
		tmpVect.erase(tmpVect.begin());
		for (auto i : tmpVect)
			transitions.push_back(i);
		tmpVect.clear();
	}

	return stringCounter;
}

void initMooreMinimisationMap(
	std::unordered_map<int, MachineClass>& minimisationMap,
	const int& primaryStatesCountSize,
	const std::vector<std::string> signals,
	std::vector<std::string>& uniqueSignals,
	const int& stringCounter)
{
	int counter = 0;
	std::vector<std::string>::iterator iter;
	for (size_t i = 0; i < primaryStatesCountSize; i++)
	{
		if (std::find(uniqueSignals.begin(), uniqueSignals.end(), signals[i]) == uniqueSignals.end())
		{
			uniqueSignals.push_back(signals[i]);
			minimisationMap[counter].count = uniqueSignals.size() - 1;
		}
		else
		{
			iter = std::find(uniqueSignals.begin(), uniqueSignals.end(), signals[i]);
			minimisationMap[counter].count = std::distance(uniqueSignals.begin(), iter);
		}
		minimisationMap[counter].uniqueSignal = std::move(signals[i]);
		counter++;
	}
}

void minimiseMooreMachine(
	std::vector<std::string>& uniqueSignals,
	std::unordered_map<int, MachineClass>& minimisationMap,
	const int& primaryStatesCountSize,
	const std::vector<std::string> transitions,
	std::vector<std::string>& newTransitions,
	const int& stringCounter)
{
	int uniqueSignalsCount = 0;
	std::string tmpString = "";
	int counter;
	std::vector<std::string>::iterator iter;

	do
	{
		uniqueSignalsCount = uniqueSignals.size();
		counter = 0;
		uniqueSignals.clear();

		for (size_t i = 0; i < transitions.size(); i++)
		{
			newTransitions[i] = std::to_string(minimisationMap[std::stoi(transitions[i]) - 1].count);
		}

		for (size_t i = 0; i < primaryStatesCountSize; i++)
		{
			for (size_t j = 0; j < stringCounter; j++)
			{
				if (j == 0)
					tmpString = tmpString + newTransitions[i];
				else
					tmpString = tmpString + newTransitions[i + (primaryStatesCountSize * j)];
			}
			tmpString = tmpString + std::to_string(minimisationMap[i].count);
			if (std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString) == uniqueSignals.end())
			{
				uniqueSignals.push_back(tmpString);
				minimisationMap[counter].count = uniqueSignals.size() - 1;
			}
			else
			{
				iter = std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString);
				minimisationMap[counter].count = std::distance(uniqueSignals.begin(), iter);
			}
			tmpString.pop_back();
			minimisationMap[counter].uniqueSignal = std::move(tmpString);
			counter++;
		}
	} while (uniqueSignalsCount != uniqueSignals.size());
}

void generateOutputMooreStates(
	std::ofstream& output,
	std::unordered_map<int, MachineClass>& minimisationMap,
	std::vector<int>& uniqueMachineClasses,
	std::vector<std::string>& primarySignals)
{
	std::vector<std::string> uniqueClassStates;
	std::string finalSignals = ";";
	std::string finalStates = ";";
	for (size_t i = 0; i < minimisationMap.size(); i++)
	{
		if (std::find(uniqueClassStates.begin(), uniqueClassStates.end(),
			std::to_string(minimisationMap[i].count)) == uniqueClassStates.end())
		{
			uniqueClassStates.push_back(std::to_string(minimisationMap[i].count));
			uniqueMachineClasses.push_back(i);
			finalSignals = finalSignals + primarySignals[i] + ";";
			finalStates = finalStates + std::to_string(minimisationMap[i].count) + ";";
		}
	}
	output << finalSignals << std::endl << finalStates << std::endl;
}

void generateOutputMooreTransitions(
	std::ofstream& output,
	const int& stringCounter,
	std::unordered_map<int, MachineClass>& minimisationMap,
	std::vector<int>& uniqueMachineClasses,
	std::vector<std::string>& primaryStates,
	std::vector<std::string>& transitions)
{
	for (size_t i = 0; i < stringCounter; i++)
	{
		output << i << ";";
		for (size_t j = 0; j < uniqueMachineClasses.size(); j++)
		{
			if (i == 0)
				output << minimisationMap[std::stoi(transitions[uniqueMachineClasses[j]]) - 1].count << ";";
			else
				output << minimisationMap[std::stoi(transitions[uniqueMachineClasses[j] + i * primaryStates.size()]) - 1].count << ";";
		}
		output << std::endl;
	}
}