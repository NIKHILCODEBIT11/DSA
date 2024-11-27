#include<iostream>
#include<queue>

using namespace std;

void print_queue(queue <int> &q){
    while(!q.empty()){
        cout<<q.front()<<" ";
        q.pop();
    }
}

int main(){
    queue <int> q;
    q.push(3);
    q.push(4);
    q.emplace(6);
    q.emplace(7);
    cout<<"Printing elements of queue in front order :-"<<endl;
    print_queue(q);
    return 0;
}

//      size(), swap(), empty() is same as that in stack.

// The time complexity is   O(1).