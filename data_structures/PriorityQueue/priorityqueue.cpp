/*
 * Heap is garbage, use priority_queue
 * - It offers all the conveniences you'd expect
 */
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;

#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>



void priorityQueue_max() {
    ANNOUNCE_SECTION( "Priority Queue (Max Priority)" );
    /*
    The max value will always be at the top.
    */

    std::priority_queue<int> pq;
    std::vector<int> ints = {10, 3, 1, 5, 6 };

    for( auto i : ints ) {
        pq.push( i );
    }

    std::cout << "{ ";
    while( ! pq.empty() ) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "}" << std::endl;
}

void priorityQueue_min() {
    ANNOUNCE_SECTION( "Priority Queue (Min Priority)" );
    /*
    The min value will always be at the top.
    */

    std::vector<int> ints = {10, 3, 1, 5, 6 };
    // Fancy alternate way to construct a pri-q
    std::priority_queue pq( ints.begin(), ints.end(), std::greater<int>() );

    std::cout << "{ ";
    while( ! pq.empty() ) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "}" << std::endl;
}

void heap() {
    ANNOUNCE_SECTION( "Heap" );
    std::vector<int> ints = {10, 3, 1, 5, 6 };

    std::cout << vectorToStr( ints ) << std::endl;

    std::make_heap( ints.begin(), ints.end() );

    std::cout << vectorToStr( ints ) << std::endl;
}

int main() {
    heap();
    priorityQueue_max();
    priorityQueue_min();
}