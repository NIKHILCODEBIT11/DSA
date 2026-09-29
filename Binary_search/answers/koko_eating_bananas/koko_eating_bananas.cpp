#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (KOKO EATING BANANAS - OPTIMAL BINARY SEARCH):
   - Problem:
     Hume piles of bananas ka ek array `nums` diya hai aur ek deadline `hour` di hai.
     Hume MINIMUM eating rate `k` (bananas per hour) nikalna hai taaki Koko saare 
     bananas diye gaye `hour` ke andar ya barabar time me kha sake.
     Condition: Agar ek pile me `k` se kam bananas bache hain, toh bhi Koko bacha 
     hua ghanta aaram karegi (agli pile agli hour me hi shuru hogi).
     Matlab ek pile `nums[i]` ko finish karne me ceil(nums[i] / k) ghante lagenge.

   - Monotonic Search Space (Binary Search on Answers):
     - Minimum possible eating rate: low = 1 banana/hour.
     - Maximum meaningful eating rate: high = max_element(nums).
       Kyun? Agar Koko sabse badi pile ke barabar speed se khayegi, toh har pile 
       exactly 1 ghante me khatam ho jayegi (total time = nums.size() hours).
       Isse tez speed lene par bhi time kam nahi ho sakta kyunki har pile kam se kam 
       1 pura ghanta leti hi hai.
     - Jaise jaise eating rate `mid` badhta hai:
       Har pile me lagne wala time ceil(nums[i] / mid) kam hota hai.
       Iska matlab total required time monotonically decrease hota hai.
     - Search Space ka Nature:
       Rate:    1      2      3   ...   k      k+1   ...   max(nums)
       Valid? [No,    No,    No,  ...  Yes,    Yes,  ...     Yes   ]
     - Hume pehla (minimum) "Yes" dhundhna hai. Is binary transition (No -> Yes) 
       ki wajah se hum Linear Search (O(M)) ki jagah Binary Search (O(log M)) use karte hain.

   - The Polarity Switch (Why returning `low` is guaranteed correct):
     - `low` shuru hota hai invalid side (No / total_hour > hour).
     - `high` shuru hota hai valid side (Yes / total_hour <= hour).
     - Jab `total_hour <= hour` hota hai:
       Speed valid hai, par hume smaller rate dekhna hai, toh left jao: `high = mid - 1`.
     - Jab `total_hour > hour` hota hai:
       Speed bohot slow hai, deadline miss ho gayi, toh speed badhao: `low = mid + 1`.
     - Jab binary search khatam hota hai (low > high):
       `high` slip hokar last INVALID rate par rukta hai.
       `low` aage badhkar theek first VALID (minimum required rate) par land karta hai!
       Isliye seedhe `return low;` answer deta hai.

   - Important Practical Gotchas (Production / LeetCode Alert):
     1. Overflow in total_hour: Agar piles badi hon aur `mid` chhota ho, toh ghanton ka 
        sum 32-bit int ki limit (2 * 10^9) cross kar sakta hai. Isliye `calculate_total_hour` 
        me return type aur sum ko `long long` rakhna best practice hai.
     2. Mid calculation: Integer overflow se bachne ke liye `low + (high - low) / 2` 
        likhna safer hota hai.
     3. Ceil without double: Floating-point precision error se bachne ke liye integer math 
        bhi use kar sakte hain: ceil(nums[i] / hourly) == (nums[i] + hourly - 1) / hourly.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `findmax(v)` ---
   - `int max_i = INT_MIN;` : Maximum element track karne ke liye minimum possible value se initialize kiya.
   - `for(int i = 0; i < v.size(); i++) max_i = max(max_i, v[i]);` : Pure array ko scan karke highest pile size nikal liya (jo humara `high` banega).

   --- `calculate_total_hour(nums, hourly)` ---
   - `int total_hour = 0;` : Given eating rate `hourly` ke hisab se total hours accumulate karne ke liye.
   - `total_hour += ceil((double)nums[i] / (double)hourly);` : 
     Double cast karke accurate floating division kiya aur uska ceiling lekar total hours me add kiya.

   --- `rate(nums, hour)` ---
   - `int low = 1, high = findmax(nums);` :
     Binary search boundaries initialize kiye: minimum possible speed 1 se max pile size tak.
   - `while(low <= high)` :
     Jab tak search window valid hai tab tak binary search chalega.
   - `int mid = (low + high) / 2;` :
     Middle eating speed calculate ki.
   - `if (total_hour <= hour) high = mid - 1;` :
     Mid speed par Koko time ke andar bananas finish kar leti hai! 
     Yeh ek valid answer hai, par hume MINIMUM speed chahiye, isliye aur chhota candidate 
     left side me dhundhne ke liye `high = mid - 1` kar diya.
   - `else low = mid + 1;` :
     Deadline miss ho gayi (time zyada lag gaya), matlab Koko bohot dheere kha rahi hai. 
     Speed badhane ke liye right half me shift hue: `low = mid + 1`.
   - `return low;` :
     Loop cross hone ke baad `low` exactly minimum valid speed par settle hota hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Input: nums = [3, 4, 7, 9, 12], hour = 11
   findmax(nums) = 12
   Initial State: low = 1, high = 12

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 1, high = 12
   mid = (1 + 12) / 2 = 6

   Call calculate_total_hour(nums, hourly = 6):
     ceil(3 / 6)  = 1
     ceil(4 / 6)  = 1
     ceil(7 / 6)  = 2
     ceil(9 / 6)  = 2
     ceil(12 / 6) = 2
     total_hour = 1 + 1 + 2 + 2 + 2 = 8 hours

   Check: total_hour <= hour (8 <= 11) -> TRUE (Valid speed!)
   Action:
     Left half me aur chhota rate dhundho:
     high = mid - 1 = 6 - 1 = 5
   State updated: low = 1, high = 5

   --- Iteration 2 ---
   low = 1, high = 5
   mid = (1 + 5) / 2 = 3

   Call calculate_total_hour(nums, hourly = 3):
     ceil(3 / 3)  = 1
     ceil(4 / 3)  = 2
     ceil(7 / 3)  = 3
     ceil(9 / 3)  = 3
     ceil(12 / 3) = 4
     total_hour = 1 + 2 + 3 + 3 + 4 = 13 hours

   Check: total_hour <= hour (13 <= 11) -> FALSE (Deadline miss!)
   Action:
     Speed badhao -> right side jao:
     low = mid + 1 = 3 + 1 = 4
   State updated: low = 4, high = 5

   --- Iteration 3 ---
   low = 4, high = 5
   mid = (4 + 5) / 2 = 4

   Call calculate_total_hour(nums, hourly = 4):
     ceil(3 / 4)  = 1
     ceil(4 / 4)  = 1
     ceil(7 / 4)  = 2
     ceil(9 / 4)  = 3
     ceil(12 / 4) = 3
     total_hour = 1 + 1 + 2 + 3 + 3 = 10 hours

   Check: total_hour <= hour (10 <= 11) -> TRUE (Valid speed!)
   Action:
     Left half me jao:
     high = mid - 1 = 4 - 1 = 3
   State updated: low = 4, high = 3

   --- Loop Terminate ---
   Condition: low <= high (4 <= 3) -> FALSE! Loop terminates.

   Visual of Final Polarity State:
   Speed:         1       2       3   |   4       5       6  ...  12
   Valid?        No      No      No   |  Yes     Yes     Yes ... Yes
                                  ^       ^
                                 high    low
   
   high = 3 (Last invalid / deadline miss speed)
   low  = 4 (First valid / minimum required speed)

   Returns low = 4.
   Final Output: "The minimum value is 4"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size() aur M = max_element in nums.
     * `findmax()` function pure array ko scan karta hai: O(N).
     * Binary Search space [1, M] me traverse karta hai: O(log2 M) steps.
     * Har step par `calculate_total_hour()` N elements iterate karta hai: O(N).
     * Total Time Complexity: O(N) + O(N * log2 M) = O(N * log2 M).
     * Brute Force O(N * M) ke muqable yeh massively fast hai.
       (e.g., Agar M = 10^9 ho, toh Linear search me 10^9 checks lagenge, 
        jabki Binary search me sirf log2(10^9) ≈ 30 checks lagenge!).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard primitive variables 
       (`low`, `high`, `mid`, `total_hour`, `max_i`) use hue hain.
       Koi extra array, hash map ya recursive stack use nahi hua.
