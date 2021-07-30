

/*
This is my implementation of the quick sort algorithm, which is a naive sorting algorithm

*/

#include <iostream>


// function that takes sequence of integers as input and stores them in array
void input(std::istream& is, int*& begin, int*& end){ // begin and end are nullptr's passed in as referenz
  std::cout << "Enter any integer sequence, with the first number being the length of the sequence: \n";
  unsigned int length; is >> length;

  begin = new int[length]; // initialize empty array, with pointer called "begin"
  end = begin+length; // end is the pointer to the first element NOT in the array
  // fill array
  for (int* it = begin; it < end; ++it) is >> *it;
}


// function that outputs sorted array
void output(std::ostream& os, const int* begin, const int* end){
  bool first = true;
  for (const int* pt = begin; pt < end; ++pt){
    if (first == true) {
      os << *pt;
      first = false;
    }
    else os << " " << *pt;
  }
}


//the values pointed to by pointers a and b have get swapped.
void swap(int* a, int* b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

// now the pivot function that sort an array by comparing the first element (the pivot) to all other elements
// end returns the pointer to the pivot
int* pivot(int* begin, int* end){
  int* piv = begin;
  int* next = begin + 1;
  int* last = end;

  while(next < last){
    if (*piv > *next) { // swap both elements and increment their pointers by one
      swap(piv, next);
      ++piv; ++next;
    }
    else swap(next, --last); //swap next element with last element and decrease range
  }
  return piv; // return the pointer to the pivot
}


// now the quicksort function, which calls itself, i.e. is recursive
void quicksort(int* begin, int* end){
  if (begin < end){
    int* piv = pivot(begin, end);
    quicksort(begin, piv); // sort range to the left of pivot
    quicksort(piv+1, end); // sort range to the right of pivot
  }
}



int main(){

  int* begin = nullptr;
  int* end = nullptr;
  input(std::cin, begin, end);
  quicksort(begin, end);
  output(std::cout, begin, end);
  if (begin) delete[] begin;

  return 0;
}
