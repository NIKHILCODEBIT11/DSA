/*
Here, i am using 2 pointer approach or sliding window approach
left right start from 0 
right badhate jao jab tak sum k ke barabar naa mile lekin agar right badhate hue sum agar k ko cross kar gaya 
tab left wale se subtract karo sum ko aur left ko aage move karo
*/

#include<bits/stdc++.h>
using namespace std;

int longest_subarray_with_sum_k(vector <int> &nums, int k){
    int left = 0;
    int right = 0;
    int sum = nums[0];
    int max_len = 0;
    int n = nums.size();

    while (right < n) {
        // Agar sum k se bada ho gaya hai toh left se shrink karo
        while (left <= right && sum > k) {
            sum -= nums[left];
            left++;
        }

        // Agar sum k ke barabar aa gaya toh length calculate karo
        if (sum == k) {
            max_len = max(max_len, right - left + 1);
        }

        // Window ko aage expand karo
        right++;
        if (right < n) {
            sum += nums[right];
        }
    }
    return max_len;
}

/*
Two-pointer / Sliding Window approach ki complexities:

Time Complexity (TC): O(2N) jo overall O(N) banta hai.
right pointer index 0 se lekar N−1 tak chalega (total N steps).
left pointer bhi array ke shuru se aage badhte hue maximum N steps hi chal sakta hai (wo kabhi peeche nahi jaata).
Bhale hi nested while loop hai, par dono pointers milakar poore code ke execution mein maximum 2N steps lete hain, isliye time complexity linear O(N) rehti hai.

Space Complexity (SC): O(1)
Koi hashmap, extra array ya dynamic memory use nahi hoti; sirf 4 variables (left, right, sum, max_len) use hote hain.

Reason of TC O(2n) not O(n**2) even thugh nested while loops are present :-

Hamara inner loop:
while (left <= right && sum > k) {
    sum -= a[left];
    left++; // <--- Is variable ko dhyan se dekho
}

left kabhi piche nahi jata: Poore program mein kahin bhi left-- ya left = 0 (reset) nahi likha hai.
left hamesha aage hi badhta hai (left++).
left ki shuruat 0 se hoti hai aur ye zyada se zyada kahan tak jaa sakta hai? Array ke aakhiri index tak (N).
*/

/*
================================================================================
DRY RUN ON EXAMPLE: arr = [7, 0, 0, 0, 0, 0, 3], k = 3, n = 7
================================================================================

INITIAL STATE:
- left = 0, right = 0
- sum = arr[0] = 7
- max_len = 0

--------------------------------------------------------------------------------
ITERATION 1 (right = 0, arr[0] = 7):
- Check: sum > k (7 > 3) -> TRUE
  * sum -= arr[left] => sum = 7 - 7 = 0
  * left++ => left = 1
  * Now sum <= k, inner while-loop breaks.
- Check: sum == k (0 == 3) -> FALSE
- Expand: right++ => right = 1
  * sum += arr[1] => sum = 0 + 0 = 0
- Status: left = 1, right = 1, sum = 0, max_len = 0

--------------------------------------------------------------------------------
ITERATION 2 (right = 1, arr[1] = 0):
- Check: sum > k (0 > 3) -> FALSE
- Check: sum == k (0 == 3) -> FALSE
- Expand: right++ => right = 2
  * sum += arr[2] => sum = 0 + 0 = 0
- Status: left = 1, right = 2, sum = 0, max_len = 0

--------------------------------------------------------------------------------
ITERATION 3 (right = 2, arr[2] = 0):
- Check: sum > k (0 > 3) -> FALSE
- Check: sum == k (0 == 3) -> FALSE
- Expand: right++ => right = 3
  * sum += arr[3] => sum = 0 + 0 = 0
- Status: left = 1, right = 3, sum = 0, max_len = 0

--------------------------------------------------------------------------------
ITERATION 4 (right = 3, arr[3] = 0):
- Check: sum > k (0 > 3) -> FALSE
- Check: sum == k (0 == 3) -> FALSE
- Expand: right++ => right = 4
  * sum += arr[4] => sum = 0 + 0 = 0
- Status: left = 1, right = 4, sum = 0, max_len = 0

--------------------------------------------------------------------------------
ITERATION 5 (right = 4, arr[4] = 0):
- Check: sum > k (0 > 3) -> FALSE
- Check: sum == k (0 == 3) -> FALSE
- Expand: right++ => right = 5
  * sum += arr[5] => sum = 0 + 0 = 0
- Status: left = 1, right = 5, sum = 0, max_len = 0

--------------------------------------------------------------------------------
ITERATION 6 (right = 5, arr[5] = 0):
- Check: sum > k (0 > 3) -> FALSE
- Check: sum == k (0 == 3) -> FALSE
- Expand: right++ => right = 6
  * sum += arr[6] => sum = 0 + 3 = 3
- Status: left = 1, right = 6, sum = 3, max_len = 0

--------------------------------------------------------------------------------
ITERATION 7 (right = 6, arr[6] = 3):
- Check: sum > k (3 > 3) -> FALSE
- Check: sum == k (3 == 3) -> TRUE (MATCH FOUND)
  * len = right - left + 1 = 6 - 1 + 1 = 6
  * max_len = max(0, 6) = 6
  * Subarray elements: arr[1...6] = [0, 0, 0, 0, 0, 3]
- Expand: right++ => right = 7 (7 < 7 is FALSE, no sum update)
- Status: left = 1, right = 7, sum = 3, max_len = 6

--------------------------------------------------------------------------------
TERMINATION:
- Outer loop condition fails (right < n is FALSE since 7 < 7 is false).
- Return max_len = 6.
================================================================================
*/