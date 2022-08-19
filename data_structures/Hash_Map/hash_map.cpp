/*
maps are ordered, with insert and access being log(n)
unordered_maps have insert and access in O(1)

finding is much saner than previously believed, but [<key>] is still dangerous
*/

#include <iostream>
using std::cout;
using std::endl;

#include <helpers.hpp>

#include<map>
#include<unordered_map>



int main()
{
    ANNOUNCE_SECTION("Basic accessing");
    std::map<std::string, int> m;

    // Setting is as easy as this
    m["one"] = 1;
    m["two"] = 2;

    // getting is as easy as this
    cout << "map[one]: " << m["one"] << endl;

    ANNOUNCE_SECTION("Handling Non-Existent Keys");
    // Getting a non_existent key via brackets actually creates a value for that key and returns it!
    // That's some dangerous behaviour!
    cout << "map[non_existent]: " << m["non_existent"] << endl;

    // A much safer alternative is to use .at()
    // at() will raise an exception if the key does not exist
    try
    {
        auto& val = m.at("very_not_existent");
        cout << "map[very_not_existent]" << val << endl;
    }
    catch(std::out_of_range& e)
    {
        // The exception message isn't particularly good
        cout << "Exception was caught: " << e.what() << endl;
    }

    ANNOUNCE_SECTION("Checking if key exists");
    // A little wack, returns count of keys matching
    // Since the map enforces unique keys, this will only ever be 0 or 1
    if(m.count("one") == 1) cout << "Key 'one' exists" << endl;
    if(m.count("very_non_existent") == 0) cout << "Key 'very_non_existent' does not exist" << endl;

    ANNOUNCE_SECTION("Deleting a key");
    // A little wack, returns the number of keys deleted
    // Since the map enforces unique keys, this will only ever be 0 or 1
    if(m.erase("non_existent") == 1) cout << "'non_existent was erased'" << endl;
    if(m.erase("non_existent") == 0) cout << "'non_existent was already erased'" << endl;


    ANNOUNCE_SECTION("Finding is misunderstood");
    // you can iterate through the map, meaning find actually does have a use
    // The return is an iterator over std::pairs, <key, value>
    // If not found, return is end()
    auto it = m.find("one");
    if(it != m.end())
    {
        cout << "Element 'one' was found, value is: " << it->second << endl;
    }

    auto it2 = m.find("very_not_existent");
    if(it2 != m.end())
    {
        cout << "Element "<< it2->first << " was found, value is: " << it2->second << endl;
    }
    if(it2 == m.end())
    {
        cout << "Element 'very_not_existent' was not found" << endl;
    }
}