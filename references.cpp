/* References
Though not enforced by the standard, References are basically
 a short hand for pointers.
Also a little safer.
Must be initialized immediately.
Cannot be reassigned.

Can access the object's address by &(Reference).

*/

#include <iostream>
using namespace std;


class Base {
public:
	Base() {
		stuff = 420;
	}

	void report() {
		cout << stuff << endl;
	}

	int stuff;
};

// Takes a reference, will modify the actual value
void writeBase(Base& b) {
	b.stuff = 1337;
}

int main() {
	Base b;
	Base& referencedB = b; //References need to be initialized immediately


	b.report();
	writeBase(b); //b is implicitly converted into a pointer
	b.report();
	referencedB.report();

	// Cannot do this, compiler not that helpful
	writeBase(&b);
}

