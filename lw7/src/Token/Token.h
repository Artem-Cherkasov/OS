#pragma once

struct Token {
    std::string source;
    TokenType type;
    Position position;
};
