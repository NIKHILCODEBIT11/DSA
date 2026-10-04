#include<bits/stdc++.h>
using namespace std;

// Here, in this file of hashing i am doing integer hashing and an important point to remember :-
// Inside main :- i can define an array of MAXIMUM INT SIZE :- arr[10^6] and a BOOLEAN OF SIZE 10^7
// Outside main :- i can define an array of MAXIMUM INT SIZE :- arr[10^7] and a BOOLEAN OF SIZE 10^8

int main(){
    int n;
    cout<<"Enter size of array :- ";
    cin>>n;
    int nums[n];
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }

    // PRECOMPUTE :-
    // First i will have to find MAX from array as i will have to define a hashmap of size MAX + 1
    int maximum = INT_MIN;
    for(int x : nums){
        maximum = max(maximum, x);
    }

    int hashmap[maximum+1] = {0};
    // Creating hashmap :-
    for(int i = 0; i < n; i++){
        hashmap[nums[i]]++;
    }

    // Fetching the occurences of each element inside nums via hashmap
    cout<<"Occurences :-"<<endl;
    for(int i = 0; i < maximum+1; i++){
        cout<<i<<" : "<<hashmap[i];
        cout<<endl;
    } 
    return 0;
}