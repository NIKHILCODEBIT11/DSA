#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIND PEAK IN MULTIPLE PEAKS ARRAY):
   - Problem:
     Array me multiple peaks (chotiyan) ho sakti hain (e.g., [1, 5, 1, 2, 1] jahan 5 aur 2 dono peak hain).
     Hume koi BHI EK peak element return karna hai.

   - The 4 Possible Shapes for `mid`:
     Kisi bhi middle element par sirf 4 cases ban sakte hain:
     Case 1: `nums[mid] > nums[mid - 1]` && `nums[mid] > nums[mid + 1]` -> PEAK (Found)!
     Case 2: `nums[mid] > nums[mid - 1]` && `nums[mid] < nums[mid + 1]` -> Increasing slope -> Peak RIGHT me guaranteed hai.
     Case 3: `nums[mid] < nums[mid - 1]` && `nums[mid] > nums[mid + 1]` -> Decreasing slope -> Peak LEFT me guaranteed hai.
     Case 4: `nums[mid] < nums[mid - 1]` && `nums[mid] < nums[mid + 1]` -> Trough/Gaddha (Local Minima)!

   - Point 1 & Point 2 Ka Logic (Trough / Multiple Peaks Decision):
     Case 4 (Trough/Local Minima) me left neighbor bhi bada hai aur right neighbor bhi bada hai:
       `nums[mid - 1] > nums[mid] < nums[mid + 1]`
     Iska matlab:
     - Left side bhi slope upar chadh raha hai -> Left me at least 1 peak GUARANTEED hai.
     - Right side bhi slope upar chadh raha hai -> Right me at least 1 peak GUARANTEED hai.
     Kyunki hume koi BHI EK peak chahiye, hum left jayein (`high = mid - 1`) ya 
     right jayein (`low = mid + 1`), dono 100% correct hain!

   - Code Simplification:
     Code me Case 3 (`nums[mid] < nums[mid - 1]`) ke baad bache hue dono cases:
       - Increasing slope (`nums[mid] < nums[mid + 1]`)
       - Trough (`nums[mid] < nums[mid - 1]` wala part pehle hi filter ho chuka hai)
     Dono me right side jana valid hai. Isliye:
         else if (nums[mid] < nums[mid + 1]) low = mid + 1;
         else low = mid + 1;
     ko merge karke direct `else low = mid + 1;` likhna 100% safe aur standard hai!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n == 1) return nums[0];`:
     1 element array me wahi self-peak hai.
   - `if (nums[0] > nums[1]) return nums[0];`:
     Agar array downward slope se shuru ho raha hai, toh 0th index hi peak hai.
   - `if (nums[n - 1] > nums[n - 2]) return nums[n - 1];`:
     Agar array aakhir tak upward ja raha hai, toh last index peak hai.
   - `int low = 1, high = n - 2;`:
     Search space ko internal elements tak limit kiya taaki `mid - 1` aur `mid + 1` 
     kabhi out-of-bounds error na dein.
   - `if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) return nums[mid];`:
     Peak mil gaya! Function exits.
   - `else if (nums[mid] < nums[mid - 1]) high = mid - 1;`:
     Left neighbor bada hai, decreasing slope par hain, left half me guaranteed peak hai -> Left jao.
   - `else`:
     Chahe increasing slope ho ya local minima (trough), right side me peak guaranteed exist 
     karegi hi karegi -> `low = mid + 1`.

======================================================================
3. DETAILED DRY RUN:

   Input (Multiple Peaks Case):
   Indices:  0   1   2   3   4   5   6
   nums:    [1,  5,  2,  1,  6,  7,  3]
   Here, peak 1 is at index 1 (val 5), peak 2 is at index 5 (val 7).
   n = 7

   --- Boundary Checks ---
   nums[0] > nums[1] (1 > 5) -> False
   nums[6] > nums[5] (3 > 7) -> False
   Safe range: low = 1, high = n - 2 = 5

   --- Iteration 1 (Hit on Trough / Gaddha) ---
   low = 1, high = 5
   mid = 1 + (5 - 1) / 2 = 3
   nums[mid] = nums[3] = 1

   Neighbors of mid:
     Left  : nums[2] = 2
     Right : nums[4] = 6

   Checks:
     1. nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
        1 > 2 && 1 > 6 -> FALSE.
     2. nums[mid] < nums[mid - 1]
        1 < 2 -> TRUE!
   Action:
     Decreasing side se left move kiya:
     high = mid - 1 = 3 - 1 = 2.
   State updated: low = 1, high = 2.

   --- Iteration 2 ---
   low = 1, high = 2
   mid = 1 + (2 - 1) / 2 = 1
   nums[mid] = nums[1] = 5

   Neighbors of mid:
     Left  : nums[0] = 1
     Right : nums[2] = 2

   Checks:
     1. nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
        5 > 1 (True) && 5 > 2 (True) -> TRUE!
   Action:
     Peak found!
     Return nums[1] => return 5.

   Notice: Agar Iteration 1 me trough par right jate (`low = mid + 1`),
   toh agle steps me 7 mil jata (jo ki doosra valid peak tha). 
   Dono directions valid result deti hain!

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Array boundaries peak hon ya first mid peak nikal jaye.
     * Worst Case: O(log2 N) -> Multiple peaks hone ke bawajood binary search 
       har step par search range ko exactly half kar deta hai.
     * Average Case: O(log2 N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer pointers (`n`, `low`, `high`, `mid`) 
       use hue hain. No extra memory overhead.
======================================================================
*/

int multiple_peak(vector <int> &nums){
    int n = nums.size();

    // for single element array 
    if(n == 1){
        return nums[0]; 
    }
    
    // checking for 0th index element or first element
    if(nums[0] > nums[1]){
        return nums[0];
    }

    // checking for (n-1)th index element or last element
    if(nums[n - 1] > nums[n - 2]){
        return nums[n - 1];
    }

    int low = 1;
    int high = n - 2;

    while(low <= high){
        int mid = low + (high - low)/2;
        
        // checking if mid is the peak :-
        if(nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]){
            return nums[mid];
        }

        else if(nums[mid] < nums[mid - 1]){
            high = mid - 1;
        }

        else if(nums[mid] < nums[mid + 1]){   // 1. for multiple peak isko mein hata ke niche wala else rakh sakta hu
            low = mid + 1;
        }

        else{                   
            low = mid + 1;    // 2. iske badle mein high = mid - 1 bhi likh sakta tha
        }
    }

    return - 1;   // ye kabhi bhi execute nahi hoga kyuki har baar ek peak element to kam se kam hoga hi aur is ode mein deal hi single peak se kar raha hu, agar array ke andar nahi hoga to obviously index 0 ya n-1 wala koi zarur peak hoga

}

int main(){
    vector <int> nums = {1,5,1,2,1};
    cout<<"The peak element is "<<multiple_peak(nums);
    return 0;
}

/*
   ============================= PEAK ELEMENT INTUITION =============================
   
   Values ^
          |                 PEAK 1                PEAK 2              PEAK 3
          |                   /\                    /\                  /\
          |                  /  \                  /  \   [mid on]     /  \
          |                 /    \                /    \  slope \     /    \
          |                /      \              /      \        \   /      \
          |               /        \            /        \        \ /        \
          |              /          \          /          \        V          \
          |             /            \  [mid] /            \                   \
          |            /              \  in  /              \                   \
          |           /                \vall/                                    \
          |          /                  \ey/                                      \
          |         /                    \/                                        \
          |        /                                                                \
          |     [low]                                                              [high]
          +---------------------------------------------------------------------------------> Indices
   
   ================================ LOGIC SUMMARY ================================
   
   1. Case 1: nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
      ==> PEAK FOUND! (return mid)

   2. Case 2: nums[mid] < nums[mid-1]   (Decreasing slope)
      ==> Left side peak pakka exist karti hai.
      ==> Action: high = mid - 1;

   3. Case 3: nums[mid] < nums[mid+1]   (Increasing slope)
      ==> Right side peak pakka exist karti hai.
      ==> Action: low = mid + 1;

   4. Case 4: VALLEY CASE (nums[mid] < nums[mid-1] && nums[mid] < nums[mid+1])
      ==> Left aur Right DONO taraf peak exist karti hai!
      ==> Tu chahe 'low = mid + 1' kar ya 'high = mid - 1', dono 100% correct hain.
      ==> Hence, Case 3 and Case 4 can be merged into a single 'else { low = mid + 1; }'
   ================================================================================
*/