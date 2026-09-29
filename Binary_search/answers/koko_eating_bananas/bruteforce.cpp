#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (KOKO EATING BANANAS - BRUTE FORCE):
   - Problem:
     Hume ek array `nums` diya hai jisme har pile me kitne bananas hain wo likha hai.
     Ek integer `hours_given` (h) diya hai.
     Koko ko ek aisi MINIMUM eating speed `k` (bananas per hour) decide karni hai 
     taaki wo saare bananas `hours_given` ke andar ya barabar time me khatam kar sake.
     Rule: Ek ghante me Koko sirf ek pile se kha sakti hai. Agar pile me speed `k` se kam 
     bananas hain, toh bhi wo bacha hua ghanta aaram karegi (agli pile shuru nahi karegi).
     Iska matlab har pile ko khatam karne me `ceil(nums[i] / k)` ghante lagenge.

   - Brute Force Search Space:
     - Minimum speed kya ho sakti hai? `1` banana per hour (0 banana khane se kabhi khatam nahi hoga).
     - Maximum speed ki zaroorat kitni ho sakti hai? `max_element(nums)`.
       Kyunki agar Koko ek ghante me sabse badi pile ke barabar banana kha sakti hai, 
       toh har pile theek 1 ghante me khatam ho jayegi (total time = array ka size).
       Isse tez speed lene ka koi faida nahi kyunki ek ghante me wo ek hi pile kha sakti hai!
     - Range: `1` se lekar `max(nums)`.
     - Hum speed `i = 1` se test karna shuru karte hain:
       - Speed badhegi -> Total hours kam lagenge (Monotonic relation).
       - Jaise hi pehli aisi speed `i` milegi jisme `hours_taken <= hours_given`, 
         wahi minimum required speed hogi!

   - Edge Case (`hours_given < nums.size()`):
     Har pile ko kam se kam 1 ghanta lagna hi lagna hai chahe Koko ki speed 1000 bananas/hr kyu na ho.
     Agar total piles = 5 hain, toh minimum 5 ghante chahiye hi chahiye.
     Agar `hours_given = 4` diya ho, toh Koko chahe kitni bhi tez khaye, 
     wo 4 ghante me 5 alag-alag piles kabhi khatam nahi kar sakti!
     Isliye seedhe -1 return karke early exit kar jao.

   - Missing Return Guard in Code:
     Function ke end me ek default fallback return (jaise `return -1;`) hona zaroori hota hai 
     taaki control end tak bina return ke na pahuche (compiler warning se bachne ke liye).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `total_hours(nums, banana_per_hour)` ---
   - `int sum = 0;` : Current speed par lagne wale total ghante count karne ke liye.
   - `sum += ceil(double(nums[i]) / double(banana_per_hour));` :
     Har pile ke liye lagne wale ghante nikal kar add kiya.
     Example: Agar pile me 7 bananas hain aur speed 3 hai, toh `ceil(7 / 3) = 3` ghante lagenge.
   - `return sum;` : Total hours return kiya.

   --- `banana_eat_rate(nums, hours_given)` ---
   - `if (hours_given < nums.size()) return -1;` :
     Impossible case check. Piles ki sankhya se kam ghante diye hain toh task namumkin hai.
   - `for(int i = 1; i <= *max_element(nums.begin(), nums.end()); i++)` :
     Speed ko 1 se badha kar maximum pile size tak linearly check kar rahe hain.
   - `int hours_taken = total_hours(nums, i);` :
     Current speed `i` par total kitna time lagega wo calculate kiya.
   - `if (hours_taken <= hours_given) return i;` :
     Kyunki hum `i = 1` se start kar rahe hain, jo pehli speed deadline meet karegi 
     wahi humari MINIMUM speed hogi! Turant return karo.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [3, 4, 7, 9, 12], hours_given = 11
   nums.size() = 5
   Max element = 12
   Check: hours_given (11) < nums.size() (5) -> False (Possible, continue)

   -------------------------------------------------------------------
   Iter 1: Speed i = 1
   - ceil(3/1) = 3
   - ceil(4/1) = 4
   - ceil(7/1) = 7
   - ceil(9/1) = 9
   - ceil(12/1) = 12
   Total Hours = 3 + 4 + 7 + 9 + 12 = 35
   Check: 35 <= 11 -> False. Next speed.

   Iter 2: Speed i = 2
   - ceil(3/2) = 2
   - ceil(4/2) = 2
   - ceil(7/2) = 4
   - ceil(9/2) = 5
   - ceil(12/2) = 6
   Total Hours = 2 + 2 + 4 + 5 + 6 = 19
   Check: 19 <= 11 -> False. Next speed.

   Iter 3: Speed i = 3
   - ceil(3/3) = 1
   - ceil(4/3) = 2
   - ceil(7/3) = 3
   - ceil(9/3) = 3
   - ceil(12/3) = 4
   Total Hours = 1 + 2 + 3 + 3 + 4 = 13
   Check: 13 <= 11 -> False. Next speed.

   Iter 4: Speed i = 4
   - ceil(3/4) = 1
   - ceil(4/4) = 1
   - ceil(7/4) = 2
   - ceil(9/4) = 3
   - ceil(12/4) = 3
   Total Hours = 1 + 1 + 2 + 3 + 3 = 10
   Check: 10 <= 11 -> TRUE! (Condition Satisfied!)

   Action:
     Return i = 4 immediately!
     Output: "The minimum value is 4"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size() aur M = max_element(nums).
     * Outer loop `i` 1 se lekar M tak chalta hai (M steps in worst case).
     * Har iteration me `total_hours()` pure array par iterate karta hai (N steps).
     * Total Time Complexity: O(N * M).
     * Note on limitation: Agar array me pile ka size 10^9 ho (jaise LeetCode 875 me hota hai), 
       toh 10^9 * N operations Time Limit Exceeded (TLE) de denge.
       (Isliye isko Binary Search on Answers se O(N * log M) me convert karna padta hai).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard scalar variables 
       (`sum`, `i`, `hours_taken`) use hue hain. Extra memory bilkul constant hai.
======================================================================
*/

int total_hours(vector <int> &nums, int banana_per_hour){
    int sum = 0;
    for(int i = 0;i < nums.size();i++){
        sum += ceil(double(nums[i])/double(banana_per_hour));
    }
    return sum;
}

int banana_eat_rate(vector <int> &nums, int hours_given){
    
    if(hours_given < nums.size()){    // wo case jaha mien chk karta hu ki agar 100 bananna/hr bhi khaye to bhi 5 hours to lagenge hi lekin agar hours_given hi 4 hrs ho to direct -1 return kar de na ki pure code run ho
        return -1;
    }

    for(int i = 1; i <= *max_element(nums.begin(), nums.end());i++){
        int hours_taken = total_hours(nums, i);
        if(hours_taken <= hours_given){
            return i;
        }
    }
}

int main(){
    vector <int> nums={3,4,7,9,12};
    int hours;
    cout<<"Enter hours :- ";
    cin>>hours;
    int ans=banana_eat_rate(nums,hours);
    cout<<"The minimum  value is "<<ans;
    return 0;
}