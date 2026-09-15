/*
Suppose given array is :- [0,1,2,0,1,2,1,2,0,0,0,1]
Now i will traverse whole array and will have 3 counters :-
cout0 :- counting number of 0s
cout1 :- counting number of 1s
cout2 :- counting number of 2s
after this i will traverse array from i=0 to cout0-1 and make all elements 0s
after this i will traverse array from i=cout0 to cout1-1 and make all elements 1s
after this i will traverse array from i=cout0+cout1 to cout2-1 and make all elements 2s
*/

#include<bits/stdc++.h>
using namespace std;

void sort_0s_1s_2s(vector <int> &nums){
    int n = nums.size();
    int cout0 = 0, cout1 = 0,cout2 = 0;
    for(int i = 0;i < n;i++){
        if(nums[i] == 0){
            cout0++;
        }
        else if(nums[i] == 1){
            cout1++;
        }
        else{
            cout2++;
        }
    }

    // Editing the array with initially cout0 0s then cout1 1s and finally cout2 2s
    for(int i = 0; i < cout0;i++){
        nums[i] = 0;
    }
    for(int i = cout0;i < cout0 + cout1;i++){
        nums[i] = 1;
    }
    for(int i = cout0 + cout1;i < n;i++){
        nums[i] = 2;
    }
}

int main(){
    vector <int> nums = {0,1,2,0,1,2,1,2,0,0,0,1};
    int n = nums.size();
    cout<<"Before sorting :-"<<endl;
    for(int i = 0;i < n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    sort_0s_1s_2s(nums);
    cout<<"After sorting :-"<<endl;
    for(int i = 0;i < n;i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}

/*
TC :- O(2N) ----> As, i am traversing whole array 2 times 1st time for updating cout0 cout1 and cout2 and 2nd time for replacing elements in array
SC :- O(1) ----> As, no extra space is used
*/