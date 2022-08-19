/* vector, string, queue, map, sorting */

#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <stack>
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector
#include <queue>
#include <map>

using namespace std;

// Some nice inheritance
// Operators are not inherited by default
class myString : public string {
public:
  // Call super class constructor
  myString() : string(&current) {
    current = current - 1;
    instantiationCount++;
    this->report();
  }

  myString(const char* inChar) : string(inChar) {}
  // myString(const char inChar) : string(inChar) {}

  void report() {
    cout << *this << endl;
  }

  bool operator<(const myString & rhs) const {
    return (string)*this < (string) rhs;
  }

  string operator=(const myString & rhs) const {
    return (string)*this = (string)rhs;
  }

  bool operator==(const myString & rhs) const {
    return (string)*this == (string)rhs;
  }

  static char current;
  static int instantiationCount;
  static map* allocatedMyStrs;
};

char myString::current = 'z';
int myString::instantiationCount = 0;
int sizeAr = 10;


void stackTest() {
  cout << "QUEUE" << endl;

  myString* strAr[sizeAr];
  stack<myString*> myStack;

  for(int i = 0; i < sizeAr; i++) {
    strAr[i] = new myString;
    myStack.push(strAr[i]);
  }
}

void priority_queueTest() {
  cout << "priority_queue" << endl;

  priority_queue<myString*> priQueue;
  myString* strAr[sizeAr];

  for(int i = 0; i < sizeAr; i++) {
    priQueue.push(new myString);
  }

  cout << "heap!" << endl;

  while(!priQueue.empty()) {
    auto current = priQueue.top();
    priQueue.pop();

    current->report();
  }
}




int main() {



}
