/* const
Nice summary:
The effects of declaring a variable to be const propagate throughout the program. 
Once you have a const object, it cannot be assigned to a non-const reference or use 
functions that are known to be capable of changing the state of the object. This is 
necessary to enforce the const-ness of the object, but it means you need a way to 
state that a function should not make changes to an object. In non-object-oriented 
code, this is as easy as using const references as demonstrated above. 

 In C++, however, there's the issue of classes with methods. If you have a const 
 object, you don't want to call methods that can change the object, so you need a 
 way of letting the compiler know which methods can be safely called. These methods 
 are called "const functions", and are the only functions that can be called on a 
 const object. Note, by the way, that only member methods make sense as const methods.
  Remember that in C++, every method of an object receives an implicit this pointer to 
  the object; const methods effectively receive a const this pointer. 

 Variable declaration:
 */
 	const int constantInteger;
 	const int* pointerToConstantInteger;
 	int* const constantPointerToNonConstData;
 	const int* const constantPointerToConstantData;




// class Base {
// public:
// 	Base() {
// 	}

// 	const int constVar;
// };

// const int Base::constVar = 1337;

#include <iostream>
  using namespace std;

void const examineConstVars(const int var) {
	cout << var << endl;
}

void alterConstVars(const int* vat)



int main() {
	int happyInt = 1337;

	// Will always be three, can't modify
	const int alwaysThree = 3;

	// Declaring a pointer to constant data
	const int* intPointer = &alwaysThree;

	// Can change what the pointer points to though
	intPointer = &happyInt;

	// the pointer itself is const, can change contents but not address
	int* const constantPointer = &happyInt;
	*constantPointer = happyInt;

	// Can't do this, even though the data we point to now isn't const
	// *intPointer = happyInt;

	// Can't declare a non-const pointer to const data
	// int* nonConstPointer = &alwaysThree;

	// Valid, now we can't change either
	const int* const reallySecurePointer = &alwaysThree;


	examineConstVars(*intPointer);
}