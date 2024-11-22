#include <iostream>
#include <queue>
using namespace std;

// PRIORITY QUEUE
// allows new elements to enter a system. stores elements of an array in sorted order (largest value on top) IF it is a max-heap
// in general, largest element is also on top for all queues no matter if the array is sorted. queue will sort for you
// can push and pop elements
int main()
{
    int arr[6] = { 10, 2, 4, 8, 6, 9 };

    // defining priority queue
    priority_queue<int> pq;

    // printing array. normal order of values is kept
    cout << "Array: ";
    for (auto i : arr) {
        cout << i << ' ';
    }
    cout << endl;
    // pushing array sequentially one by one
    for (int i = 0; i < 6; i++) {
        pq.push(arr[i]); // inserts value
    }

    // printing priority queue
    cout << "Priority Queue: "; // prints queue in desceneing order, largest value first
    while (!pq.empty()) {
        cout << pq.top() << ' '; // prints top value
        pq.pop(); // removes value
    }

    return 0;
}