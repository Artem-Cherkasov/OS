#pragma once
#include "stdafx.h"

struct MachineClass
{
    int count;
    std::string uniqueSignal;
};

void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);