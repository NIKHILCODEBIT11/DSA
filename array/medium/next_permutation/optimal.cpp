#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
                     STEP-BY-STEP DRY RUN ON {2, 1, 5, 4, 3, 0, 0}
================================================================================
Initial Array:
Indices:   0   1   2   3   4   5   6
Values:   [2,  1,  5,  4,  3,  0,  0]
           n = 7

--- STEP 1: Find the break point (pivot) --- Right se khojta hua aaunga aur jaha mujhe nums[i] < nums[i+1] wahi i hoga break point
Traverse from i = n - 2 = 5 down to 0:
- i = 5: nums[5] < nums[6] -> 0 < 0  (False)
- i = 4: nums[4] < nums[5] -> 3 < 0  (False)
- i = 3: nums[3] < nums[4] -> 4 < 3  (False)
- i = 2: nums[2] < nums[3] -> 5 < 4  (False)
- i = 1: nums[1] < nums[2] -> 1 < 5  (True!) -> BREAK POINT FOUND!
Result: index = 1 (Value = nums[1] = 1)

--- STEP 2: Find just greater element than nums[index] from right --- Uske baad array ke end se leke index+1 tak aaunga aur jo pehla number GREATER THAN nums[index] hoga uske saath hi nums[index] ko swap kar dunga
Traverse from i = n - 1 = 6 down to index + 1 = 2:
- i = 6: nums[6] > nums[index] -> 0 > 1 (False)
- i = 5: nums[5] > nums[index] -> 0 > 1 (False)
- i = 4: nums[4] > nums[index] -> 3 > 1 (True!) -> FIRST MATCH FOUND!
Swap nums[index] (1) with nums[4] (3):
Array after swap:
Indices:   0   1   2   3   4   5   6
Values:   [2,  3,  5,  4,  1,  0,  0]

--- STEP 3: Reverse the suffix from index + 1 to end --- Ab kyuki maine swap kar diya to wo jo 'index' yaani break point wala number tha {DENOTED AS K} wo chala gaya hoga right side mein jiske saath swap kiya tha aur kyuki yaha jo pehe numer tha WO EK LAUTA AISA NUMBER THA JO KI 'K' SE HALKA SA HI BADA THA ISLIYE SWAP KE BAAD WAHA JO 'K' GAYA HAI WO BHI uske right mein rehne wale numbers se bada hoga aur saath  hi left mein rehne wale numbers se chota hoga to reverse karne se koi dikkat nahi haikyuki JO DESCENDING RAHA HOGA AB WO ASCENDING HO JAYEGA
Reverse range: from (index + 1) = 2 to index 6:
Subarray to reverse: [5, 4, 1, 0, 0]
Reversed subarray:   [0, 0, 1, 4, 5]

Final Array:
Indices:   0   1   2   3   4   5   6
Values:   [2,  3,  0,  0,  1,  4,  5]
================================================================================
*/

vector <int> next_perm(vector <int> &nums){
    int n = nums.size();
    int index = -1;

    // Finding the break point :-
    for(int i = n-2;i >= 0;i--){
        if(nums[i] < nums[i+1]){
            index = i;
            break;
        }
    }
    if(index == -1){
        reverse(nums.begin(), nums.end());
        return nums;
    }

    // traverse the array from end till index  i and find nums[j] > nums[i] ---> ONLY FIRST OCCURENCE
    for(int i = n-1;i > index;i--){
        if(nums[i] > nums[index]){
            swap(nums[index], nums[i]);
            break;
        }
    }

    // Just sort the remainning elements after index :-
    reverse(nums.begin()+index+1, nums.end());
    return nums;
}

int main(){
    vector <int> nums = {2,1,5,4,3,0,0};
    cout<<"Before next permutation :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
    nums = next_perm(nums);
    cout<<"After next permutation :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
}

/*
Time Complexity (TC): O(N)
    1. Finding the pivot: At most N - 1 comparisons while scanning right to left ---> O(N).
    2. Finding the swap candidate: At most N comparisons while scanning from the end ---> O(N).
    3. Reversing the suffix: Reversing at most N elements takes O(N) swaps.
    4. Total Time Complexity = O(N) + O(N) + O(N) = O(3*N) = O(N).

Space Complexity (SC): O(1) auxiliary space (O(N) as written due to pass-by-value return)
    1.Auxiliary Space: O(1) because the pointers, comparisons, swaps, and reverse operations all modify the vector in-place without allocating dynamic memory.
    2. Return Value Note: Because the return type is vector<int> instead of void or vector<int>&, returning by value creates an O(N) copy of the vector. Changing it to void next_perm(vector<int> &nums) makes the overall extra space strictly O(1).
*/