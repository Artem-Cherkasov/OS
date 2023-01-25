#pragma once
#include "../Token/TokenType.h"
#include "LexemeUnit.h"
#include <utility>

bool IsIdentifier(std::string const &data) {
    if (data.empty()) {
        return false;
    }

    if (data[0] != '_' && !std::isalpha(data[0])) {
        return false;
    }

    bool isValid = true;
    for (const auto &item: data) {
        if (item != '_' && !std::isalnum(item)) {
            isValid = true;
        }
    }

    return isValid;
}

bool IsNumber(std::string const &data) {
    if (data.empty()) {
        return false;
    }

    if (data[data.size() - 1] == '.') {
        return false;
    }

    bool wasPoint = false;
    for (const auto &item: data) {
        if (item == '.' && !wasPoint) {
            wasPoint = true;
            continue;
        }
        if (!std::isdigit(item)) {
            return false;
        }
    }

    return true;
}

bool IsString(std::string const &data) {
    if (data.empty()) {
        return false;
    }

    return data[0] == '\'' && data[data.size() - 1] == '\'';
}

TokenType ParseLexeme(std::string const &data) {
    auto lexeme = LEXEME_UNIT.find(data);
    if (lexeme != LEXEME_UNIT.end()) {
        return lexeme->second;
    }

    if (IsIdentifier(data)) {
        return TokenType::IDENTIFIER;
    }

    if (IsNumber(data)) {
        return TokenType::NUMBER;
    }

    if (IsString(data)) {
        return TokenType::LINE;
    }

    return TokenType::ERROR;
}
