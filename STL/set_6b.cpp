#include<iostream>
#include<set>
using namespace std;
int main(){
    set <int> s ={3,4,5,6,7};
//  auto i = s.rbegin()++;       I can't do this because "REVERSE ITERATOR" can surely be incremeneted, but not directly during initialization
//  auto i1 = s.rbegin()+4;
    auto i=s.rbegin();
    auto i1=s.rbegin();
    ++i;        // 6
    advance(i1, 3);  // i1 now points to the element 4 (we need 3 steps from i)     4
    //s.erase(i.base(),i1.base());     
    auto k = ++s.begin();
    cout<<*k<<endl;
    set <int> :: iterator it = k++;
    cout<<*it<<endl;
    s.erase(s.begin(),it);
    for(auto it :s){
        cout<<it<<" ";
    }
    return 0;
}

