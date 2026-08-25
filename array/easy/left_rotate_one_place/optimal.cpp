// Here, suppose i have an array [1,2,3,4,5,6] so after left rotation by 1 place i should get [2,3,4,5,6,1]
// I will store the first element in temp and will start a loop from i = 1 till i = n-1 and will replace (i-1)th element with ith element

#include<bits/stdc++.h>
using namespace std;

void left_rotate_one_place(vector <int> &nums){
    if(nums.empty()){    // This is for empty vector
        return;
    }

    auto temp = nums[0];
    for(int i = 1; i < nums.size(); i++){
        nums[i-1] = nums[i];
    }
    nums[nums.size() - 1] = temp; 

    // For rotation using stl i could also do :-
    // std::rotate(nums.begin(), num.begin() + 1, nums.end())
}

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    cout<<"Before left rotation by one place :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;

    left_rotate_one_place(nums);

    cout<<"After left rotation by one place :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}

// Time complexity :- O(N)   ----> As, i am traversing over whole vector
// Space complexity :- O(1)  ----> As, i am using no extra space

// std::rotate(first, middle, last);

// Left Rotate by 1 ----> std::rotate(nums.begin(), nums.begin() + 1, nums.end()); ----> Element at index 1 becomes the start.
// Left Rotate by K ----> std::rotate(nums.begin(), nums.begin() + k, nums.end()); ----> Element at index k becomes the start.
// Right Rotate by K----> std::rotate(nums.begin(), nums.end() - k, nums.end()); ------> Element at index n - k becomes the start.