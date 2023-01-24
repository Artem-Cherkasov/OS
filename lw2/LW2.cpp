#include "stdafx.h"
#include "mealyMinimisationFunc.h"
#include "mooreMinimisationFunc.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Invalid arguments";
        return 1;
    }

    const char delim = ';';
    const char separator = '/';
    const std::string mealyMachine = "mealy";
    const std::string mooreMachine = "moore";

    std::ifstream input(argv[2]);
    std::ofstream output(argv[3]);

    if (argv[1] == mealyMachine)
    {
        std::vector<std::string> primaryStatesCount;
        std::vector<std::string> transitions;
        std::vector<std::string> signals;
        std::vector<std::string> uniqueSignals;
        int stringCounter = 0;

        stringCounter = parseMealyMachine(input, primaryStatesCount, transitions, signals);

        std::vector<std::string> primarySignals = signals;
        std::unordered_map<int, MachineClass> minimisationMap;

        initMealyMinimisationMap(minimisationMap, primaryStatesCount.size(), signals, uniqueSignals, stringCounter);

        minimiseMealyMachine(uniqueSignals, minimisationMap, primaryStatesCount.size(), transitions, signals, stringCounter);

        std::vector<int> uniqueMachineClasses;
        generateOutputMealyStates(output, minimisationMap, uniqueMachineClasses);

        output << std::endl;

        generateOutputMealyTransitions(
            output,
            minimisationMap,
            primarySignals,
            stringCounter,
            uniqueMachineClasses,
            primaryStatesCount.size(),
            transitions);
    }
    if (argv[1] == mooreMachine)
    {
        std::string str = "";
        std::vector<std::string> primarySignals;
        std::vector<std::string> primaryStates;
        std::vector<std::string> transitions;

        int stringCounter = parseMooreMachine(input, transitions, primarySignals, primaryStates);

        std::vector<std::string> signals = primarySignals;
        std::unordered_map<int, MachineClass> minimisationMap;
        std::vector<std::string> uniqueSignals;
        initMooreMinimisationMap(minimisationMap, primaryStates.size(), signals, uniqueSignals, stringCounter);

        int uniqueSignalsCount = 0;
        std::vector<std::string> newTransitions = transitions;
        std::string tmpString = "";
        minimiseMooreMachine(uniqueSignals, minimisationMap, primaryStates.size(), transitions, newTransitions, stringCounter);

        std::vector<int> uniqueMachineClasses;
        generateOutputMooreStates(output, minimisationMap, uniqueMachineClasses, primarySignals);

        generateOutputMooreTransitions(output, stringCounter, minimisationMap, uniqueMachineClasses, primaryStates, transitions);
    }

    return 0;
}
