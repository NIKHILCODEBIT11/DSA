/*
Here, i am gonna REVERSE PARTS OF ARRAY
Like :- [2,3,4,5,6,7,8,9] ----> I have to rotate this array by d = 3 -----> [5,6,7,8,9,2,3,4]
In optimal i will :-

[2,3,4,   5,6,7,8,9] ------> I will divide array into 2 parts getting separated from the "d" index

Now reverse each of the segregated part of array then reverse the whole array at once

step 1 :- [4,3,2,    5,6,7,8,9]
step 2 :- [4,3,2,    9,8,7,6,5]
step 3 :- [5,6,7,8,9,2,3,4]
*/

#include<bits/stdc++.h>
using namespace std;

void reverse(vector <int> &nums, int start, int end){
    while(start <= end){
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void left_rotate_d_places(vector <int> &nums, int d){

    if(nums.size() <= 1){
        return;
    }

    // Normalize d:-
    d = d % nums.size();

    if(d == 0){
        return;
    }

    reverse(nums, 0, d - 1);
    reverse(nums, d, nums.size() - 1);
    reverse(nums, 0, nums.size() - 1);
}
int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }

    int d;
    cout<<"Enter number of places of rotation :- ";
    cin>>d;

    cout<<"Before left rotation by "<<d<<" places :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;

    left_rotate_d_places(nums , d);

    cout<<"After left rotation by "<<d<<" places :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}

/*
Time complexity :-
For 1st reversal :- O(d)
For 2nd reversal :- O(n-d)
For 3rd reversal :- O(n)

Time complexity :- O(d) + O(n-d) + O(n) = O(2n) ----> INCREASED TC AS FROM bruteforce {O(n+d)}
Space complexity :- O(1) ------> DECREASED SC AS FROM bruteforce {O(d)}

Although in "optimal" approach TC increased but sc has major reduction, so it is fine to use
*/