======================================================================
*/

int findmax(vector <int> &v){               // Used for calculating maximum/high in function "rate"
    int max_i=INT_MIN;
    for(int i=0;i<v.size();i++){
        max_i=max(max_i,v[i]);
    }
    return max_i;
}

int calculate_total_hour(vector <int> &nums,int hourly){        // Used for calculating total_hour for each pile of banana mentioned with default rate of   "mid"   bananas per hour
    int total_hour=0;
    for(int i=0;i<nums.size();i++){
        total_hour+=ceil((double)nums[i]/(double)hourly);
    }
    return total_hour;
}

int rate(vector <int> &nums,int hour){              // It will check and update low, high and will ultimately give the final "rate"
    int low=1,high=findmax(nums);    // or simply   high = *max_elements(nums.begin(), nums.end());
    while(low<=high){
        int mid=(low+high)/2;
        int total_hour=calculate_total_hour(nums,mid);
        if(total_hour<=hour){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;         // "low" index will be the   MINIMUM   value or "rate"
}



/*

Consider pile as :-     [3,6,7,11]   with h=8

suppose i assume      rate = 3 bananas/hour

so, time= 1 + 2 + 3 + 4 = 10hours   >  8 hours, so reduce    value of "rate"


min start value = 1

max start value = maximum element from the given array of pile i.e,   11

PROOF :-

For rate = 11 :-
time = 1 + 1 + 1 + 1 = 4   WHICH IS THE ANSSWER EVEN IF I TAKE   rate = 12,13,14,15,16 ..........

So, my answer will lie between [1 2 3 4 5 6 7 8 9 10 11]



ceil(4/3)=2  as 4/3=1.333 which with ceil gives 2

            1       2      3       4       5       6       7       8       9       10      11
            no      no     no     yes     yes     yes     yes     yes     yes     yes      yes

1st         low                                   mid                                      high
2nd         low            mid            high
3rd                               low     high
                                 and mid
4th                        high   low   


Reason for using double() in ceil :-

used double because ceil() works on floating-point numbers, not integers.

with integer :-
7 / 3 = 2          // decimal LOST
ceil(2) = 2 ❌

with double :-
ceil(2.333...) = 3

*/


int main(){
    vector <int> nums={3,4,7,9,12};
    int hours;
    cout<<"Enter hours :- ";
    cin>>hours;
    int ans=rate(nums,hours);
    cout<<"The minimum  value is "<<ans;
    return 0;
}