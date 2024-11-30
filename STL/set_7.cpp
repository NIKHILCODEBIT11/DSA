#include<iostream>
#include<set>

using namespace std;

int main(){
    set <int> s = {3,4,5,6};
    set <int> :: iterator it = s.begin();
    while(it!=s.end()){
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;

    auto e1 = s.rbegin();
    auto e2 = s.rend();
    e2--;
    cout<<"The value of *e2 is "<<*e2<<endl;
    e2--;
    cout<<"The value of *e2 is "<<*e2<<endl;

    s.erase(e2.base(),e1.base());       // (5,6]    as by using base(), it points to the element just after the iterator with which base() is used IN THE NORMAL OR REGULAR SET NOT IN REVERSE SET.
    set <int> :: iterator ite = s.begin();
    while(ite!=s.end()){
        cout<<*ite<<" ";
        ite++;
    }
    return 0;
}