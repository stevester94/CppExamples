/*
 * - Store lambas using std::function< {returnType}({param types...}) >
 * - Define lambdas using [<captured vars>](<params>) { <body> };
 * - Captures are complicated
 *   - You can capture by reference or capture by value.
 *   - Care must be taken for capture by reference, since your target can fall out of scope
 */
#include <iostream>
#include <vector>
#include <functional>
#include <helpers.hpp>
#include <algorithm> // for_each

std::function<void()> captureMe();

int main( int argc, char** argv ) {

    ANNOUNCE_SECTION( "Basic Usage" );
    std::function<int(int,int)> lam = [](int a, int b) {
        return a+b;
    };

    std::cout << lam( 1336,1 ) << std::endl;



    ANNOUNCE_SECTION( "Basic algorithm::for_each" );
    std::vector<int> vect = {3,5,1};

    std::function<void(int)> prettyLambda = [](int a ) { std::cout << "is " << a << std::endl; };

    std::for_each( vect.begin(), vect.end(), prettyLambda );

    // Obviously they're more based when inline
    std::for_each( vect.begin(), vect.end()-1, [](int a) { std::cout << a << ",";} );
    std::cout << *(vect.end()-1) << std::endl;


    ANNOUNCE_SECTION( "Lambda capturing" );
    std::cout << "This gives garbage because we are capturing a stack variable by reference which is folling out of scope" << std::endl;
    captureMe()();
    
}

std::function<void()> captureMe() {
    int aStackVariable = 3;
    std::function<void(void)> captureLambda = [&aStackVariable]() { std::cout << "aStackVariable is " << aStackVariable << std::endl; };
    return captureLambda;
}