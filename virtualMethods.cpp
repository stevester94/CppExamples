/*
Virtual Methods are designed such that if you're iterating through a list of
generic base-class objects, when dereferencing and invoking a method the run-time
will actually check what kind of object it really is (despite typecasting) and will
invoke the actual function.
If a deriving class has not implemented it then it will call the base class's.

Pure Virtual methods achieve the same goal as interfaces as java.
If a class has at least one pure virtual method it is said to be an abstract class
	and can not be instantiated (it is also in fact called an interface)
It is up to the deriving class to implement it, if it does not it is a compiler error

*/


#include <iostream>

using namespace std;

class base {
	virtual void implementMe() = 0;
};

class A : public base {
public:
	//Run time will check what the object actually is
	virtual void whatAmI() {
		cout << "I am an A!\n";
	}

	//This is bound at compile time, will not be checked
	void dumbWhatAmI() {
		cout << "i think I'm an A...\n";
	}

	//The pure virtual method declared by the interface "base" class
	virtual void implementMe() {
		cout << "A has implemented!\n";
	}

	//Test if derived class has implemented this
	virtual void haveYouImplementedMe() {
		cout << "Nope!\n";
	}
};

class B : public A {
public:
	virtual void whatAmI() {
		cout << "I am a B!\n";
	}

	void dumbWhatAmI() {
		cout << "i think I'm a B...\n";
	}

	virtual void implementMe() { cout << "B has implemented!" << endl; }
};



int main() {
	B* b = new B();
	A* a = new A();

	A* castList[2] = {a,b};

	for(int i = 0; i < 2; i++) {
		//Will default to A's implementation since bound at compile time
		castList[i]->dumbWhatAmI(); 

		//Both will say "nope" since B has not implemented
		castList[i]->haveYouImplementedMe();

		//Will report correct value since checked at run time
		castList[i]->whatAmI();

		//Both classes had to implement this
		castList[i]->implementMe();
		
		cout << endl;
	}
/*
Output:
	i think I'm an A...
	Nope!
	I am an A!
	A has implemented!

	i think I'm an A...
	Nope!
	I am a B!
	B has implemented!

*/
	


}