/* Friend Classes and Functions
By declaring a Class or function as a friend of a class it is given
complete access to all data members and methods.

Friend is designed to be practical, it can often be necessary in large code
bases. Idealy however you probably shouldn't need to be using this. Can lead
to tighter coupling (become more closely connected, you're directly using
elements of a class that the class should be dealing with itself).
<Test Comment>
*/

#include <iostream>
using namespace std;

class Base {
public:
  Base() { privateStuff = 420; }

  // Specify that this function is a friend of Base
  friend void friendlyFunction(Base b);

  // Specify that this class is a friend of Base
  friend class FriendlyClass;

private:
  int privateStuff;
};

// Since it is a friend, any methods in FriendlyClass has complete access to
// all members of Base
class FriendlyClass {
public:
  FriendlyClass(Base b) { cout << b.privateStuff << endl; }
};

// If this weren't a friend function we'd get a compiler error
void friendlyFunction(Base b) { cout << b.privateStuff << endl; }

int main() {
  Base b;
  FriendlyClass f(b);

  friendlyFunction(b);
}