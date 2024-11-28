#include<iostream>
#include<set>

using namespace std;

void set_explain(){
    set <int> s = {3,7,4,6};
    s.insert(22);
    s.insert(23);
    s.emplace(19);

    cout<<"Using find function :-";
    auto it=s.find(3);     // "find(a)" return the memory address of that location where that value "a" is present."
//  cout<<*it;      If i call the function till here only then i am getting garbage value (7), to avoid this i will need if-else stated beloe :-

    if(it==s.end()){
        cout<<"Element not found";
    }
    else{
        cout<<*it;
    }
}

int main(){
    set_explain();
    return 0;
}