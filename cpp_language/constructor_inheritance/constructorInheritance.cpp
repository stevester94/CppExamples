/* Constructor inheritance & private inheritance quirks
The base class's constsructor is called before the derived class.
The base class's constructor can access private fields (makes sense), but
the derived class cannot (as seen in basicInheritance)

the base class's members still exists even though it's private
Derived will be able to call report which is pubicly inherited
report however is still able to access private members of the Base
class, it is still held in memory, just not DIRECTLY accessible to the derived

*/

#include <iostream>
using namespace std;

class Base {
public:
	Base() {
		cout << "base Constructor called\n";
		privateStuff = 1337;
		cout << privateStuff << endl;
	}

	void report() {
		cout << privateStuff << endl;
	}

private:
	int privateStuff;
};

class Derived : public Base {
public:
	Derived() {
		cout << "Derived Constructor called\n";

		//Can't do this, its private!
		// cout << privateStuff << endl;
	}
};


int main() {
	Base b;
	Derived d;

	d.report();
/* Output:
	base Constructor called
	1337
	base Constructor called
	1337
	Derived Constructor called
*/

}