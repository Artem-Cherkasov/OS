#pragma once
#include "Token.h"
#include "TokenType.h"
#include <iostream>
#include <vector>

std::string MapTokenTypeToString(TokenType const &type) {
    switch (type) {
        case TokenType::CONST:
            return "const";
        case TokenType::LET:
            return "let";
        case TokenType::VAR:
            return "var";
        case TokenType::IF:
            return "if";
        case TokenType::ELSE:
            return "else";
        case TokenType::WHILE:
            return "while";
        case TokenType::FOR:
            return "for";
        case TokenType::DO:
            return "do";
        case TokenType::TRUE:
            return "true";
        case TokenType::FALSE:
            return "false";
        case TokenType::IMPORT:
            return "import";
        case TokenType::EXPORT:
            return "export";
        case TokenType::EQUALITY:
            return "equality";
        case TokenType::STRICT_EQUALITY:
            return "strict equality";
        case TokenType::NOT_EQUALITY:
            return "not equality";
        case TokenType::NOT_STRICT_EQUALITY:
            return "not strict equality";
        case TokenType::GREATER:
            return "greater";
        case TokenType::LESS:
            return "less";
        case TokenType::GREATER_EQUAL:
            return "greater or equal";
        case TokenType::LESS_EQUAL:
            return "less or equal";
        case TokenType::ASSIGNMENT:
            return "assignment";
        case TokenType::COMMA:
            return "comma";
        case TokenType::SEMICOLON:
            return "semicolon";
        case TokenType::COLON:
            return "colon";
        case TokenType::CURLY_OPENING:
            return "curly opening";
        case TokenType::CURLY_CLOSING:
            return "curly closing";
        case TokenType::ROUND_OPENING:
            return "round opening";
        case TokenType::ROUND_CLOSING:
            return "round closing";
        case TokenType::LINE:
            return "line";
        case TokenType::PLUS:
            return "plus";
        case TokenType::MINUS:
            return "minus";
        case TokenType::MULTIPLY:
            return "multiply";
        case TokenType::DIVIDE:
            return "divide";
        case TokenType::NOT:
            return "not";
        case TokenType::AND:
            return "and";
        case TokenType::OR:
            return "or";
        case TokenType::COMMENT:
            return "comment";
        case TokenType::IDENTIFIER:
            return "identifier";
        case TokenType::NUMBER:
            return "number";
        case TokenType::ERROR:
            return "error";
        default:
            return "unknown";
    }
}

void PrintTokens(std::ostream &output, std::vector<Token> const &data) {
    for (const auto &item: data) {
        output << "[" << MapTokenTypeToString(item.type) << "] [" << item.position.line << ":" << item.position.column << "] (" << item.source << ")" << std::endl;
    }
}
