#include<iostream>
#include<queue>

using namespace std;

void output(priority_queue <int> &);

void input(){
    priority_queue <int> pq={2,9};
    pq.push(6);
    pq.emplace(7);
    output(pq);
}

void output(priority_queue <int> &q){
    if(q.empty()){
        return;
    }
    auto it = q.top();
    q.pop();
    output(q);
    cout<<it<<" ";
}

int main(){
    input();
    return 0;
}