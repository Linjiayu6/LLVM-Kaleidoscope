#include<stdio.h>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <string>

// Lexer
enum Token {
  token_eof = -1,

  token_define = -2,
  token_extern = -3,

  token_identifier = -4,
  token_number = -5
};

static std::string IdentifierStr;
static double NumVal;

// return next token from the input
static int gettoken() {
  static int LastChar = ' ';
  
  // skip whitespace
  while(isspace(LastChar))
    LastChar = getchar();

  // check [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    // eg: let name = 2, match 'name' until whitespace.
    while(isalnum(LastChar = getchar()))
      IdentifierStr += LastChar;

    // check identifier
    if (IdentifierStr == "def") {
      return token_define;
    }

    // check token_extern
    if (IdentifierStr == "extern") {
      return token_extern;
    }

    return token_identifier;
  }

  // check  Number: [0-9.]+
  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;

    while (isdigit(LastChar) || LastChar == '.')
    {
      NumStr += LastChar;
      LastChar = getchar();
    }
    NumVal = strtod(NumStr.c_str(), nullptr);
    return token_number;
  }

  // check comments until end of line
  if (LastChar == '#') {
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) {
      return gettoken();
    }
  }

  // check is end
  if (LastChar == EOF) {
    return token_eof;
  }

  // continue and just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

static int CurToken;
static int getNextToken() { return CurToken = gettoken(); }

static void MainLoop() {
  while (true) {
    fprintf(stderr, "ready> ");
    switch (CurToken)
    {
    case token_eof:
      return;

    case ';':
      getNextToken();
      break;
    
    default:
      break;
    }
  }
  
}

int main() {
  // // Install standard binary operators.
  // // 1 is lowest precedence.
  // BinopPrecedence['<'] = 10;
  // BinopPrecedence['+'] = 20;
  // BinopPrecedence['-'] = 20;
  // BinopPrecedence['*'] = 40; // highest.

  // Prime the first token.
  fprintf(stderr, "ready> ");
  
  getNextToken();

  /* printf("SUM: %d\n", CurToken); */

  // Run the main "interpreter loop" now.
  MainLoop();

  return 0;
}

