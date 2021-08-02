

/*
The objective is to implement a copy constructor, an assigment operator and a destructor for the class "avec",
which represents an array based vector.

*/
#include<iostream>
#include<cassert>


class avec {
  unsigned int length; // Size of the vector
  int* elements; // Vector elements (actually, a pointer to the first element)

public:
  // Constructor
  // POST: Instantiated a new avec with 'size' elements
  avec(unsigned int size){
    this->length = size;
    this->elements = new int[this->length];
  }

  // Copy constructor
  // POST: Instantiated a copy of vec.
  avec(const avec& vec){
    this->length  = vec.length;
    this->elements = new int[this->length];
    for (unsigned int i = 0; i < this->length; ++i){
      this->elements[i] = vec.elements[i];
    }

  }

  // POST: Assign to content of vec, return reference to the this-object.
  avec& operator=(const avec& vec){
    if (this->elements != vec.elements){
    avec copy = vec;
    std::swap(copy.length, this->length);
    std::swap(copy.elements, this->elements);
    //copy carries now the "trash" and is deallocated after this scope
  }
    return (*this);
  }

  //deconstructor
  // POST: Deallocate the content.
  ~avec(){
    delete[] this->elements;
  }

  // POST: Returns the size of the vector
  unsigned int size() const {
    return this->length;
  }

  // PRE:  i < size()
  // POST: Returns a reference to the ith element
  int& operator[](unsigned int i){
    assert(i < this->length);
    return *(elements+i); // Important: we return a the value of the ith element as a reference (i.e. an lvalue) so that we can assign new value if we like
  }

  // PRE:  i < size()
  // POST: Returns a reference to the ith element, or aborts the program
  //       if i is not a valid index
  int& at(unsigned int i){
    assert(i < this->length);
    return *(elements+i); // Important: we return a the value of the ith element as a reference (i.e. an lvalue) so that we can assign new value if we like
  }

  // POST: All vector elements were output to 'sink'
  void print(std::ostream& sink) const {
    int* end = this->elements + this->length;
    for (int* pt = this->elements; pt < end; ++pt){
      sink << *pt << " ";
    }
    sink << "\n";
  }
};



// POST: All elements of 'vec' were output to 'sink'
std::ostream& operator<<(std::ostream& sink, const avec& vec) {
  vec.print(sink);
  return sink;
}


int main(){

  // Instantiation test: Create avec and fill with integers and print them to console
  avec a = avec(5);
  a[0] = 6;
  a[1] = 6;
  a[2] = 6;
  a[3] = 6;
  a[4] = 6;

  std::cout << a;

  //Initialization test: init b with values of a
  avec b = a;
  std::cout << b;

  //Assignment test: init c with some values, then override c with values of a
  avec c = avec(3);
  c[0] = 1;
  c[1] = 2;
  c[2] = 3;

  c = a;
  std::cout << c;

  // Copy test
  avec d(a);
  std::cout << d; 


  return 0;
}
