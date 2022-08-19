/*

*/
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;

#include <vector>

int main() {
    std::vector<int> v {1,2}; // Fancy init with 2 elements

    auto beg = v.begin();
    auto end = v.end();

    cout << "Begin is: " << *beg << endl;

    // This does not crash, but it is not valid.
    // End points to the theoretical element that exists
    // past the last element
    cout << "End is: " << *end << endl;

    // Despite the docs stating that distance returns
    // " The number of elements between first and last."
    // this line is actually equivalent to v.size()
    cout << "Distance between begin and end: " << 
    std::distance(v.begin(), v.end()) << endl;

    // Really it's more accurate to say, how many elements are
    // in the range of [first, second)
    std::cout << "Distance between first and second: "
    << std::distance(v.begin(), v.begin()+1) << endl;

    // This is 0, so it's consistent
    std::cout << "Distance between first and first: "
    << std::distance(v.begin(), v.begin()) << endl;
}