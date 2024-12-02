//      It stores "KEY-VALUE" pair in which elements are "UNIQUE" but are "UN-SORTED", and store those pair in a "hash table".

//      Any operation in "MAP", it takes time - complexity of """"""log(N)"""""""" and that of "UNORDERED-MAP" is """""" O(1) """""""" mostly, but in worst case it will be """""" O(N)""""""

#include<iostream>
#include<unordered_map>

using namespace std;

int main(){
    unordered_map <int,int> u = {{2,2},{1,2},{3,3}};
    u.insert({2,4});
    u.emplace(4,4);
    cout<<"Printing the unordered map :-"<<endl;
    for(auto it : u){
        cout<<it.first<<","<<it.second<<endl;
    }
    return 0;
}

/*
I am getting output as :-

Printing the unordered map :-
4,4
3,3
2,2
1,2

The above order may change if i run the program again, as the order of elements is not sorted
*/