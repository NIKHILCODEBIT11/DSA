#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BINARY SEARCH ON ANSWERS):
   - Problem:
     Hume ek array `nums` aur ek integer `threshold` diya gaya hai.
     Hume ek aisa SMALLEST divisor `d` dhundhna hai jisse array ke har element 
     ko divide karke ceiling lene par unka total sum `<= threshold` ho.

   - Monotonic Search Space (Binary Search kyun lagega?):
     Divisor `d` ki possible values 1 se lekar max(nums) ke beech lie karti hain:
     - Jab divisor `d` bohot chhota hota hai (jaise 1), toh sum bohot BADA hota hai (> threshold) -> NOT POSSIBLE (False)
     - Jaise jaise divisor `d` BADHTA hai, har term `nums[i]/d` GHATTA hai, 
       isliye total sum bhi GHATTA hai!
     - Ek point par sum pehli baar `<= threshold` ban jata hai -> POSSIBLE (True)
     - Uske baad divisor ko aur aage badhaoge toh sum aur chhota hi hoga, 
       matlab wo saare divisors bhi condition satisfy karenge -> ALL POSSIBLE (True)

     Pattern of validity across search space [1 ... max(nums)]:
         d:        1       2       3    ...    k      k+1    ...   max(nums)
         Valid?  [False,  False,  False, ...  True,   True,  ...     True   ]
     
     Hume pehla (SMALLEST) `d` chahiye jahan validity `True` banti hai.
     Kyunki pattern monotonically False se True switch ho raha hai, hum 
     Linear Search (O(M)) ki jagah Binary Search (O(log M)) laga sakte hain!

   - Edge Case / Impossible Check (`min_sum > threshold`):
     Jab hum divisor `d = max(nums)` lete hain, toh har element divide hokar 
     ceil value 1 ban jayega (kyunki koi bhi element max se bada nahi hai).
     Toh array ka MINIMUM POSSIBLE SUM hota hai:
         min_sum = 1 * nums.size() = nums.size()
     Agar yeh minimum sum bhi threshold se bada ho gaya (`nums.size() > threshold`), 
     toh duniya ka koi bhi divisor sum ko threshold ke barabar ya chhota nahi kar sakta!
     Isliye seedhe -1 return kar do.

   - The Polarity Switch (Why returning `low` works):
     - `low` shuru hota hai NOT POSSIBLE zone me (False side).
     - `high` shuru hota hai POSSIBLE zone me (True side).
     - Whenever condition is True (`sum <= threshold`):
       Answer mil gaya, par hume chhota divisor chahiye, toh hum left me shrink karte hain:
       `high = mid - 1`.
     - Whenever condition is False (`sum > threshold`):
       Divisor chhota hai, sum bohot bada hai, toh right jao:
       `low = mid + 1`.
     - Jab Binary Search terminate hota hai (`low > high` hone par):
       Pointers apni polarity switch kar chuke hote hain!
       `high` cross hokar last NOT POSSIBLE value par rukta hai.
       `low` aage badhkar theek first POSSIBLE value (yaani MINIMUM valid divisor) 
       par land karta hai! Isliye direct `return low;` answer de deta hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `sum_bd(nums, d)` ---
   - `int sum = 0;` : Current divisor `d` ke corresponding total ceiling sum track karne ke liye.
   - `sum += ceil((double)nums[i] / (double)d);` : Har element ko `d` se divide karke ceil add kiya.
     *(Optimization tip: Integer math bina double ke: `(nums[i] + d - 1) / d`)*
   - `return sum;` : Calculated total sum return kiya.

   --- `smallest_divisor(nums, threshold)` ---
   - `int low = 1, high = *max_element(nums.begin(), nums.end());` :
     Search boundaries set kiye (Divisor 1 se chhota nahi ho sakta aur max element se bada lene ka koi faida nahi).
   - `if (min_sum > threshold) return -1;` :
     Quick reject guard: Agar maximum divisor lagane ke baad bhi sum threshold cross kar raha hai, toh solution impossible hai.
   - `int mid = low + (high - low) / 2;` :
     Overflow-safe midpoint divisor.
   - `if (sum_bd(nums, mid) <= threshold)` -> `high = mid - 1;` :
     Mid divisor valid hai! Par hume smallest divisor chahiye, toh hum left side 
     me check karne ke liye `high` ko peeche shift karte hain.
   - `else` -> `low = mid + 1;` :
     Mid divisor par sum limit se bahar nikal gaya, isliye divisor ko badhana padega -> `low` right shift kiya.
   - `return low;` :
     Loop cross hone ke baad `low` automatically smallest valid divisor index par khada hota hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Input: nums = [1, 2, 6, 9], threshold = 7
   nums.size() = 4, max_element = 9
   Search Range: low = 1, high = 9
   min_sum check: sum_bd(nums, 9) = ceil(1/9)+ceil(2/9)+ceil(6/9)+ceil(9/9) = 1+1+1+1 = 4 <= 7 (Valid, proceed)

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 1, high = 9
   mid = 1 + (9 - 1) / 2 = 5

   Call sum_bd(nums, 5):
     ceil(1/5) = 1
     ceil(2/5) = 1
     ceil(6/5) = 2
     ceil(9/5) = 2
     sum = 1 + 1 + 2 + 2 = 6

   Check: sum <= threshold (6 <= 7) -> TRUE (POSSIBLE)
   Action:
     Candidate mil gaya, par smaller divisor dhundho -> high = mid - 1 = 4
   State: low = 1, high = 4

   --- Iteration 2 ---
   low = 1, high = 4
   mid = 1 + (4 - 1) / 2 = 2

   Call sum_bd(nums, 2):
     ceil(1/2) = 1
     ceil(2/2) = 1
     ceil(6/2) = 3
     ceil(9/2) = 5
     sum = 1 + 1 + 3 + 5 = 10

   Check: sum <= threshold (10 <= 7) -> FALSE (NOT POSSIBLE)
   Action:
     Sum bohot bada hai, divisor badhao -> low = mid + 1 = 3
   State: low = 3, high = 4

   --- Iteration 3 ---
   low = 3, high = 4
   mid = 3 + (4 - 3) / 2 = 3

   Call sum_bd(nums, 3):
     ceil(1/3) = 1
     ceil(2/3) = 1
     ceil(6/3) = 2
     ceil(9/3) = 3
     sum = 1 + 1 + 2 + 3 = 7

   Check: sum <= threshold (7 <= 7) -> TRUE (POSSIBLE)
   Action:
     Candidate mil gaya, left jao -> high = mid - 1 = 2
   State: low = 3, high = 2

   --- Loop Terminate ---
   Condition check: low <= high (3 <= 2) -> FALSE!
   Loop ends.

   Visual of Final Polarity State:
   Divisors:     1       2   |   3       4       5  ...  9
   Status:     False   False | True    True    True ... True
                         ^     ^
                        high  low
   
   high = 2 (Last False / Not Possible)
   low  = 3 (First True / Smallest Possible Divisor)

   Return low -> 3.
   Output: "The smallest divisor is 3"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size() aur M = max_element in nums.
     * Binary Search range [1, M] me traverse karta hai -> O(log2 M) iterations.
     * Har iteration me `sum_bd()` pure array par traverse karta hai -> O(N) operations.
     * Initial max_element find karne me O(N) lagta hai.
     * Total Time Complexity: O(N * log2 M).
     * Brute force O(N * M) ke muqable yeh massively fast hai (e.g., M = 10^6 ke liye 
       sirf ~20 iterations lagenge instead of 10^6).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer variables 
       (`low`, `high`, `mid`, `sum`, `i`) use hue hain. Extra memory bilkul constant hai.
