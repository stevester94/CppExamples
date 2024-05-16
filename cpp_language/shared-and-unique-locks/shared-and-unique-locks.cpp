/*
 * So backing up a bit.
 * Locks are RAII goodness over a mutex. You can directly use mutexes, but locks make it safer since they're RAII
 * 
 * Now, the point of shared_mutexes is so you can have multiple readers and one writer. If you use a shared_lock, it calls lock_shared() on the mutex
 * - multiple threads can have lock_shared() at once
 * But if you use a lock_guard or unique_lock, it'll call lock() on the shared_mutex
 * - Only one thread can be lock() at a time
 * 
 * The three are very similar
 * - lock_guard
 *   - lock() on construction, unlock on destruction, does nothing else
 * - shared_lock
 *   - lock() on construction (also suports deferred lock), unlock on destruction
 *   - supports manual lock and unlock
 * - unique_lock
 *   - lock() on construction (also suports deferred lock), unlock on destruction
 *   - supports manual lock and unlock
 *   - Supports timed lock attempts
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <functional>   // std::bind
#include <atomic>

using namespace std;

volatile int payload = -1;

// Synchronization
shared_mutex mtx;


void producer() {
    cout << "Producer locking mtx..." << endl;
    lock_guard<shared_mutex> guard(mtx);
    // unique_lock<shared_mutex> lock(mtx, std::defer_lock ); // You can do this (if you even wanted to)
    cout << "Producer working" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    payload = 1337;

    cout << "data produced" << endl;
}

void reader(int index) {
    while(true) {
        cout << "/" << flush;
        unique_lock<shared_mutex> sharedLock(mtx); // Scoped guard
        cout << "." << flush;
        sharedLock.unlock();

        this_thread::sleep_for( chrono::milliseconds(500) );
        if( payload == 1337 )
            break;
    }
}


int main() {

    vector<thread> consumers;
    
    for( int i = 0; i < 1000 ; i++ ){
        consumers.push_back( thread( bind(reader, i) ) );
    }

    this_thread::sleep_for(chrono::seconds(2));
    thread producer_thread( producer );

    for( auto it = consumers.begin() ; it != consumers.end() ; it++  ){
        it->join();
    }
    producer_thread.join();

    return 0;
}