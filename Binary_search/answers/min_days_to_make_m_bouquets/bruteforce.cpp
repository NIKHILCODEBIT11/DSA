#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE :-        [7 7 7 7 13 11 12 7]    M(NO. OF BOUQUETS) = 2   K(ADJ FLOWERS REQ) = 3

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (MINIMUM DAYS TO MAKE M BOUQUETS - BRUTE FORCE):
   - Problem:
     Hume ek array `nums` (bloomDay) diya hai jahan `nums[i]` batata hai ki i-th flower 
     kis din bloom (khil) hoga.
     Hume `m` bouquets banane hain, aur har bouquet me `k` ADJACENT (lagataar) 
     bloomed flowers hone chahiye.
     Hume wo MINIMUM din (day) nikalna hai jab hum `m` bouquets successfully bana sakein.

   - Adjacent Flowers Ka Funda:
     Bouquet banane ke liye flowers ka bagal-bagal (contiguous) khila hona zaroori hai.
     Agar continuous chain me khile hue phool mil rahe hain, toh counter badhate jao.
     Jaise hi beech me koi phool bina khila mila (`nums[i] > days`), chain toot jati hai!
     Toh ab tak ke khile phoolon se kitne bouquets ban sakte the (`counter / k`) unhe 
     total bouquets me add karo aur counter ko 0 karke nayi chain ka wait karo.

   - Brute Force Search Space (Range of Days):
     - Minimum Possible Day: `min_element(nums)`
       Is din se pehle toh array ka ek bhi phool nahi khila hoga, toh bouquets 
       banna namumkin hai.
     - Maximum Possible Day: `max_element(nums)`
       Is din tak array ke saare ke saare phool khil chuke honge. Agar is din bhi 
       `m` bouquets nahi bane, toh aage kabhi nahi ban sakte!
     - Search range: `min_element` se lekar `max_element` tak.
     - Hum din `i = min_element` se linearly test karna shuru karte hain:
       Jaise jaise din aage badhenge, aur zyada phool khilenge (monotonic nature).
       Toh jo PEHLA din condition satisfy karega (`possible() == true`), 
       wahi humara answer (MINIMUM days) hoga!

   - Edge Case / Impossible Check (`nums.size() < (long long)m * k`):
     Agar hume `m = 2` bouquets banane hain aur har bouquet me `k = 3` phool chahiye, 
     toh total phool lagenge: m * k = 6 phool.
     Agar array ka size hi 5 ho, toh chahe hazar din beet jayein, jab total phool hi 
     kam hain toh bouquets banana namumkin hai! Isliye direct `-1` return karo.
     *(Warning: Production/LeetCode me `m * k` karte waqt integer overflow se bachne 
     ke liye `(long long)m * k` use karna zaroori hai).*

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `possible(nums, days, m, k)` ---
   - `int no_of_bouquet = 0, counter = 0;`:
     `counter` consecutive khile hue flowers ginta hai, aur `no_of_bouquet` 
     total bane hue bouquets track karta hai.
   - `if (nums[i] <= days) counter++;`:
     Phool target din tak khil chuka hai, continuous chain lambi hui.
   - `else { no_of_bouquet += counter / k; counter = 0; }`:
     Chain toot gayi! Current chain se bane bouquets count kiye (`counter / k`) 
     aur consecutive counter reset kiya.
   - `no_of_bouquet += counter / k;` (After Loop):
     Array khatam hone par jo aakhri chain bach gayi thi, uske bouquets add kiye.
   - `return no_of_bouquet >= m;`:
     Check kiya ki kya required bouquets ban paye ya nahi.

   --- `min_and_max(nums)` ---
   - Array ko scan karke minimum day aur maximum day ka pair return karta hai 
     taaki search boundary tay ho sake.

   --- `final_days(nums, m, k)` ---
   - `if (nums.size() < m * k) return -1;`:
     Early exit check: total flowers hi kam hain toh answer exist nahi karta.
   - `for(int i = min_max.first; i <= min_max.second; i++)`:
     Minimum blooming day se lekar maximum blooming day tak ek-ek din linearly test kiya.
   - `if (possible(nums, i, m, k) == true) return i;`:
     Smallest day milte hi turant return kar diya.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [7, 7, 7, 7, 13, 11, 12, 7], m = 2, k = 3
   nums.size() = 8
   Total flowers needed = m * k = 2 * 3 = 6 <= 8 (Valid)
   min_element = 7, max_element = 13
   Search Space: days = 7 se 13 tak

   -------------------------------------------------------------------
   --- Test Day = 7 ---
   Call: possible(nums, days = 7, m = 2, k = 3)
   Array Bloom Status on Day 7:
   - i=0: nums[0]=7 <= 7 -> Bloomed! counter = 1
   - i=1: nums[1]=7 <= 7 -> Bloomed! counter = 2
   - i=2: nums[2]=7 <= 7 -> Bloomed! counter = 3
   - i=3: nums[3]=7 <= 7 -> Bloomed! counter = 4
   - i=4: nums[4]=13 > 7 -> NOT bloomed! Chain breaks!
          no_of_bouquet += counter / k = 4 / 3 = 1 bouquet ban gaya.
          counter reset = 0.
   - i=5: nums[5]=11 > 7 -> NOT bloomed! counter = 0
   - i=6: nums[6]=12 > 7 -> NOT bloomed! counter = 0
   - i=7: nums[7]=7 <= 7 -> Bloomed! counter = 1
   Loop ends.
   After loop: no_of_bouquet += counter / k = 1 / 3 = 0.
   Total bouquets formed on Day 7 = 1.
   Check: no_of_bouquet >= m (1 >= 2) -> FALSE!
   Day 7 is not enough.

   --- Test Day = 8, 9, 10, 11 ---
   Day 8, 9, 10 par status Day 7 jaisa hi rahega (Total = 1 bouquet) -> False.
   Day 11 par nums[5] khilega, par nums[4]=13 aur nums[6]=12 band hain, 
   toh koi naya adjacent group of 3 nahi banega -> False.

   --- Test Day = 12 ---
   Call: possible(nums, days = 12, m = 2, k = 3)
   Array Bloom Status on Day 12:
   - i=0 to 3: nums[0..3]=7 <= 12 -> 4 bloomed.
   - i=4: nums[4]=13 > 12 -> Chain breaks!
          no_of_bouquet += 4 / 3 = 1 bouquet. counter = 0.
   - i=5: nums[5]=11 <= 12 -> Bloomed! counter = 1.
   - i=6: nums[6]=12 <= 12 -> Bloomed! counter = 2.
   - i=7: nums[7]=7 <= 12  -> Bloomed! counter = 3.
   Loop ends.
   After loop: no_of_bouquet += counter / k = 3 / 3 = 1 bouquet.
   Total bouquets formed on Day 12 = 1 + 1 = 2 bouquets!
   Check: no_of_bouquet >= m (2 >= 2) -> TRUE!

   Action:
     Pehla valid day = 12 mil gaya!
     Return 12 immediately.
     Output: "The minimum no of days are 12"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Min = min_element(nums), Max = max_element(nums).
     * Range of days = (Max - Min + 1).
     * Outer loop is range par linearly travel karta hai: O(Max - Min + 1) steps.
     * Har step par `possible()` function pure array par iterate karta hai: O(N) steps.
     * Total Time Complexity: O(N * (Max - Min + 1)).
     * Worst case me agar Min = 1 aur Max = 10^9 ho, toh operations 10^9 * N 
       ho jayenge jo Time Limit Exceeded (TLE) de dega.
       (Isliye isko Binary Search on Answers se O(N * log(Max - Min)) me optimize karte hain).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard loop aur counter variables 
       (`no_of_bouquet`, `counter`, `min`, `max`, `i`) use hue hain. 
       Extra memory bilkul constant hai.
