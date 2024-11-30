#include<iostream>
#include<set>

using namespace std;

void output_set(set <int> &);
void set_explain(){
    set <int> s = {3,7,4,6};
    s.insert(22);
    s.insert(23);
    s.emplace(19);
//  cout<<s[0];     I can't use "index" method in "set"

    cout<<"Using find function :-";
    auto it=s.find(3);     // "find(a)" return the memory address of that location where that value "a" is present."
//  cout<<*it;      If i call the function till here only then i am getting garbage value (7), to avoid this i will need if-else stated beloe :-

    if(it==s.end()){
        cout<<"Element not found";
    }
    else{
        cout<<*it<<endl;
    }
    cout<<"Printing the elements of the set :-"<<endl;
    output_set(s);
    cout<<endl<<"Erasing single element 23 from the set :-"<<endl;
    s.erase(23);
    output_set(s);
    cout<<endl<<"Erasing multiple elements from set starting from 7 to 22:-"<<endl;
//  s.erase(s.begin(),s.end());     This will erase all elements.       And     s.erase(s.begin()+1,s.end()-2)      will show error as, "SET" do not support indexing   { s[0] or s.begin()+2 or s.end()-3 },   but can directly use    s.erase(s.begin(),s.end())

    auto e1=s.find(7);
    auto e2=s.find(22);

    if(e1 != s.end() && e2 != s.end()){
        s.erase(e1,e2);
    }

    output_set(s);

    // Count method of set :- Since, the set is a collection of UNIQUE and SORTED elements, so if, i do s.count(2), and if "2" is present, then it will return 1, and if "2" is not present in set, then it will return 0

    auto i = s.count(7);
    cout<<endl<<"In set s 7 is present :- "<<i<<endl;

    auto i1 = s.lower_bound(5);     // It will return me an iterator which will point to such a value which will be GREATER THAN OR EQUAL TO 5.
    cout<<"Lower bound of 5 is "<<*i1<<endl;

    i1 = s.upper_bound(5);     // It will return me an iterator which will point to such a value which will be GREATER THAN 5.
    cout<<"Upper bound of 5 is "<<*i1<<endl;

    // Next function is equal_range() :- It will return a "PAIR OF ITERATOR", in which the first iterator points to the first element that is greater than or equal to value {like lower_bound}
    //      and the other iterator will point to the first element of the set which is GREATER THAN value.

//  i1 = s.equal_range(5);  -----> Here, the error is that "equal_range(value)" returns a pair of iterator {pair <iterator,iterator>}, but previously when i use "auto", then at that time it was just a single iterator like  set <int> :: iterator it; which gets updated each time while using "lower_bound()" and "uppper_bound()", for which a single iterator was required but not this time.

    auto range = s.equal_range(5);
    if(range.first != s.end() && range.second != s.end()){
        cout<<"Equal range of 5 : ["<<*range.first<<", "<<*range.second<<")"<<endl;
    }

    // Using function key_comp() :-

    auto i3 = s.key_comp();     //In "set" by default the key_comp() function is std::less <T>, which i can change  refer program set_.cpp
    if(i3(4,6)){
        cout<<"4 is less than 6"<<endl;
    }

    if(i3(6,4)){
        cout<<"6 is less than 4"<<endl;
    }
}

void output_set(set <int> &a){
    for(auto it : a){       //  C++ COMPILER automatically converts     "auto it : a"       to          for (auto it = a.begin(); it != a.end(); ++it)      
        cout<<it<<" ";
    }
}
int main(){
    set_explain();
    return 0;
}

// Other functions like size(), swap(), is_empty() are similar to that of vector.

// In set, every operation happend with a "TIME COMPLEXITY" of log(n)