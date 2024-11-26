#include<iostream>
#include<list>
using namespace std;

//  In list, i can't use    ls.at(i) or ls[i]   to access the elements.

void explain_list(){
    list <int> ls={3,4};    // Defining a list
    list <int> ls_;

// push_back() :-

    cout<<"Pushing {5} to back of list :-"<<endl;
    ls.push_back(5);
    for(auto it : ls){
        cout<<it<<" ";
    }
    cout<<endl;

// emplace_back() :-

    cout<<"Emplacing {6} to back of list :-"<<endl;
    ls.emplace_back(6);
    for(auto it =ls.begin();it!=ls.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

// push_front() :-

    cout<<"Pushing {7} to front of list :-"<<endl;
    ls.push_front(7);
    for(auto i : ls){
        cout<<i<<" ";
    }
    cout<<endl;

// emplace_front() :-

    cout<<"Emplacing {9} to front of list :-"<<endl;
    ls.emplace_front(9);
    for(auto i = ls.begin();i!=ls.end();i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}

int main(){
    explain_list();
    return 0;
}

// Rest functions are same as vectors    like begin(), end(), rbegin(), rend(), clear(), insert(), size(), swap()