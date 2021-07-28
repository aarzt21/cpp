
// This is a program is a calculator (actually a parser with evaluation) that allows you to calculate with
// complex numbers.... a complex number has to be entered in the format [3,-1] where 3 is the real part and
// -1 the imaginary part..... 
#include<iostream>
#include<string>
#include <istream>
#include <cassert>
#include<cmath>



//definition of our custom complex type ---------------------------------------------------------------------
struct complex {
  double real;
  double imag;
};

// tolerance used for floating point comparison
const double abs_err = 1e-6;

// complex number output: takes in ostream as reference, assigns [...] to it and returns the outstream as
// reference again
std::ostream & operator<< (std::ostream& out, const complex& a){
  return out << '[' << a.real << ',' << a.imag << ']';
}


// reads complex number from input_rational
// returns a boolean to indicate whether the input was valid or not
bool read_input(std::istream& in, complex& a){
  unsigned char c;
  // (in >> c) prüft nicht nur ob die Zuweisung klappt sondern es wird c auch gleich der erste character
  // der eingabe zugewiesen. Dann prüfen wir ob dieser erste Character '[' ist.
  // Anschliessend überprüft (in >> a.real) nicht nur ob die Zuweisung des Nächsten charakters der eingabe
  // nach a.real möglich ist sondern macht diese auch.  Dann prüft (in >> c) wieder ob der nächste Character
  // nach c assigned werden kann und c != ',' prüft ob es ein ',' ist. ......
  // D.h: If(in >> c) prüft nicht nur ob die Zuweisung möglich ist sondern es wird dem c auch gleich der erste
  // character aus der Eingabe zugewiesen.
  if(!(in >> c) || c != '['
    || !(in >> a.real)
    || !(in >> c) || c != ','
    || !(in >> a.imag)
    || !(in >> c) || c!= ']') return false;

  else return true;

}


std::istream& operator>>(std::istream& in , complex& a){
  if(!read_input(in,a)){
    in.setstate(std::ios::failbit);
  }
  return in;
}

// now we gonna overload the arithmetic operators
complex operator+(const complex& a, const complex& b){
  complex result;
  result.real = a.real + b.real;
  result.imag = a.imag + b.imag;
  return result;
}

complex operator-(const complex& a, const complex& b){
  complex result;
  result.real = a.real - b.real;
  result.imag = a.imag - b.imag;
  return result;
}

complex operator*(const complex& a, const complex& b){
  complex result;
  // boom motherfucker: got it right!
  result.real = a.real*b.real - (a.imag*b.imag);
  result.imag = a.real*b.imag + a.imag*b.real;
  return result;
}

complex operator/(const complex& a, const complex& b){
  complex result;
  double den;
  // got it right again
  den = b.real*b.real + b.imag*b.imag;
  result.real = (a.real*b.real + a.imag*b.imag) / den;
  result.imag = (a.real * (-b.imag) + a.imag*b .real)/den;

  return result;
}


// negation operator
complex operator-(const complex & a){
  complex result;
  result.real = -a.real;
  result.imag = -a.imag;
  return result;
}

// comparison operators
bool operator==(const complex& a , const complex& b){
  return fabs(a.real - b.real) < abs_err && fabs(a.imag - b.imag) < abs_err;
}

bool operator!=(const complex& a , const complex& b){
  return !(a==b);
}




// helper functions -----------------------------------------------------------------------------------------

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



// Calculator --------------------------------------------------------

// forward declarations

// Pre: is = expression
// Post: term is extracted from is, and its value is returned
complex expression(std::istream& is);

//Pre: is = terminated
// Post: term is extracted from is, and its value is returned
complex term(std::istream& is);


//Pre: is = factor
// Post: factor is extracted from is, and its value is returned
complex factor(std::istream& is);


//definitions
complex number(std::istream& is){
  complex num = complex();
  is >> num;
  return num;
}

complex expression(std::istream& is){
  complex value = term(is);
  while(true){
    if(consume(is,'+')){value = value + term(is);}
    else if(consume(is,'-')){value = value - term(is);}
    else return value;
  }
}

complex term (std::istream& is){
  complex value = factor(is);
  while(true){
    if(consume(is,'*')) value = value*factor(is);
    else if (consume(is,'/')) value = value/factor(is);
    else return value;
  }
}

complex factor(std::istream& is){
  complex value = complex();
  if(consume(is,'(')) {
    value = expression(is);
    consume(is,'(');
  }

  else if (consume(is,'-')){
    value = -factor(is);
  }

  else {
    value = number(is);
  }

  return value;
}


complex evaluation(std::istream& input){
  complex value = expression(input);
  assert(consume(input, '='));
  return value;
}


int main(){
  std::cout << "input expressions followed by = " << "\n";
  std::cout << evaluation(std::cin) << "\n";
  return 0;
}
