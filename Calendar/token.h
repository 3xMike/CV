#pragma once

enum class TokenType {
  DATE, // 11-10-2000
  EVENT,// "some ev"
  COLUMN,// date / event
  LOGICAL_OP,// OR, AND
  COMPARE_OP,// >, <, ...
  PAREN_LEFT,// (
  PAREN_RIGHT,// )
};

struct Token {
  const string value;
  const TokenType type;
};

vector<Token> Tokenize(istream& cl);
