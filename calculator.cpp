

// This program implements a calculator using the Extended Backus Naur Form (EBNF) from my informatics lecture. It supposed to illustrate how
// an EBNF is implemented in code. In concrete terms, the ENBF allows to program a calculator that can evaluate expressions like 3+3*3 correctly. 

// Syntax in EBNF:
// ---------------
// evaluation = expression "=".
// expression =  term { "+" term | "-" term }.
// term = factor { "*" factor | "/" factor }.
// factor = number | "(" expression ")" | "-" factor.
// number = digit {digit}.
// digit = '0' | '1' | ... | '9'.

#include<iostream>
#include<istream>
#include<cassert>


// Helper functions -----------------------------------------------------------------

// PRE:  valid input stream input
// POST: returns true if further input is available
//       otherwise false
bool input_available(std::istream& input){
  input.peek(); // in case end of input has not yet been seen
  return input.good();
}

// PRE:  valid input stream input
// POST: the next character at the stream is returned (but not consumed)
//       if no input is available, 0 is returned
// wir können das nächste Zeichen im Stream angucken OHNE es zu verbrauchen! Darauf können wir entscheiden ob
// wir es vebrauchen oder ob wir jemand anders aufrufen, der es verbrauchen kann
char peek(std::istream& input) {
  if (input_available(input)){
    return input.peek();
  } else {
    return 0;
  }
}

// POST: leading whitespace characters are extracted
//       from input, and the first non-whitespace character is returned (but not consumed)
//       if an error or end of stream occurs, 0 is returned
char lookahead(std::istream& input) {
  input >> std::ws;         // skip whitespaces
  return peek(input);
}

// PRE:  Valid input stream input, expected > 0
// POST: If ch matches the next lookahead then it is consumed and true is returned
//       otherwise no character is consumed and false is returned
bool consume(std::istream& input, char expected) {
  assert(expected > 0);
  if (lookahead(input) == expected) {
    input.get();
    assert(input.good());
    return true;
  }
  return false;
}


// translate the ENBF into functions ---------------------------------------------------------------------------

// (forward) declarations
double expression(std::istream& input);
double term(std::istream& input);
double factor(std::istream& input);

// define the functions

//Pre: -
//Post: returns true if input is digit and false otw.
bool isDigit(char x){
  return x >= '0' && x <= '9';
}

// PRE:  valid input stream with a digit as next consumable character
// POST: returns the unsigned integer consumed from the stream
// number = digit {digit}.
unsigned int number(std::istream& input) {
  char ch = lookahead(input); //get the character from the stream
  assert(isDigit(ch)); // make sure its a digit

  unsigned int num = 0;
  while(isDigit(ch) && input >> ch) { // read remaining digits
    num = num * 10 + ch - '0';
    ch = peek(input);
  }

  return num;
}


// PRE:  input = expression...
// POST: extracted expression from input, and
//       return its value
// expression =  term { "+" term | "-" term }
double expression(std::istream& input) {
  double value = term(input);        // calls term
  while (true) {
    if (consume(input, '+'))
      value += term(input);          // "+" term
    else if (consume(input, '-'))
      value -= term(input);          // "-" term
    else
      return value;
  }
}


// PRE:  input = term...
// POST: extract term from input, and
//       return its value
// term = factor { "*" factor | "/" factor }
double term(std::istream& input) {
  double value = factor(input);        // call factor

  while (true) {
    if (consume(input, '*'))
      value *= factor(input);          // "*" factor
    else if (consume(input, '/'))
      value /= factor(input);          // "/" factor
    else
      return value;
  }
}


// PRE: input = factor...
// POST: extract factor from input, and
//       return value of factor
// factor = number | "(" expression ")" | "-" factor
double factor(std::istream& input) {
  double value;

  if (consume(input, '(')) {
    value = expression(input);      // calls either expression
    assert(consume(input, ')'));            // ")"
  } else if (consume(input, '-')) {
    value = -factor(input);         // or factor
  } else {
    value = number(input);  // or number
  }

  return value;
}


// PRE:  valid expression in input stream, terminated by "="
// POST: consume expression from stream input and terminating "=", and
//       return value of expression
// evaluation = expression "=".
double evaluation(std::istream& input) {
  double value = expression(input); // calls expression
  assert(consume(input,'='));
  return value;
}


int main() {
  std::cout << "input expressions followed by '=' each\n\ncalc> ";

  while (lookahead(std::cin)){
    std::cout << evaluation(std::cin) << "\n\ncalc> ";
  }

  return 0;
}