======================================================================
*/

bool possible(vector <int> &nums,int days,int m,int k){   // ye part decide karta hai ki selected "days" ke liye kya "m" no. of bouquets ban sakte hain
    int no_of_bouquet=0,counter=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]<=days){
            counter++;
        }else{
            no_of_bouquet+=counter/k;
            counter=0;
        }
    }
    no_of_bouquet+=counter/k;
    if(no_of_bouquet>=m){
        return true;
    }
    else{
        return false;
    }
}

pair <int,int> min_and_max(vector <int> &nums){   // ye "nums" array mein min and max nikalta hai 
    int min=INT_MAX,max=INT_MIN;  
    for(int i=0;i<nums.size();i++){
        if(nums[i]<min){
            min=nums[i];
        }
        if(nums[i]>max){
            max=nums[i];
        }
    }
    return {min,max};
}

int final_days(vector <int> &nums,int m,int k){    //ye us "i" ko return karta hai jo ki days represent karta hai jisme ki "m" no. of bouquets ban jaye with "k" adjacent flowers
    auto min_max=min_and_max(nums);
    if(nums.size()<m*k){    // agar "nums" mein 4 element hain matlab 4 flowers jo ki kisi kisi din bloom ho rahe hain lekin agar mujhe "m=3" bouquet banana hai with "k=2" yaano bouquet mein 2  adjacent flowers ho us caes men total flowers jo mujhe chahiye wo honge "m*k" = 6 par nums mein flowers hi 4 hain to ye to kabhi ho hi nahi sakta
        return -1;
    }
    for(int i=min_max.first;i<=min_max.second;i++){
        if(possible(nums,i,m,k)==true){
            return i;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={7,7,7,7,13,11,12,7};
    int m=2,k=3;
    cout<<"The minimum no of days are "<<final_days(nums,m,k);
    return 0;
}