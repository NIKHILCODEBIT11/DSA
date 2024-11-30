#include<iostream>
#include<set>

//      In multiset, it only follows "SORTING" not "UNIQUE" and thus more than 1 times, the element can be present, but will remain sorted.

using namespace std;

void output(multiset <int> &);

void input(){
    multiset <int> m = {3,4,4,4,5,5,5,6};

//  insert operation :-

    m.insert(2);
    m.insert(2);
    m.insert(3);
    output(m);

//  erasing a single element :-

    m.erase(4);     // Since, here i am passing a value, so it will erase all the occurences of the "value" passed.
    output(m);

//  erasing the first single occurence of element :-

    m.erase(m.find(3));
    output(m);

//  erasing a range of elements :-

    m.erase(m.find(3),m.find(5));
    output(m);

//  Counting number of occurences of a "value" :-

    int cnt=m.count(5);
    cout<<"Count of 5 is "<<cnt<<endl;

}

void output(multiset <int> &a){
    for(auto it :a){
        cout<<it<<" ";
    }
    cout<<endl;
}

int main(){
    input();
    return 0;
}