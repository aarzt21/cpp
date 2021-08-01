
/*
Informatics homework: 

Words, e.g.  in a dictionary or an index are sorted lexicographically as given by the alphabet

Task: Implement a lexicographic comparison function for strings using the alphabetical orderding
provided by the ASCII code.


A string a is lexicographically smaller than a string b, if
    1. the first character of a in that both a and b differ is smaller than the corresponding character
      of b (e.g bycycle < bike) because the first different characters are c < k

    2. the string a forms the start of b, but is shorte (e.g. web < website)


Write a function that compares two strings. The function must return TRUE if the first string is smaller than the
second with respect to lexicographic order. NOTE: Using string comparisons is not allowed. 
*/

#include<iostream>
#include<string>
using Iterator = std::string::iterator;

//PRE: [first1, last1) and [first2, last2) are valid ranges
//POST: Returns true if string at [first1, last1) is strictly lexicographically smaller than string at [first2, last2).
//      Returns false otw.


bool lexicographic_compare(Iterator first1, Iterator last1, Iterator first2, Iterator last2){
  while (first1!=last1){
    //if second word is done or letter in second word is smaller than letter in first word
   if (first2==last2 || *first2<*first1) return false;
   else if (*first1<*first2) return true;
   ++first1; ++first2;
  }
 return (first2!=last2);
}


// Now write a program that compares two strings and outputs the lexicographic minimum of the two.
// If they area identical output "EQUAL"
int main (){

  std::string string1;
  std::string string2;
  std::cout << "Enter two words separate by a white space: \n";
  std::cin >> string1, std::cin >> string2;

  if (lexicographic_compare(string1.begin(), string1.end(), string2.begin(), string2.end())) std::cout << string1;
  else if (lexicographic_compare(string2.begin(), string2.end(), string1.begin(), string1.end())) std::cout << string2;
  // if first string is not smaller than second one and second one is not smaller than first one, then they have to be equal
  else std::cout << "EQUAL";


  return 0;
}
