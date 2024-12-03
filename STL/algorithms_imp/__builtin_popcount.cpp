#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int a =7;
    int count = __builtin_popcount(a);
    cout<<"Using __builtin_popcount() for an integer :-"<<endl;
    cout<<"The number of 1s in binary form of "<<a<<" is "<<count;
    cout<<"\nUsing __builtin_popcount() for a long double :-"<<endl;
    long long num = 2435626462874536473;
    int count_ = __builtin_popcountll(num);
    cout<<"The number of set bits in binary form of "<<num<<" is "<<count_;
    return 0;
}


//  __builtin_popcount()  is a GCC-specific function, and it returns the number of set bits (1s) in the binary form of a number.
// In binary form   7     has   0111 {in 4 bits} but in any representation of bits, it will only have 3 "1s", which is being returned by   __builtin_popcount(7)


/*
Difference between __builtin_popcount() and __builtin_popcountll() :-

----> The argument to __builtin_popcount() is usually an int, but if i pass a long long to it, then the function will implicitly cast 
the long long to int, which may lead to truncation or loss of data, if the number is too large to fit in int.

----> This function is specifically designed to count the set bits in a long long type and it does not require conversion from long long
to int.



######### Even in outputo f this program :-


if i didn't used __builtin_popcountll() , then :-


Using __builtin_popcount() for an integer :-
The number of 1s in binary form of 7 is 3
Using __builtin_popcount() for a long double :-
The number of set bits in binary form of 2435626462874536473 is 13



if i used __builtin_popcountll() , then :-


Using __builtin_popcount() for an integer :-
The number of 1s in binary form of 7 is 3
Using __builtin_popcount() for a long double :-
The number of set bits in binary form of 2435626462874536473 is 28
*/