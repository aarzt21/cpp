/*
This is my informatics homework: 

The objective is to implement your own queue class with integer values as a dynamic data structure.

A queue provides the two basic operations: enqueue and dequeue.
The operation enqueue adds a new element to the back of the queue. The operation dequeue removes the first element from the queue:


The most common way to implement a queue is by using a linked list. In order to
to enqueue and dequeue we need to be able to access the first and last element of the list.

*/
#include <iostream>
#include <cassert>





struct Node {
    Node(const int _value, Node* _next) : value(_value), next(_next) { }
    const int value;
    Node* next;
};

void print_node_reverse(std::ostream& os, Node* n){
  if (n != nullptr){
    //recursion
    print_node_reverse(os, n->next);
    os << n->value << ' ';
  }
}

void print_node(std::ostream& os, Node* n){
  if (n != nullptr){
    //recursion
    os << ' ' << n->value;
    print_node_reverse(os, n->next);
  }
}


class Queue {
public:
    // PRE:  -
    // POST: Valid and empty queue.
    Queue(){
      this->first = nullptr;
      this->last = nullptr;
    };

    // PRE:  Valid queue.
    // POST: Valid queue with new node having value i added at end of queue.
    void enqueue(int value){
      is_valid();

      Node* node = new Node(value, nullptr);
      if (this->first == nullptr){
        this->first = node;
        this->last = node;
      } else{
        this->last->next = node;
        this->last = node;
      }

    }

    // PRE:  Valid and non-empty queue.
    // POST: Removes first node from queue.
    //       Returns content of first node.
    int dequeue(){
      is_valid();
      assert(!is_empty());

      Node* node = this->first;
      this->first = this->first->next;

      if (this->first == nullptr){
        this->last = nullptr;
      }

      int val = node->value;
      return val;
    }

    // PRE:  Valid queue.
    // POST: Returns true if queue is empty, false otherwise.
    bool is_empty() const {
      is_valid();
      return this->first == nullptr;
    }

    // PRE:  Valid queue.
    // POST: Outputs queue content to os in sequence from first to last.
    void print(std::ostream& os) const {
      os << "[";
      if (this->first != nullptr){
        os << first->value;
        print_node(os, this->first->next);
      }
      os << "]";
    }


    // PRE: Valid queue
    // POST: Outputs queue content to os in reverse order, from last to first.
    void print_reverse(std::ostream& os) const {
      os << "[";
      if (this->first != nullptr){
        print_node_reverse(os, this->first->next);
        os << first->value;
      }
      os << "]";
    }

private:

    // Class invariant: first == nullptr iff last == nullptr
    Node* first; // pointer to first element of queue or nullptr is queue is empty.
    Node* last;  // pointer to last element of queue or nullptr if queue is empty.

    // PRE: -
    // POST: Ensures class invariant. A class invariant is an assertion that captures the properties and relationships,
    // which remain stable throughout the life-time of instances of the class.
    void is_valid() const {
      assert((this->first == nullptr) == (this->last == nullptr));
    }
};




// The following main function implements the testing harness.
// Note: We use *(ref). as the operator -> is not introduced in the lecture.
int main() {
    Queue q;

    // parse and process the test data until the end marker occurs.
    // The format of the test data is:
    // <function> <parameter>
    // where <parameter> is optional and specific to the function.
    while (std::cin.good()) {

        // get <function>, exit if end marker occurs
        std::string function;
        std::cin >> function;
        if (function == "end") {
            break;
        }

        if (function == "dequeue") {
            std::cout << q.dequeue() << "\n";

        } else if (function == "enqueue") {
            int value; // parameter "value"
            std::cin >> value;
            q.enqueue(value);

        } else if (function == "is_empty") {
            std::cout << q.is_empty() << "\n";

        } else if (function == "print_reverse") {
            q.print_reverse(std::cout);
            std::cout << "\n";

        } else {
            std::cout << "unknown function: " << function << "\n";
            break;
        }

    }
    return 0;
}
