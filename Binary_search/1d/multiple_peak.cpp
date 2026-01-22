#include<bits/stdc++.h>
using namespace std;


/*
CONCEPT: Find Single Peak Element using Binary Search

- A peak element is strictly greater than its immediate neighbors:
  nums[i] > nums[i-1] AND nums[i] > nums[i+1]

ASSUMPTION:
- There is exactly ONE peak element in the array.

KEY IDEA (Slope-Based Binary Search):
- If nums[mid] < nums[mid+1], the array is increasing at mid,
  so the peak must lie on the RIGHT side.
- If nums[mid] > nums[mid+1], the array is decreasing at mid,
  so the peak must lie on the LEFT side (or at mid).

WHY THIS WORKS:
- An increasing slope must eventually end in a peak.
- A decreasing slope means we have already passed a peak.
- Since only one peak exists, we never lose it by following the slope.

IMPLEMENTATION NOTES:
- Handle edge cases separately (first or last element).
- Perform binary search only in range [1 ... n-2]
  so that mid-1 and mid+1 are always valid.

TIME COMPLEXITY: O(log n)
SPACE COMPLEXITY: O(1)
*/


/*
CONCEPT: Find Any Peak Element (Multiple Peaks Allowed)

- A peak element is strictly greater than its immediate neighbors:
  nums[i] > nums[i-1] AND nums[i] > nums[i+1]

ASSUMPTION:
- There may be MULTIPLE peak elements.
- We need to return ANY ONE of them.

KEY OBSERVATION:
- At least one peak always exists in an array.

SLOPE-BASED BINARY SEARCH:
- If nums[mid] < nums[mid-1], the slope is descending from the left,
  so a peak must exist on the LEFT side.
- Otherwise, the slope is flat or rising from the left,
  so a peak must exist on the RIGHT side.

WHY THIS WORKS:
- Binary search always moves toward a guaranteed peak.
- Even if multiple peaks exist, at least one remains in the search range.

IMPLEMENTATION NOTES:
- First and last elements are checked separately.
- Binary search is applied in range [1 ... n-2].
- Only slope comparison is needed; no extra cases required.

TIME COMPLEXITY: O(log n)
SPACE COMPLEXITY: O(1)
*/



int multiple(vector <int>&nums){
    int low=1,high=nums.size()-2;
    if(nums.size()==1){
        return nums[0];
    }
    else if(nums[0]>nums[1]){
        return nums[0];
    }
    else if(nums[nums.size()-1]>nums[nums.size()-2]){
        return nums[nums.size()-1];
    }
    else{
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]>nums[mid-1] && nums[mid]>nums[mid+1]){
                return nums[mid];
            }
            else{
                if(nums[mid]<nums[mid-1]){
                    low=mid+1;
                }
                else{
                    high=mid-1;
                }

                /*
                
                if(nums[mid]<nums[mid-1]){
                    high=mid-1;
                }
                else{
                    low=mid+1;
                }

                */
            }
        }
    }
    return -1;
}

int main(){
    vector <int> nums={2,5,2,3,2};
    int res=multiple(nums);
    cout<<"The multiple peak element is "<<res;
    return 0;
}