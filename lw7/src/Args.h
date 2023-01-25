#pragma once
#include <iostream>
#include <optional>

struct Args {
    std::string input;
    std::string output;
};

std::optional<Args> ParseArgs(int argc, char *argv[]) {
    if (argc != 3) {
        return std::nullopt;
    }

    return Args{argv[1], argv[2]};
}
