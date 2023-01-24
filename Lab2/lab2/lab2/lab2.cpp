#include "stdafx.h"

void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void matrixInit(std::vector<std::vector<std::string>>& matrix, std::ifstream& input)
{
    std::string str;
    char delim = ';';
    std::vector<std::string> matrixString;
    while (getline(input, str))
    {
        tokenize(str, delim, matrixString);
        matrixString.erase(matrixString.begin());
        matrix.push_back(std::move(matrixString));
    }
}

struct MachineClass
{
    int count;
    std::string uniqueSignal;
};

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
    std::vector<std::vector<std::string>> matrix;

    if (argv[1] == mealyMachine)
    {
        std::string str = "";
        std::string primaryStatesCount = "";
        std::vector<std::string> outVect;
        std::vector<std::string> tmpVect;
        std::vector<std::string> transitions;
        std::vector<std::string> signals;
        std::vector<std::string> uniqueSignals;
        int counter = 0;
        int stringCounter = 0;
        std::string chars;
        chars.insert(chars.begin(), delim);
        std::unordered_map<int, std::string> primaryStates;

        getline(input, primaryStatesCount);
        for (char c : chars)
        {
            primaryStatesCount.erase(remove(primaryStatesCount.begin(), primaryStatesCount.end(), c), primaryStatesCount.end());
        }

        //std::cout << primaryStates << std::endl;
        
        while (getline(input, str))
        {
            stringCounter++;
            tokenize(str, delim, outVect);
            outVect.erase(outVect.begin());
            for (size_t i = 0; i < outVect.size(); i++)
            {
                primaryStates[counter] = outVect[i];
                tokenize(outVect[i], separator, tmpVect);
                transitions.push_back(tmpVect[0]);
                signals.push_back(tmpVect[1]);
                //std::cout << signals[counter] << std::endl;
                //signals.push_back(std::move(tmpVect[0]));
                /*std::cout << tmpVect[0] << " " << tmpVect[1] << std::endl;*/
                counter++;
                tmpVect.clear();
            }
            outVect.clear();
        }

        std::string tmpString = "";
        std::vector<std::string> minimVec;
        std::unordered_map<int, MachineClass> minimisationMap;
        counter = 0;
        std::vector<std::string>::iterator iter;
        for (size_t i = 0; i < primaryStatesCount.size(); i++)
        {
            for (size_t j = 0; j < stringCounter; j++)
            {
                if (j == 0)
                    tmpString = tmpString + signals[i];
                else
                    tmpString = tmpString + signals[i + (primaryStatesCount.size() * j)];
            }
            if (std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString) == uniqueSignals.end())
                uniqueSignals.push_back(tmpString);
            iter = std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString);
            minimisationMap[counter].count = std::distance(uniqueSignals.begin(), iter);
            minimisationMap[counter].uniqueSignal = std::move(tmpString);
            counter++;            
        }

        for (size_t i = 0; i < transitions.size(); i++)
        {
            transitions[i] = std::to_string(minimisationMap[std::stoi(transitions[i]) - 1].count);
        }

        counter = 0;
        uniqueSignals = {};
        for (size_t i = 0; i < primaryStatesCount.size(); i++)
        {
            for (size_t j = 0; j < stringCounter; j++)
            {
                if (j == 0)
                    tmpString = tmpString + transitions[i];
                else
                    tmpString = tmpString + transitions[i + (primaryStatesCount.size() * j)];
            }
            if (std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString) == uniqueSignals.end())
                uniqueSignals.push_back(tmpString);
            iter = std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString);
            minimisationMap[counter].count = std::distance(uniqueSignals.begin(), iter);
            minimisationMap[counter].uniqueSignal = std::move(tmpString);
            counter++;
            //std::cout << tmpString << std::endl;
        }

        /*do
        {

        } while (true);*/

        /*for (auto i : transitions)
        {
            std::cout << i << std::endl;
        }*/

        for (const std::pair<int, MachineClass>& tup : minimisationMap)
        {
            std::cout << tup.first << " " << tup.second.count << " " << tup.second.uniqueSignal << std::endl;
        }

        return 0;
    }
}

/*std::string tmpString = "";
std::vector<std::string> minimVec;
std::unordered_map<int, std::string> minimisationMap;
counter = 0;
for (size_t i = 0; i < primaryStatesCount.size(); i++)
{
    for (size_t j = 0; j < stringCounter; j++)
    {
        if (j == 0)
            tmpString = tmpString + signals[i];
        else
            tmpString = tmpString + signals[i + (primaryStatesCount.size() * j)];
    }

    if (std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString) == uniqueSignals.end())
        uniqueSignals.push_back(tmpString);

    minimVec.push_back(std::move(tmpString));


    minimisationMap[counter] = tmpString;
    counter++;

    std::cout << tmpString << std::endl;

    if (std::find(uniqueSignals.begin(), uniqueSignals.end(), tmpString) == uniqueSignals.end())
        uniqueSignals.push_back(std::move(tmpString));
    else
        tmpString.clear();
}*/


/*for (auto i : minimVec)
{
    std::cout << i << std::endl;
}*/

//std::cout << stringCounter;

//std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

/*for (const std::pair<int, std::string>& tup : minimisationMap)
{
    std::cout << tup.first << " " << tup.second << std::endl;
}*/

/*tokenize(str, delim, first);

matrixInit(matrix, input);

std::set<std::string> st;
std::string val = "";
std::vector<std::string> out;
std::vector<MachineClass> vect;

for (size_t i = 0; i < first.size(); i++)
{
    for (size_t j = 0; j < matrix.size(); j++)
    {
        tokenize(matrix[j][i], separator, out);
        val = val + out[1];
        out = {};
    }
    std::cout << val << std::endl;
    st.insert(val);
    val = "";
}
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
std::set<std::string>::iterator it = st.begin();
for (size_t i = 0; i < st.size(); i++)
{
    std::cout << *it << std::endl;
    it++;
}*/