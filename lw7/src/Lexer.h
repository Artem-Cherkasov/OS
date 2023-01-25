#pragma once
#include "Lexeme/Lexeme.h"
#include "Token/Token.h"
#include <sstream>
#include <utility>

class Lexer {
public:
    explicit Lexer(std::istream &stream)
        : m_stream(stream) {}

    std::vector<Token> Parse() {
        std::vector<Token> result;

        std::string line;
        while (std::getline(m_stream, line)) {
            std::stringstream ss(line);

            std::string item;
            while (ss >> item) {

                int offset = ss.tellg();
                auto currentPosition = offset - item.size();
                if (offset == -1) {
                    currentPosition = line.size() - item.size();
                }
                m_position.column = ++currentPosition;

                auto token = ParseLexeme(item);
                result.push_back({.source = item,
                                  .type = token,
                                  .position = {
                                          m_position.line,
                                          m_position.column,
                                  }});
                std::cout << item << " " << m_position.line << ":" << m_position.column << std::endl;
            }

            m_position.line++;
            m_position.column = 1;
        }

        return result;
    }

private:
    std::istream &m_stream;
    Position m_position{1, 1};
};
