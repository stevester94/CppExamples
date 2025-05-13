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


/*
The purpose of a condvar is two-fold:
1. avoid a busy-waiting mutex loop via OS support of waking 1/all threads
2. Make it harder to fuck up concurrency

The condvar revolves around a predicate and a lock.
The predicate must be acted on atomically (Both read and set). 

Here's a scenario which would break if we don't set the predicate atomically:
-----------------------------------------------------------------------
Producer                                Consumer
<sleeping>                              Locks the lock
                                        Checks predicate, it's false
                                        <Preempted>
<wakes and sets predicate to true>
<notify_all on condvar>
                                        Waits on the condvar... forever
-----------------------------------------------------------------------
In this case, the notify from the producer is lost to the ether, and consumer blocks forever


This is what makes condvars good for purpose #2: You have to have the lock locked in order to call wait()
When you call wait(), the condvar unlocks the lock, and then blocks until notified or spuriously woken up
- When wait returns, you are automatically, and atomically, holding the lock
- notify() does not require you to be holding the lock, and in fact you shouldn't because that would make the freshly notified 
  condvar have to wait for the notifier to release



Note how if you don't mind busy loops, and you don't need notify-one, then you can get away with just a busy mutex
*/

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

// Need to check this due to spurious wakeup
// volatile is not necessary for concurrency (Though I am still unsure about atomic)
bool predicate=false;

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
    predicate = true;
    payload = 1337;
    condvar.notify_all(); // You gotta notify all of them
}

void basicConsumer() {
    unique_lock<mutex> lock(mtx); // unique_lock locks automatically on construction
    
    while( !predicate ) { // We own the lock, so we can safely check the predicate. We loop in case of spurious wake-up
        condvar.wait(lock); // We wait, releasing the lock

        // We own the lock after wait() returns

        if( !predicate) // This is just for illustration
            cout << "basicConsumer woke up but not ready" << endl;
    }
    if(payload != 1337) {
        throw runtime_error( "Concurrency fucked up" );
    }
    cout << "+" << flush;
}

void fancyConsumer() {
    unique_lock<mutex> lock(mtx);
    
    condvar.wait( lock, [](){ return predicate; } );

    /* The above is equivalent to 

    unique_lock<mutex> lock(mtx);
    while(!predicate())
        condvar.wait(lock);

    */

    if(payload != 1337) {
        throw runtime_error( "Concurrency fucked up" );
    }

    cout << "+" << flush;
}

void busyConsumer() {
    unique_lock<mutex> lock(mtx, std::defer_lock);
    
    while(1) {
        lock.lock();
        if( predicate ) {
            cout << "busyConsumer done" << endl;
            lock.unlock();
            break;
        }
        cout << "busyConsumer still spinning" << endl;
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
}

int main() {
    thread producer_thread( producer );
    
    std::vector<thread> consumers;
    for( int i = 0; i < 100; i++ ) {
        consumers.push_back( thread ( basicConsumer ) );
        consumers.push_back( thread ( fancyConsumer ) );
    }
    consumers.push_back( thread(busyConsumer) );
    
    for( auto& t : consumers ) {
        t.join();
    }
    producer_thread.join();

    return 0;
}