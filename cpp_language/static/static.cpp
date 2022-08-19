/* Static
Static variables within a function are kept the same across all function calls
Static variables within a class are shared across all instantiations of it.
	Have a very weird initialization process, where you explicitly set the value outside of the class
Static functions are called from the class not an object
*/

#include <iostream>
using namespace std;

void staticCallCounter() {
	static int numCalls = 0; //Preserved across calls

	cout << numCalls << endl;

	numCalls++;
}

class StaticClass {
public:
	StaticClass() {
		staticVar++;

	}

	void report() {
		cout << staticVar << endl;
	}

	static void resetStaticVar() {
		staticVar = 0;
	}

#if ERROR
	static int staticVar = 10; //This must be initialized outside of the class!
#endif
	static int staticVar;
};

int StaticClass::staticVar = 10; //This is the proper way to initialize

int main() {

	cout << "staticCallCounter" << endl;
	for(int i = 0; i < 10; i++) {
		staticCallCounter();
	}

	StaticClass::resetStaticVar(); // How you access static functions
	
	//This becomes valid once we initialize outside of class. 
	StaticClass::staticVar = 1337; 
	cout << endl << "staticClass stuff" << endl;
	for(int i = 0; i < 10; i++) {
		StaticClass sc;
		sc.report();
	}


}