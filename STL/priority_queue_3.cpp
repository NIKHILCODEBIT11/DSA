//      "Priority queue" in which the smallest element is stored at top and largest element at bottom.

#include<iostream>
#include<queue>

using namespace std;

void priority_queue_input(){
    priority_queue <int, vector<int>, greater<int>> pq;     // This will make the priority queue a  min-heap
//  priority_queue <int, vector<int>, greater<int>> pq;     // This will make the priority queue a  max-heap which is the default behaviour of priority queue.

    pq.push(3);
    pq.push(4);
    pq.push(6);
    pq.emplace(7);

    cout<<pq.top();
}

int main(){
    priority_queue_input();
    return 0;
}


/*
The line            priority_queue <int, vector<int>, greater<int>> pq;     means :-

i am defining and initialzing a priority queue "pq", in whose declaration, inside of angular brackets "< >", there are three parts :-

1) int :    It specifies the type of element that will be stored in the "priority queue"

2) vector<int>  :   This is the "UNDERLYING CONTAINER" that stores the element.

3) greater <int>  :     This specifies the "COMPARISION FUNCTION", which is used to determine the PRIORITY of elements.In this case,
                        greater <int> is a built in  "COMPARATOR" in C++ standard library, which makes the "QUEUE BEHAVE AS A MIN-HEAP
                        INSTEAD OF THE DEFAULT BEHAVIOUR OF QUEUE AS MAX-HEAP."
*/