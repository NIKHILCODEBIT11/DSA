#include<bits/stdc++.h>
using namespace std;

// Return the element which is present in the array only a single time rest all elements are present 2 times each.


/*
CONCEPT: Single Element in a Sorted Array (Binary Search)

- Array is sorted
- Every element appears exactly twice, except one element which appears once

KEY OBSERVATION:
- Before the single element → pairs start at EVEN indices
  (nums[0] == nums[1], nums[2] == nums[3], ...)
- After the single element → pairs start at ODD indices
  (nums[1] == nums[2], nums[3] == nums[4], ...)

BINARY SEARCH STRATEGY:
1. Handle edge cases first:
   - If nums[0] != nums[1] → single element is at index 0
   - If nums[n-1] != nums[n-2] → single element is at last index

2. Apply binary search between indices [1 ... n-2]
   (so mid-1 and mid+1 are always valid)

3. At each mid:
   - If nums[mid] != nums[mid-1] AND nums[mid] != nums[mid+1]
     → nums[mid] is the single element

4. Use index parity to decide direction:
   - If mid is EVEN and nums[mid] == nums[mid+1]
     → single element lies on the RIGHT side
   - If mid is ODD and nums[mid] == nums[mid-1]
     → single element lies on the RIGHT side
   - Otherwise → single element lies on the LEFT side

5. Always shrink search space accordingly until the single element is found

TIME COMPLEXITY: O(log n)
SPACE COMPLEXITY: O(1)
*/


int single(vector <int> &nums){
    int low=1,high=nums.size()-2;

    if(nums.size()==1){
        return nums[0];
    }
    else if(nums[0]!=nums[1]){
        return nums[0];
    }
    else if(nums[nums.size()-1]!=nums[nums.size()-2]){
        return nums[nums.size()-1];
    }
    
    while(low<=high){
    int mid=(low+high)/2;
    if(nums[mid]!=nums[mid-1] && nums[mid]!=nums[mid+1]){
        return nums[mid];
    }
    else{
        if((mid%2==1 && nums[mid]==nums[mid-1]) || (mid%2==0 && nums[mid]==nums[mid+1])){
            low=mid+1;
        }
        else{
            high=mid-1;;
        }
    }
    }
    return -1;
}

int main(){
    vector <int> nums={2,2,3,3,4,6,6,7,7,9,9};
    int res=single(nums);
    cout<<"The single element is "<<res;
    return 0;
}