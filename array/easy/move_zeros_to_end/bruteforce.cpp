// Here, o am going to follow 3 step process :-
// Step - 1 :- Iterate over the whole array and find NON-ZERO terms and store them in a vector temp
// Step - 2 :- Iterate over vector nums till the size of temp and put all the non-zero numbers and also a varable poiting to the size of array so as to start putting zeros from that iindex in array
// Strp - 3 :- Iterate over array starting from size of array till the size of nums and put zeros

#include<bits/stdc++.h>
using namespace std;

void move_zeros_to_end(vector <int> &nums){
    int n = nums.size();
    vector <int> temp;

    // Step - 1 :-
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] != 0){
            temp.push_back(nums[i]);
        }
    }

    // Step - 2 :-
    int non_zero_size = temp.size();
    for(int i = 0;i < temp.size(); i++){
        nums[i] = temp[i];
    }

    // Step - 3 :-
    for(int i = non_zero_size; i < n; i++){
        nums[i] = 0;
    }
}

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    cout<<"Before moving zeros to end :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;

    move_zeros_to_end(nums);

    cout<<"After moving zeros to end :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}

// Time complexity :- O(N) + O(X) + O(N-X)  ----> O(2*N) ----> As, O(N) for traversal in step 1 then O(X) for traversal in step 2 then O(N-X) for traversal in step 2
// Space complexity :- O(N)  ----> As, in worst case there might be no zeros in nums, so temp will be as of the size of nums

