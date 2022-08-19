/*
Nothing crazy, can't iterate.
*/

#include <iostream>
using std::cout;
using std::endl;

#include <queue>

int main()
{
    std::queue<int> queue;

    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);

    cout << "Front is: " << queue.front() << endl;
    cout << "Back is: " << queue.back() << endl;

    while(not queue.empty())
    {
        cout << queue.front() << endl;
        queue.pop();
    }
}