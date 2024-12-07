#include<iostream>
using namespace std;

int count(int,int arr[],int);

int main(){
    int n,n_;
    cout<<"Enter the number of items in array :- ";
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cout<<"Enter value at "<<i<<"th index :- ";
        cin>>arr[i];
    }
    cout<<endl<<"Enter the number whose count is needed :- ";
    cin>>n_;
    cout<<"The count of "<<n_<<" is "<<count(n_,arr,n);
    return 0;
}

int count(int n,int arr[],int a){
    int count_ = 0;
    for(int i=0;i<a;i++){      
        if(arr[i]==n){
            count_++;
        }
    }
    return count_;
}



/*

sample output :-


Enter the number of items in array :- 7
Enter value at 0th index :- 3
Enter value at 1th index :- 2
Enter value at 2th index :- 3
Enter value at 3th index :- 4
Enter value at 4th index :- 3
Enter value at 5th index :- 3
Enter value at 6th index :- 5

Enter the number whose count is needed :- 3
The count of 3 is 4


But, the issue in this program is that :-

-----> The tine complexity of this program is    O(N)    , as suppose user entered 4 elements in array, so the loop will run for 4 times
-----> Now,consider user wants to track different numbers like say 3 and 5 in the same program, then for getting count of each element, the time complexity will become    O(N) and again O(N)  collectively say    O(2N)

-----> Now consider user entered    10^5   elements in array and wants to know the count of again     10^5     integers, so time complexity will become     O(10^10N)


----> In general,    for 10^8 operations, it takes 1 second, so for 10^10 operations, it will take 100 seconds, which is not at all feasible.


So,      "HASHING"       comes for rescue
*/