======================================================================
*/


// BINARY SEARCH
int sum_bd(vector <int>&nums,int d){
    int sum=0;
    for(int i=0;i<nums.size();i++){
        sum+=ceil((double)nums[i]/(double)d);
    }
    return sum;
}

int smallest_divisor(vector <int>&nums,int threshold){
    int low=1,high=*max_element(nums.begin(),nums.end());

    int min_sum=sum_bd(nums,high);          // If the "MINIMUM SUM" possible due to max element of "nums" is greater than threshold then there will be no "smallest divisor" and so return -1
    if(min_sum  > threshold){               // Upar ke comment ka matlab hai ki as i know d ranges from 1 -> max(nums) to agar mein d = max(nums) manu aur divide karu aur agar wahi value ka sum > threshold ho jaye to uske baad mein jitna bhi piche jau yaani d ko reduce karu sum ka value badhega hi isliye d doesn't exist
        return -1;
    }
    
    while(low<=high){
        int sum=0;
        int mid=low+(high-low)/2;
        if(sum_bd(nums,mid)<=threshold){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;   // kyuki initially jab d ke liye array banaya 1 -> max_element us samay low = 1 , ...... high = 9 jaha pe low point kar raha hai > threshold pe aur high point kar raha hai < threshold pe, to jab search khatam ho jayega tab dono low, high position switch kar lenge aur low usko point karega jo ki < threshold ho aur hihg waha point karega jah > threshold ho
}

int main(){
    vector <int>nums={1,2,6,9};
    int threshold=7;
    cout<<"The smallest divisor is "<<smallest_divisor(nums,threshold);
    return 0;
}

/*

I am using Binary search for optimal answer because :-

(1) The answer lies in a continous side from which "minimum" is to be found

                    1       2       3       4       5       6       7       8       9
start   1st        low                              mid                            high'
        2nd        low     mid             high
        3rd                         low    high
                                    mid
final   4th                 high    low

HENCE,     "low"        points to the       "MINIMUM"       index and so i can return it


############################ VERY VERY IMPORTANT OBSERVATION :-

                "LOW"    and     "HIGH"     switch the    "polarity"     that means :-

                ----> "low" started with polarity of "NOT POSSIBLE"
                ----> "high" started with polarity of "POSSIBLE"

                ----> After all iterations :-
                ----> "low" switches polarity and reaches to the "POSSIBLE" (AND THAT TOO TO THE "MINIMUM" DIVISOR POLARITY)
                ----> "high" switches polarity and reaches to the "NOT POSSIBLE" 
*/