/* Advanced polymorphism
Upcasting is converting a derived-class reference or pointer to a base-class


*/

#include <iostream>
using namespace std;

class Base {
public:
	Base() {
		type = 'B';
	}

	virtual void report() {
		cout << "I think I am Base" << endl;
		cout << type << endl;
	}

	char type;
};

class Left : public Base {
public:
	Left() {
		type = 'L';
	}

	void report() {
		cout << "I think I am Left" << endl;
		cout << type << endl;
	}

	virtual void leftMethod() {
		cout << "Left method!!" << endl;
	}
};

class Right : public Base {
public:
	Right() {
		type = 'R';
		rightVar = 3;
	}

	void report() {
		cout << "I think I am Right" << endl;
		cout << type << endl;
	}

	virtual void rightMethod() {
		cout << "Right method called" << endl;
	}

	int rightVar;
};

int main() {
	Base b;
	Left l;
	Right r;


	// This cross-caste is valid. However we get weird shit happening
	// It kind of works becuase there are member variables and 
	// functions in the same slots but it leads to undefined behaviour
	Left* actuallyR = ((Left*)&r);

	// If we don't declare report to be virtual then it will use
	// Left's implementation
	actuallyR->report();

	//If we declare leftMethod virtual but not rightMethod we segfault
	//If we declare leftMethod normally then it is called normally
	//   Compiler is binding it so no weird dynamic shit happening
	//If we declare both as dynamic then rightMethod is called!
	//   Fucking weird
	actuallyR->leftMethod();


	//'Valid' Downcasting
	Right* actuallyB = (Right*)&b;


	

	//Does not generate an error but is actually accessing out of object mem
	cout << actuallyB->rightVar << endl;

	// Danger of doing stupid shit is averted by using 
	// Will return 0 since it's really not a valid cast
	actuallyB = dynamic_cast<Right*>(&b);




}