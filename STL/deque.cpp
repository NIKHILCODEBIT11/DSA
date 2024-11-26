#include<iostream>
#include<deque>

//  CLEAR DOUBT :-      "DEQUEUE"  IS DIFFERENT FROM  "QUEUE"

using namespace std;

void explain_deque(){
    deque <int> dq={3,4};
    deque <char> dq_;

//  push_back() :-

    cout<<"Pusing {5} to the back of deque :-"<<endl;
    dq.push_back(5);
    for(auto it = dq.begin();it!=dq.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

// emplace_back() :-

    cout<<"Emplacing {6} to the back of the deque :-"<<endl;
    dq.emplace_back(6);
    deque <int> :: iterator it = dq.begin();
    for(it;it!=dq.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

// push_front() :-

    cout<<"Pushing {7} to front of the deque :-"<<endl;
    dq.push_front(7);
    for(auto it : dq){
        cout<<it<<" ";
    }
    cout<<endl;

// emplace_front() :-

    cout<<"Emplacinf {9} to front of the deque :-"<<endl;
    dq.emplace_front(9);
    for(int i=0;i<dq.size();i++){
        cout<<dq.at(i)<<" ";
    }
    cout<<endl;

// pop_back() :-

    cout<<"Popping or removing element from back from deque :-"<<endl;
    dq.pop_back();
    for(int i=0;i<dq.size();i++){
        cout<<dq[i]<<" ";
    }
    cout<<endl;

// pop_front() :-

    cout<<"Popping or removing element from front from deque :-"<<endl;
    dq.pop_front();
    for(auto it :dq){
        cout<<it<<" ";
    }
    cout<<endl;
}

int main(){
    explain_deque();
    return 0;
}

// Rest all functions are same as vector    begin(), end(), rbegin(), rend(), clear(), insert(), size(), swap()