#include<iostream>
#include<queue>

using namespace std;

void print_priority_queue(priority_queue <int> &);

int main(){
    priority_queue <int> q ;
    q.push(3);
    q.emplace(4);
    q.push(6);
    q.emplace(7);

    cout<<"Printing elements of priority queue from top to bottom :-"<<endl;
    print_priority_queue(q);
    return 0;
}

void print_priority_queue(priority_queue <int> &q){
    while(!q.empty()){
        auto it =q.top();
        cout<<it<<" ";
        q.pop();
    }
}