#include<iostream>
#include<set>
using namespace std;
int main(){
    set <int> s ={3,4,5,6,7};
    s.erase(s.begin(),--s.end());       //  Follows the syntax   [3,7)
    for(auto it :s){
        cout<<it<<" ";
    }
    return 0;
}