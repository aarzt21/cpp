#include <iostream>

/*

This is my homework assignment for the quicksort algo: 

Write a program that implements a naive sorting algorithm that sort the contents of an integer array in ascending order.
The algorithm to be used is described in steps below; do not use a different algorithm.

1. The goal of this exercise is to exercise the usage of pointers: Instead of using a vector to manage the values to be sorted,
   you have to explicitly allocate the necessary memory yourself and to traverse the memory block using ranges.
2. In particular, usage of vectors is forbidden.
3. Dereferencing pointers with operator [] is forbidden.
   Performing pointer addition/substraction (a+i) is forbidden as well due to the equation *(a+i) = a[i].
   The only exception is function input. Note that pointer incrementation/decrementation (++p, --p, p++, p--, p+1, p-1) is allowed,
   and is the expected method to traverse memory ranges.
4. Usage of library sorting function is of course not allowed.

*/


/*
 The algorithm to implement is called quicksort:

 It takes a range of values on its
 input and picks a pivot among these values. Then, it partitions the range: it swaps the elements within the
 range so that all elements less than pivot are on its "left side", and all elements greater on equal than the
 pivot are on its "right side". Then, it repeats the entire procedure to the "left" and "right" sides separately,
 picking new pivots for them and so on. The way to choose a pivot is arbitrary: in this task, you should pick the
 first element of the range.

*/


// POST: begin denotes the start of an allocated memory chunk
//       end denotes the past-the-end pointer of this memory chunk
//       the range contains the sequence of integer values read from input stream is
void input(std::istream& is, int*& begin, int*& end) {
    std::cout << "Enter your sequence, starting with its length: \n";
    unsigned int length;
    is >> length;

    begin = new int[length]; // create new array of certain size and save pointer to its first element in begin
    end = begin + length;

    for(int* pt = begin; pt < end; ++pt) is >> *pt;
}


// PRE: begin points within an allocated memory chunk
//      end points within the same memory chunk, not before begin
// POST: the sequence of integer values in memory range [begin; end)
//       has been printed to os, separated by single spaces.
void output(std::ostream& os, const int* begin, const int* end) {
    // TODO: iterate over the range [begin; end) and output all values stored in it
    bool first = true;
    for(const int* it = begin; it < end; ++it){
      if(!first){
        os << ' ';
      } else {
        first = false;
      }
      os << *it;
    }
}


// POST: the values pointed to by pointers a and b have been swapped.
void swap(int* a, int* b) {
    // TODO: swap the values
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


// PRE: begin points within an allocated memory chunk
//      end point later (strictly) within the same memory chunk
// POST: elements in range [begin; end) are the same (likely in different order)
//      Resulting pointer p points within range [begin; end)
//      *p is the old value of *begin
//      Elements in range [begin; p) are < to *p
//      Elements in range (p; end) are >= to *p.
int* pivot(int* begin, int* end) {
    int* piv = begin;
    int* next = begin + 1;
    int* e = end;
    while(next != e){
      if(*next < *piv) swap(next++, piv++); // swap and increment the pointers
      else swap(next, --e); // else swap the next element with last element in array and shrink range
    }
    return piv; // return pointer of/to the pivot
}


// PRE: begin points within an allocated memory chunk
//      end points later within the same memory chunk
// POST: elements in range [begin; end) are the same, but sorted in increasing
//       order.
void quicksort(int* begin, int* end) {
    // Recursive approach: select a pivot and sort the sub-ranges on both sides of it
    if(begin < end){
      int* piv = pivot(begin, end);
      quicksort(begin, piv); // sort range to the left of pivot
      quicksort(piv+1, end); //sort range to the right of pivot
    }
}




// test if the range is input and output correctly
void test_input_output() {
    int* begin = nullptr;
    int* end = nullptr;
    input(std::cin, begin, end);
    output(std::cout, begin, end);
    if (begin) delete[] begin;
}

// insert two numbers, swap them, print the output
void test_swap() {
    int x, y;
    std::cin >> x >> y;
    swap(&x, &y);
    std::cout << x << " " << y << "\n";
}

// read input and calculate the pivot
// print the partitioned range:
//   all elements < pivot should be on the left of it
//   all elements >= pivot should be on the right of it
void test_pivot() {
    int* begin = nullptr;
    int* end = nullptr;
    input(std::cin, begin, end);
    int p = *pivot(begin, end);
    std::cout << p << "\n";
    output(std::cout, begin, end);
    if (begin) delete[] begin;
}

// test the complete implementation of quicksort
void test_quicksort() {
    int* begin = nullptr;
    int* end = nullptr;
    input(std::cin, begin, end);
    quicksort(begin, end);
    output(std::cout, begin, end);
    if (begin) delete[] begin;
}

int main() {
    char test_type;
    std::cin >> test_type;
    switch (test_type) {
        case 'i':
            test_input_output();
            break;
        case 's':
            test_swap();
            break;
        case 'p':
            test_pivot();
            break;
        case 'q':
            test_quicksort();
            break;
        default:
            std::cout << "Unknown test type: " << test_type << std::endl;
    }
    return 0;
}
