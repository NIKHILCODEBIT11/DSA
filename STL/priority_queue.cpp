#include<iostream>
#include<queue>

using namespace std;

//      Priority queue as the name suggests is a queue where "PRIORITY IS GIVEN TO HIGHER VALUES" ----> HIGHER VALUE STAYS AT TOP OF "PRIORITY_QUEUE" AND LOWER VALUE STAYS AT BOTTOM OF "PRIORITY_QUEUE".

void print_pq(priority_queue <int> &);

void explain_priority_queue(){
    priority_queue <int> q2={3,4};  //  ---->   I can use "PRIORITY QUEUE" by including the header file     #include<queue>,    even 
    
    // The above initialization means give 3 instances of 4 , as in priority queue it supports "vector".

    priority_queue <int> pq;
    pq.push(4);
    pq.push(2);
    pq.push(7);
    pq.emplace(6);

    cout<<"The top element is "<<pq.top()<<endl;
    pq.pop();
    cout<<"After popping once, the top element is "<<pq.top()<<endl;

    cout<<"Printing elements of priority queue from bottom to top :-"<<endl;
    print_pq(pq);
}

void print_pq(priority_queue <int> &q){
    if(q.empty()){
        return;
    }
    auto it = q.top();
    q.pop();
    print_pq(q);
    cout<<it<<" ";
}

int main(){
    explain_priority_queue();
    return 0;
}

// Inside of "priority queue" not a "linear" data structure is maintained, rather a "Tree" data structure is maintained.