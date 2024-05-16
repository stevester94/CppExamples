/* Condvar is a signaling primitive; it is not used on its own to guard the critical section
 * It is used with a lock. When the condvar is signaled (or is spuriously woken up) you must then check for a predicated
 * (in order to check if this is a spurious wakeup).
 * 
 * condvar.wait(<lock>), condvar.wait( <lock>, <predicate lamdba> )
 * 
 * The lambda predicate construction (seen in fancyConsumer) is very based
 * 
 * Theory:
 * A mutex (lock) is associated with the cond var because the condition(predicate) needs to change atomically, otherwise
 * we could wait on a condition which has already been made true, and miss the wakeup that will never come
 * 
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

// Need to check this due to spurious wakeup
// volatile is not necessary for concurrency (Though I am still unsure about atomic)
bool is_ready=false;

int payload = -1;

// Synchronization
mutex mtx;
condition_variable condvar;

void producer() {
    cout << "Producer working..." << endl;

    // For the lulz we'll wake up some consumers to emulate a spurious wakeup
    for( int i = 0; i < 10; i++ ) {
        condvar.notify_one();
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "Producer locking..." << endl;
    lock_guard<mutex> guard(mtx); // Scoped guard
    cout << "Producer storing!" << endl;
    is_ready = true;
    payload = 1337;
    condvar.notify_all();
}

void basicConsumer() {
    unique_lock<mutex> lock(mtx);
    
    cout << "/" << flush;
    while( !is_ready ) {
        condvar.wait(lock);
        if( !is_ready)
            cout << "Woke up but not ready" << flush;
    }
    if(payload != 1337) {
        throw runtime_error( "Concurrency fucked up" );
    }
    cout << "." << flush;
}

void fancyConsumer() {
    unique_lock<mutex> lock(mtx);
    
    cout << "/" << flush;
    condvar.wait( lock, [](){ return is_ready; } );
    if(payload != 1337) {
        throw runtime_error( "Concurrency fucked up" );
    }

    cout << "." << flush;
}


int main() {
    
    thread producer_thread( producer );
    

    std::vector<thread> consumers;
    for( int i = 0; i < 100; i++ ) {
        consumers.push_back( thread ( basicConsumer ) );
        consumers.push_back( thread ( fancyConsumer ) );
    }
    
    for( auto& t : consumers ) {
        t.join();
    }
    producer_thread.join();

    return 0;
}