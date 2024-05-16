/*
 * std::unique_ptr
 * - They are quintessential RAII
 * - Can be returned from functions
 * - Only one is ever valid (cannot be copied)
 * - Destruct when they fall out of scope (if they have not been copied)
 * - Must be moved with std::move if doing something in the same scope (black magic C++ rvalue shit)
 * 
 * std::shared_ptr
 * - Reference counted
 * - works as you'd expect
 * 
 * std::weak_ptr
 * - Points to a shared_ptr's pointer
 * - Does not increment the reference count
 * - Used to break reference cycles
 * 
 * std::auto_ptr( Deprecated as of C++2017 )
 */

#include <iostream>
#include <memory>

using std::cout;
using std::endl;


class BigClass {
public:
    BigClass( const std::string& name ) : 
    payload( std::unique_ptr<char>(new char[1024*1024]) ),
    name(name)
    {}


    ~BigClass() {
        cout << "BigClass " << name << " deleting" << endl;
    }
private:
    std::unique_ptr<char> payload;
    const std::string name;
};


struct Holder {
    std::shared_ptr<BigClass> shared;
    std::unique_ptr<BigClass> unique;
};

// Can return unique from functions
std::unique_ptr<BigClass> uniqueFromFunction() {
    std::unique_ptr<BigClass> unique(new BigClass( "uniqueFromFunction" ));
    return unique;
}


int main() {
    // All three of these will deallocate once main returns
    BigClass stack( "Main stack" );
    std::unique_ptr<BigClass> unique(new BigClass( "Main unique" ));

    auto uff = uniqueFromFunction();


    std::shared_ptr<BigClass> sharedHolder(new BigClass( "Shared Holder" ));
    std::unique_ptr<BigClass> uniqueHolder(new BigClass( "Unique Holder" ));

    /*
     * OK so, unique must be moved with std::move, otherwise can't do it
     * When you do this, the original becomes invalidated. 
     * 
     */
    {
        Holder h;
        h.shared = sharedHolder;
        h.unique = std::move(uniqueHolder);
    } // Unique Holder deletes, Shared Holder remains

    if( uniqueHolder == nullptr ) {
        cout << "uniqueHolder is now null" << endl;
    }
    
    if( sharedHolder == nullptr ) {
        cout << "sharedHolder is now null" << endl;
    }






    cout << "Main returning" << endl;
}