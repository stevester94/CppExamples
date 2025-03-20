/*
Copy constructors are straight forward. They'll be used when you assign an object to another object, or when a
function takes a vanilla object (not a ref or whatever)



Really move constructors
*/
#include <helpers.hpp>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


class Movable {
public:
    Movable() : val(1337) { std::cout << "Default constructor\n"; }
    Movable(int arg) : val(arg) { std::cout << "Default constructor with arg\n"; }
    Movable(const Movable&) { std::cout << "Copy constructor\n"; }
    Movable(Movable&&) { std::cout << "Move constructor\n"; }
    ~Movable() { std::cout << "Destructor\n"; }

    int val;
private:
    char* payload;
};

class NotMovable {
    public:
        NotMovable() : val(1337) { std::cout << "Default constructor\n"; }
        NotMovable(int arg) : val(arg) { std::cout << "Default constructor with arg\n"; }
        NotMovable(const NotMovable&) { std::cout << "Copy constructor\n"; }
        NotMovable(NotMovable&&) = delete;
        ~NotMovable() { std::cout << "Destructor\n"; }
    
        int val;
    private:
        char* payload;
    };

Movable make_a_movable() {
    Movable M(68);
    return M;
}

Movable make_a_complicated_movable() {
    Movable M(68);
    if(M.val == 68) {
        M.val += 10;
    } else {
        M.val -= 10;
    }
    return M;
}

void take_an_r_value( Movable&& m ) {
    cout << m.val << endl;
}

void take_an_r_value( NotMovable&& m ) {
    cout << m.val << endl;
}

void take_a_movable( Movable m ) {
    cout << m.val << endl;
}

Movable modify_a_movable( Movable m ) {
    cout << "Doing a thing" << endl;
    m.val++;
    return m;
}

NotMovable modify_a_not_movable( NotMovable m ) {
    cout << "Doing a thing" << endl;
    m.val++;
    return m;
}


int main()
{
BEGIN_SECTION(false)
    Movable m_1; // Default constructor
    Movable m_2(42); // Default constructor with arg

    Movable m_3 = Movable(); // Default constructor, no extra object instantiation
    Movable m_4 = Movable(43); // Default constructor with arg, no extra object instantiation
END_SECTION

BEGIN_SECTION(false)
    Movable m_1; // default constructor
    Movable m_2 = m_1; // copy constructor
END_SECTION

BEGIN_SECTION(false)
    make_a_complicated_movable(); // default constructor with arg, then destructor
    make_a_movable(); // default constructor with arg, then destructor
END_SECTION

BEGIN_SECTION(false)
    Movable m_1 = make_a_movable(); // Very interesting. The compiler is optimizing and just caling default with arg
    Movable m_2 = make_a_complicated_movable(); // Same here
    // destructors called when out of scope. There is no extra copy/move being done
END_SECTION

BEGIN_SECTION(false)
    // This is calling default constructor, and then the move constructor
    // Fucking note that two destructors are being called here (obviously!)
    vector<Movable> v;
    v.push_back(Movable(42));
END_SECTION

BEGIN_SECTION(false)
    vector<NotMovable> v;

    // Starts to get a little interesting here. You cannot call push back like this if your class does not implement a move constructor
#if ERROR
    v.push_back(NotMovable(42));
#endif

    // This if fine. Calls the default constructor and copy constructor, then two destructors
    NotMovable n;
    v.push_back(n);
END_SECTION


BEGIN_SECTION(false)
    // Can't do this, m is an l value
#if ERROR
    Movable m;
    take_an_r_value( m );
#endif
END_SECTION

BEGIN_SECTION(false)
    // Can do this though! 
    take_an_r_value( Movable(13) ); // Default constructor, then destructor
    take_an_r_value( NotMovable(13) ); // Default constructor, then destructor

END_SECTION

BEGIN_SECTION(false)
    // Ah ok here we go. This avoids the copy we would have done if we didn't use std::move
    Movable m_1; // Default constructor
    Movable m_2 = std::move(m_1); // move constructor
    // 2 destructors
END_SECTION

BEGIN_SECTION(false)
    Movable m_1;

    // This calls the copy constructor
    take_a_movable( m_1 );

    // Wack! This calls the move constructor!
    take_a_movable( std::move(m_1) );
END_SECTION

BEGIN_SECTION(false)
    // default, copy, move!
    // This is interesting, because modify_a_movable is not explicitly returning an r value. 
    Movable m_1; 
    Movable m_2 = modify_a_movable( m_1 );
END_SECTION

BEGIN_SECTION(true)
    // default, copy, copy!
    // Interestingly enough, vscode is telling me this is an error because the && constructor is deleted
    NotMovable m_1; 
    NotMovable m_2 = modify_a_not_movable( m_1 );
END_SECTION
}