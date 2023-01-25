#pragma once

enum class TokenType {
    CONST,
    LET,
    VAR,

    IF,
    ELSE,

    WHILE,
    DO,
    FOR,

    TRUE,
    FALSE,

    IMPORT,
    EXPORT,

    EQUALITY,
    STRICT_EQUALITY,
    NOT_EQUALITY,
    NOT_STRICT_EQUALITY,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,

    ASSIGNMENT,

    COMMA,
    SEMICOLON,
    COLON,

    CURLY_OPENING,
    CURLY_CLOSING,
    ROUND_OPENING,
    ROUND_CLOSING,

    LINE,

    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,

    NOT,
    AND,
    OR,

    COMMENT,

    IDENTIFIER,
    NUMBER,
    ERROR,
};
