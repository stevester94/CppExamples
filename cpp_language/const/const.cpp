/* const
The const syntax is kinda weird tbh, it sorta applies to the "thing" to the left,
    and if nothing is to the left it applies to the right.

Examples:
    Applies to the int
    const int* pointer_to_constant_integer = &_;

    Applies to the pointer
    int* const constant_pointer_to_nonconst_data = nullptr;

    Applies to both
    const int* const constant_pointer_to_constant_data = nullptr;

 */

#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;




// Functions do not need to be declared const, it is sufficient to 
// appropriately declare the parameters const
void examine_const_var(const int* var) {
    cout << *var << endl;
}



// This would not compile, the compiler is smart enough to know
// you are modifying a const parameter
void alterConstVars(const int* vat)
{
#if ERROR
    *vat = 0;
#endif
}

/*
Constness on classes is a little silly. The method itself must be declared const.
When a method is declared const, the implicit "this" pointer changes:
Normally "this" is T* const, IE the object is mutable but the pointer is not
"this" changes to const T* const, meaning the underlying object cannot be modified

Long story short, the declaration is "<method> const", not "const <method>"
*/

class dummy
{
public:
    dummy() : data_(1337)
    {}

    void modify_data() { data_++; }
    void view_data() const { cout << data_ << endl; }
    void const incorrectly_const()  { cout << data_ << endl; }
private:
    int data_;
};




int main() {
    // This will always be 0
    const int constant_integer = 0;

    // The pointer can change, but the int is a constant
    const int _ = 1337;
    const int* pointer_to_constant_integer = &_;

    // The pointer cannot change but the data can
    int* const constant_pointer_to_nonconst_data = nullptr;

    // Neither the pointer nor data can change
    const int* const constant_pointer_to_constant_data = nullptr;

    examine_const_var(pointer_to_constant_integer);

    ANNOUNCE_SECTION("Object Constness");
    
    const dummy d;
#if ERROR
    d.modify_data();
    d.incorrectly_const();
#endif

    d.view_data();
}