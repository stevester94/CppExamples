/*
This is related to the issue seen in string and stack, where a sigabrt is raised if you access the front/top when the container is empty

IDK man, accessing front and back is undefined behavior. I couldn't get this to crash w/ c++ 20 nor the default
*/
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main()
{
    ANNOUNCE_SECTION( "None of these crash" );
    string A;

    A.front();

    string B = "lel" + A.front();

    char C = A.front();

    if( A.front() == '\n') {
        std::cout << C << std::endl;
    }

    string die = "";
    if( die.front() == '\n') {
        std::cout << "Never gonna get here" << std::endl;
    }
    

    ANNOUNCE_SECTION( "None of these crash" );
    string Z = "";

    if( Z.back() == '\n' ) {
        std::cout << "God" << std::endl;
    }
    


    return 0;
}