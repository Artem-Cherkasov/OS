#include "src/Args.h"
#include "src/Lexer.h"
#include "src/Token/TokenFunction.h"
#include <fstream>
#include <queue>
#include <sstream>

int main(int argc, char *argv[]) {
    auto args = ParseArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "No arguments" << std::endl;
        return 1;
    }

    std::ifstream input(args.value().input);
    std::ofstream output(args.value().output);

    try {
        auto lexer = Lexer(input);
        auto tokens = lexer.Parse();
        PrintTokens(output, tokens);
        std::cout << "The analysis is successful!" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
