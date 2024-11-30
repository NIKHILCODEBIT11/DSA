#include<iostream>
#include<unordered_set>     // Unordered set are just like set which stores "UNIQUE" elements, but "NOT IN SORTED" manner 

//  Apart from lower_bound() and upper_bound() all functions are same as that of set

using namespace std;

void output(unordered_set <int> &a){
    for(auto it : a){
        cout<<it<<" ";
    }
    cout<<"\n";
}

void input(){
    unordered_set <int> u = {3,4,5,6,-2,-1,0};

//  inserting elements :-

    u.insert(4);    // None of these will be inserted, as all these elements were already present in the unordered set.
    u.emplace(4);
    u.insert(6);

    output(u);
    cout<<"Erasing a single element 6 from unordered set :-"<<endl;
    u.erase(6);
    output(u);
    cout<<"Erasing a single element -2 from unordered set using it's memory address :-"<<endl;
    u.erase(u.find(-2));
    output(u);
    cout<<"Erasing a range of elements between 0 and 4 from unordered set :-"<<endl;
//  u.erase(u.find(4),u.find(-1)); -----> In this case, since "-1" comes first then "4", so while removing, iterator moves in forward direction, but here after reaching "4", it can't find any element "-1" after that.
    if(u.find(4)!=u.end() && u.find(0)!=u.end() && *u.find(0)<*u.find(4)){
        u.erase(u.find(0),++u.find(4));
        output(u);
    }
    else{
        u.erase(u.find(4),++u.find(0));
        output(u);
    }
}

int main(){
    input();
    return 0;
}
/*
(1) reserve() :-
---> Reserves space for at least the specified number of elements.

All the operations take a time complexity of        O(1)  to   the MOST WORST CASE OF   O(N)

*/