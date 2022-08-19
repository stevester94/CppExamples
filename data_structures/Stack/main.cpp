/*
Pretty straight forward.
top() returns a reference to the top element
pop() removes the top element
*/

#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;

#include <stack>

int main()
{
    std::stack<int> s;
    s.push(1337);
    s.push(8080);
    s.push(1338);

    while(not s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}