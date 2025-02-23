// Here, i am doing "Hashing" to reduce the time taken for counting number of elements

// Suppose i have to make an array where atmax element can be 12 {given in question}, and i will have to return count of the element specified by the user

#include<iostream>
using namespace std;

int main(){
    int arr[]={2,3,4,3,2,4,5,4,6,5,7,12,7,6,12,9};     // Declared this array
    int hash[13]={};       //   Declaring a hash array which can have 13 elements, as atmax element of the upper array is 12
    //   Now, hash array has index from   0 ----> 11  , in which i will store the count of element of arr in the respective index of hash[], so that when i will require count of an element from arr[], i can directly refer to that index in hash[]
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){      // Here, since i am directly using array arr instead of passing it to a function, so here arr cats as an array not like pointer
        int k = arr[i];
//      hash[k]=hash[k]++;      --->     Here, the error is that        hash[k]=hash[k]=hash[k]+1;     due to which it firstly returns the value then updates so it will always remain zero
        hash[k]++;
    }
    cout<<"The count of "<<12<<" in arr is "<<hash[12];
    return 0;
}

/*
hash[12]={}  ----->  It will create an array of 12 elements with all entries 0
hash[12]={0} ----->  It will create an array of 12 elements with all entries 0
hash[12]={0,} ----->  It will create an array of 12 elements with all entries 0
hash[12]={0,0} ----->  It will create an array of 12 elements with all entries 0
and so on.....
*/