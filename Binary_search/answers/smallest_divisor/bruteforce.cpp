#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIND THE SMALLEST DIVISOR GIVEN A THRESHOLD):
   - Problem:
     Hume ek array `nums` aur ek integer `threshold` diya gaya hai.
     Hume ek aisa positive integer `d` (divisor) dhundhna hai jisse array ke 
     har element ko divide karke ceil lene par jo sum aaye, wo `<= threshold` ho:
         sum = ceil(nums[0]/d) + ceil(nums[1]/d) + ... + ceil(nums[n-1]/d) <= threshold
     Hume aisa SMALLEST possible `d` return karna hai.

   - Brute Force Approach:
     Smallest divisor `1` se shuru karo aur badhate jao:
     - Divisor `d = 1` par sum maximum hoga (array ka direct sum).
     - Jaise jaise divisor `d` badhega, har fraction `nums[i] / d` chhota hoga, 
       matlab total `sum` monotonically decrease hoga!
     - Jaise hi pehla aisa `d` mile jahan `sum <= threshold`, wahi humara 
       SMALLEST divisor answer hoga.

   - CRITICAL BUG IN GIVEN CODE (Loop Boundary):
     Code me likha hai:
         for(int d = 1; d < *max_element(nums.begin(), nums.end()); d++)
     Notice the `<` sign! 
     Agar answer array ka maximum element hi hua (jaise threshold bohot tight ho 
     aur har element divide hokar ceil 1 ban jaye), toh yeh loop max element tak 
     pahunchne se pehle hi terminate ho jayega aur -1 return kar dega!
     Correct condition: `d <= *max_element(...)` hona chahiye.

   - Ceil Integer Division Trick (Without Double/Ceil):
     `ceil((double)a / (double)b)` floating-point conversion karta hai jo slow aur 
     precision issues de sakta hai.
     Pure integer math se ceil nikalne ka standard formula:
         ceil(a / b) == (a + b - 1) / b

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int d = 1; d <= max_val; d++` :
     Divisor ko 1 se shuru karke maximum possible value tak linear test kar rahe hain.
   - `int sum = 0;` :
     Har divisor `d` ke liye naya sum calculate karne ke liye reset karte hain.
   - `sum += ceil((double)nums[i] / (double)d);` :
     Har element ko `d` se divide karke ceiling value nikal kar sum me accumulate karte hain.
   - `if (sum <= threshold) return d;` :
     Kyunki hum `d = 1` se start karke aage badh rahe hain, toh jo pehla `d` 
     condition satisfy karega, wo automatically minimum/smallest divisor hoga!
   - `return -1;` :
     Fallback return (agar koi divisor na mile).

======================================================================
3. DETAILED DRY RUN (Step-by-Step Table):

   Input: nums = [1, 2, 5, 9], threshold = 6
   Max Element in nums = 9
   Search Range for d: 1 to 9

   -------------------------------------------------------------------
   Iter 1: d = 1
   - ceil(1 / 1) = 1
   - ceil(2 / 1) = 2
   - ceil(5 / 1) = 5
   - ceil(9 / 1) = 9
   Total Sum = 1 + 2 + 5 + 9 = 17
   Check: sum <= threshold (17 <= 6) -> FALSE!
   Continue to next d.

   Iter 2: d = 2
   - ceil(1 / 2) = 1
   - ceil(2 / 2) = 1
   - ceil(5 / 2) = 3
   - ceil(9 / 2) = 5
   Total Sum = 1 + 1 + 3 + 5 = 10
   Check: sum <= threshold (10 <= 6) -> FALSE!
   Continue to next d.

   Iter 3: d = 3
   - ceil(1 / 3) = 1
   - ceil(2 / 3) = 1
   - ceil(5 / 3) = 2
   - ceil(9 / 3) = 3
   Total Sum = 1 + 1 + 2 + 3 = 7
   Check: sum <= threshold (7 <= 6) -> FALSE!
   Continue to next d.

   Iter 4: d = 4
   - ceil(1 / 4) = 1
   - ceil(2 / 4) = 1
   - ceil(5 / 4) = 2
   - ceil(9 / 4) = 3
   Total Sum = 1 + 1 + 2 + 3 = 7
   Check: sum <= threshold (7 <= 6) -> FALSE!
   Continue to next d.

   Iter 5: d = 5
   - ceil(1 / 5) = 1
   - ceil(2 / 5) = 1
   - ceil(5 / 5) = 1
   - ceil(9 / 5) = 2
   Total Sum = 1 + 1 + 1 + 2 = 5
   Check: sum <= threshold (5 <= 6) -> TRUE! (Condition Satisfied!)

   Action:
     Return d = 5 immediately!
     Output: "The smallest divisor is 5"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size() aur M = max_element(nums).
     * Outer loop d = 1 se lekar M tak chalta hai (M steps in worst case).
     * Inner loop pure array ke upar traverse karta hai (N steps).
     * Total Time Complexity: O(N * M).
     * Why this is slow: Agar max element 10^6 ho aur N = 10^5 ho, toh operations 
       10^11 ho jayenge jo Time Limit Exceeded (TLE) de dega.
       (Note: Isko Binary Search on Answers se O(N * log M) me optimize kiya ja sakta hai).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard primitive variables (`d`, `sum`, `i`) 
       use hue hain. Memory completely constant hai.
======================================================================
*/

// BRUTEFORCE :-
int smallest_divisor(vector <int>&nums,int threshold){
    for(int d=1;d<*max_element(nums.begin(),nums.end());d++){
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum+=ceil((double)nums[i]/(double)d);
        }
        if(sum<=threshold){
            return d;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={1,2,5,9};
    int threshold=6;
    int divisor=smallest_divisor(nums,threshold);
    cout<<"The smallest divisor is "<<divisor;
    return 0;
}

/*
Rason of d ranging from 1 to max(nums) :-
kyuki 0, negative integers ho nahi sakte
1 se shuru karunga
aur pata hai ki ceil value calculate ho raha hai to agar mein d = 10000000000 bhi lelu to sum = 4{size of nums} hi aayega
isliye mein dheere dheere d ghataunga jisse ki sum ki value badhe 
aur kyuki maximum sum = 4 ho sakta hai jo ki agar mein max(nums) se divide karu to bhi aa jayega isliye d 1 -> max(nums) tak chalta hai
*/