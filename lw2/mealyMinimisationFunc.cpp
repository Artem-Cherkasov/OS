#include "generalFunc.h"

const char delim = ';';
const char separator = '/';

int parseMealyMachine(
	std::ifstream& input,
	std::vector<std::string>& primaryStatesCount,
	std::vector<std::string>& transitions,
	std::vector<std::string>& signals)
{
	int stringCounter = 0;
	std::string str = "";
    std::vector<std::string> outVect;
    std::vector<std::string> tmpVect;

	getline(input, str);
    tokenize(str, delim, primaryStatesCount);

    while (getline(input, str))
    {
        stringCounter++;
        tokenize(str, delim, outVect);
        outVect.erase(outVect.begin());
        for (size_t i = 0; i < outVect.size(); i++)
        {
            tokenize(outVect[i], separator, tmpVect);
            transitions.push_back(tmpVect[0]);
            signals.push_back(tmpVect[1]);
            tmpVect.clear();
        }
        outVect.clear();
    }
    return stringCounter;
}

void initMealyMinimisationMap(
    std::unordered_map<int, MachineClass>& minimisationMap,
    const int& primaryStatesCountSize,
    const std::vector<std::string> signals,
    std::vector<std::string>& uniqueSignals,
    const int& stringCounter)
{
    std::string str = "";
    std::vector<std::string>::iterator iter;
    int counter = 0;

    for (size_t i = 0; i < primaryStatesCountSize; i++)
    {
        for (size_t j = 0; j < stringCounter; j++)
        {
            if (j == 0)
                str = str + signals[i];
            else
                str = str + signals[i + (primaryStatesCountSize * j)];
        }
        if (std::find(uniqueSignals.begin(), uniqueSignals.end(), str) == uniqueSignals.end())
        {
            uniqueSignals.push_back(str);
            minimisationMap[counter].count = uniqueSignals.size() - 1;
        }
        else
        {
            iter = std::find(uniqueSignals.begin(), uniqueSignals.end(), str);
            minimisationMap[counter].count = std::distance(uniqueSignals.begin(), iter);
        }
        minimisationMap[counter].uniqueSignal = std::move(str);
        counter++;
    }
}

void minimiseMealyMachine(
    std::vector<std::string>& uniqueSignals,
    std::unordered_map<int, MachineClass>& minimisationMap,
    const int& primaryStatesCountSize,
    const std::vector<std::string> transitions,
    std::vector<std::string>& signals,
    const int& stringCounter)
{
    int uniqueSignalsCount;
    int counter;
    std::string str = "";
    std::vector<std::string>::iterator iter;

    do
    {
        uniqueSignalsCount = uniqueSignals.size();
        counter = 0;
        uniqueSignals.clear();

        for (size_t i = 0; i < transitions.size(); i++)
        {
            signals[i] = std::to_string(minimisationMap[std::stoi(transitions[i]) - 1].count);
        }

        for (size_t i = 0; i < primaryStatesCountSize; i++)
        {
            for (size_t j = 0; j < stringCounter; j++)
            {
                if (j == 0)
                    str = str + signals[i];
                else
                    str = str + signals[i + (primaryStatesCountSize * j)];
            }
            str = str + std::to_string(minimisationMap[i].count);
            if (std::find(uniqueSignals.begin(), uniqueSignals.end(), str) == uniqueSignals.end())
            {
                uniqueSignals.push_back(str);
                minimisationMap[counter].count = uniqueSignals.size() - 1;
            }
            else
            {
                iter = std::find(uniqueSignals.begin(), uniqueSignals.end(), str);
                minimisationMap[counter].count = std::distance(uniqueSignals.begin(), iter);
            }
            str.pop_back();
            minimisationMap[counter].uniqueSignal = std::move(str);
            counter++;
        }
    } while (uniqueSignalsCount != uniqueSignals.size());
}

void generateOutputMealyStates(
    std::ofstream& output,
    std::unordered_map<int, MachineClass>& minimisationMap,
    std::vector<int>& uniqueMachineClasses)
{
    std::vector<std::string> uniqueClassStates;

    for (size_t i = 0; i < minimisationMap.size(); i++)
    {
        if (std::find(uniqueClassStates.begin(), uniqueClassStates.end(),
            std::to_string(minimisationMap[i].count)) == uniqueClassStates.end())
        {
            uniqueClassStates.push_back(std::to_string(minimisationMap[i].count));
            uniqueMachineClasses.push_back(i);
            output << ";" << minimisationMap[i].count;
        }
    }
}

void generateOutputMealyTransitions(
    std::ofstream& output,
    std::unordered_map<int, MachineClass>& minimisationMap,
    std::vector<std::string>& primarySignals,
    const int& stringCounter,
    std::vector<int>& uniqueMachineClasses,
    const int& primaryStatesCountSize,
    std::vector<std::string>& transitions)
{
    int counter = 0;

    for (size_t i = 0; i < stringCounter; i++)
    {
        output << counter << ";";
        for (size_t j = 0; j < uniqueMachineClasses.size(); j++)
        {
            if (i == 0)
                output << minimisationMap[std::stoi(transitions[uniqueMachineClasses[j]]) - 1].count << "/"
                << primarySignals[uniqueMachineClasses[j]] << ";";
            else
                output << minimisationMap[std::stoi(transitions[uniqueMachineClasses[j] + i * primaryStatesCountSize]) - 1].count
                << "/" << primarySignals[uniqueMachineClasses[j] + i * primaryStatesCountSize] << ";";

        }
        output << std::endl;
        counter++;
    }
}