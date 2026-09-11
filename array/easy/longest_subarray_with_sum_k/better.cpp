#include<bits/stdc++.h>
using namespace std;

int longest_subarray_with_sum_k(vector <int> &nums, int k){
    int n = nums.size();
    long long pref_sum = 0; // Ab tak ke elements ka running total sum
    int max_len = 0;        // Longest subarray ki maximum length jo return hogi
    // Prefix sum aur unke first occurrence index ko store karne ke liye map
    // Key: prefix sum, Value: index
    unordered_map<long long, int> prefixMap;

    for(int i = 0;i < n;i++){
        // Step 1: Current element ko running sum mein add karo
        pref_sum += nums[i];

        //Agar starting se current index tak sum direct k ban gaya
        // Step 2: Direct match check karo
        // Agar array ke starting (index 0) se leke current index 'i' tak ka 
        // pura sum hi direct target 'k' ke barabar ban jaye,
        // toh subarray ki length seedha (i + 1) hogi.
        if(pref_sum == k){
            max_len = max(max_len, i+1);
        }

        //Agar re = (pref_sum - k) map mein pehle se maujood hai
        // Step 3: Math Logic -> (Remaining Prefix Sum = pref_sum - k)
        // Agar total sum 'pref_sum' hai aur aakhri part ka sum 'k' chahiye,
        // toh shuruat ke part ka sum pakka (pref_sum - k) hona chahiye.
        int rem = pref_sum - k;

        // Step 4: Map mein dhoondho ki kya 'rem' pehle kabhi dekha tha?
        // Agar find() 'end()' return NAHI karta, iska matlab 'rem' map mein mil gaya.
        if(prefixMap.find(rem) != prefixMap.end()){

            // Agar 'rem' index 'prefixMap[rem]' par bana tha,
            // toh uske theek baad wale index se leke current index 'i' tak ka sum 'k' hoga.
            // Length = Current Index - Purana Index
            int len = prefixMap[rem];    // yaha pe maine chk kiya ki agar rem present hai prefixMap pe to current index se usko subtract kar du to mujhe filhal end mein sum k hone ke subarray ka length mil jaega
            max_len = max(max_len, i - prefixMap[rem]);
        }

        // Step 5: Current prefix sum ko map mein insert karo
        // CONDITION: Map mein entry SIRF TAB karo agar yeh sum pehle se exist NA karta ho.
        // Kyun? Kyunki agar sum dobara repeat hota hai (0 ya negatives ke case mein),
        // hum index ko aage overwrite nahi karenge. 
        // Index jitna purana (leftmost) rahega, aage subarray length utni hi LONGEST milegi.
        if(prefixMap.find(pref_sum) == prefixMap.end()){
            prefixMap[pref_sum] = i;
        }
    }

    return max_len;
}

int main() {
    // Sample Input (lecture example):
    // Indices:   0  1  2  3  4  5  6  7  8  9
    // Array:   [ 1, 2, 3, 1, 1, 1, 1, 4, 2, 3 ]
    vector<int> nums = {1, 2, 3, 1, 1, 1, 1, 4, 2, 3};
    long long k = 3;

    // Subarrays with sum 3:
    // 1. [1, 2]       -> index 0 to 1 -> length 2
    // 2. [3]          -> index 2 to 2 -> length 1
    // 3. [1, 1, 1]    -> index 3 to 5 -> length 3 (MAX)
    // 4. [1, 1, 1]    -> index 4 to 6 -> length 3 (MAX)
    // 5. [3]          -> index 9 to 9 -> length 1
    // Output: 3
    cout << "Longest Subarray Length: " << longest_subarray_with_sum_k(nums, k) << endl;

    return 0;
}

/*
Time Complexity (TC):
Average Case: O(N) (agar unordered_map use kar rahe ho, kyunki lookup aur insertion average O(1) lete hain).
Worst Case: O(N^2) (agar unordered_map mein bohot saare hash collisions ho jayein, jahan lookup O(N) ban jata hai).
Agar normal map (ordered) use karoge, toh TC guaranteed O(N log N) hogi.

Space Complexity (SC):O(N) — Worst case mein array ke har element par unique prefix sum banega, toh map mein maximum N entries store hongi.
*/