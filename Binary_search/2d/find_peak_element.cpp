#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIND A PEAK ELEMENT II - 2D MATRIX):
   - Problem:
     Hume ek N x M 2D matrix di gayi hai. Hume koi bhi ek "Peak Element" 
     ka coordinate {row, col} return karna hai.
     Peak element ka matlab: aisa cell jo apne chaaro neighbors 
     (top, bottom, left, right) se strictly bada ho.
     Matrix boundaries ke bahar imaginary -1 maana jata hai.

   - Brute Force Se Better Sochna:
     Brute force me har cell ke chaaro neighbors check karne me O(N * M) lagta hai.
     Lekin 1D Peak Element me hum binary search lagate the O(log N) me. 
     Kya 2D matrix me bhi Binary Search lag sakta hai?
     Haan! Hum COLUMNS par Binary Search lagayenge!

   - The Masterstroke Intuition (Find Max of Column):
     1. Hum columns par binary search karte hain (low = 0, high = m - 1).
     2. Middle column 'mid' chuno.
     3. Middle column 'mid' ka SABSE BADA element (Global Maximum of that column) dhundho:
        Maan lo wo row 'max_row_index' par milta hai.
     4. KYUN COLUMN KA MAXIMUM HI CHUNA?
        Kyunki wo cell already apne column ka sabse bada number hai, 
        toh wo apne TOP aur BOTTOM neighbors se AUTOMATICALLY BADA HO GAYA!
        Ab hume top aur bottom check karne ki zaroorat hi nahi bachi!
     5. Ab sirf 2 neighbors bache check karne ko: LEFT aur RIGHT!
        - Agar nums[max_row_index][mid] apne left aur right dono se bada hai:
          Toh chaaro directions se bada ho gaya -> PEAK MIL GAYA!
        - Agar nums[max_row_index][mid] < left:
          Left side me koi number bada hai. Iska matlab left half me ek strictly bada 
          path exist karta hai jo aage chalkar kisi peak par terminate hoga hi hoga.
          Toh right half discard karo: high = mid - 1.
        - Agar nums[max_row_index][mid] < right:
          Right side me number bada hai, peak pakka right half me milega: low = mid + 1.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- max_index(nums, n, mid) ---
   - int max_value = INT_MIN; int maxindex = -1; :
     Middle column 'mid' ke andar traverse karke sabse bada element dhundhne ke liye.
   - for(int i = 0; i < n; i++) :
     Column 'mid' ke saare N rows scan kiye taaki column ka maximum mil sake.
   - return maxindex; :
     Us row ka index return kiya jahan column 'mid' ka largest element baitha hai.

   --- findpeak(nums) ---
   - int low = 0; int high = m - 1; :
     Columns par Binary Search ke bounds set kiye (Column 0 se Column M - 1).
   - int mid = (low + high) / 2; :
     Current search window ka middle column.
   - int max_row_index = max_index(nums, n, mid); :
     Middle column ka sabse bada element pakda. (Top & Bottom checks eliminated!).
   - int left = mid - 1 >= 0 ? nums[max_row_index][mid - 1] : -1; :
     Boundary-safe left neighbor fetch kiya. Agar col 0 par hain toh imaginary -1.
   - int right = mid + 1 < m ? nums[max_row_index][mid + 1] : -1; :
     Boundary-safe right neighbor fetch kiya. Agar last col par hain toh imaginary -1.
   - if (nums[max_row_index][mid] > left && nums[max_row_index][mid] > right) :
     Peak condition hit! Top aur bottom se pehle hi bada tha, ab left aur right se bhi bada hai. 
     Return {max_row_index, mid}.
   - else if (nums[max_row_index][mid] < left) high = mid - 1; :
     Left neighbor bada hai, peak dhoondhne left half me move karo.
   - else low = mid + 1; :
     Right neighbor bada hai, peak dhoondhne right half me move karo.
   - return {-1, -1}; :
     Matrix me hamesha peak exist karta hai, par syntax complete karne ke liye fallback.

======================================================================
3. DETAILED DRY RUN:

   Matrix (n = 4 rows, m = 5 columns):
   Col:     0    1    2    3    4
   Row 0: [ 2,   4,   6,   7,   9 ]
   Row 1: [21,  23,  25,  26,  27 ]
   Row 2: [29,  32,  33,  34,  36 ]
   Row 3: [37,  39,  40,  42,  26 ]

   Initial: low = 0, high = 4

   --- Iteration 1 ---
   low = 0, high = 4 (0 <= 4 -> True)
   mid = (0 + 4) / 2 = 2 (Column 2)

   Find max in Column 2: elements are {6, 25, 33, 40}
   Max value = 40, at row 3.
   max_row_index = 3.
   Current Cell: nums[3][2] = 40.

   Neighbors:
   - Top: nums[2][2] = 33 (40 > 33, column max hone ki wajah se guaranteed bada hai)
   - Bottom: imaginary -1 (boundary)
   - Left: nums[3][1] = 39
   - Right: nums[3][3] = 42

   Compare:
     nums[3][2] > left  => 40 > 39 -> TRUE
     nums[3][2] > right => 40 > 42 -> FALSE (Right wala bada hai!)
   
   Action:
     Right neighbor (42) bada hai, right side jao:
     low = mid + 1 = 2 + 1 = 3.
   State: low = 3, high = 4.

   --- Iteration 2 ---
   low = 3, high = 4 (3 <= 4 -> True)
   mid = (3 + 4) / 2 = 3 (Column 3)

   Find max in Column 3: elements are {7, 26, 34, 42}
   Max value = 42, at row 3.
   max_row_index = 3.
   Current Cell: nums[3][3] = 42.

   Neighbors:
   - Top: nums[2][3] = 34 (42 > 34, naturally true)
   - Bottom: imaginary -1
   - Left: nums[3][2] = 40
   - Right: nums[3][4] = 26

   Compare:
     nums[3][3] > left  => 42 > 40 -> TRUE!
     nums[3][3] > right => 42 > 26 -> TRUE!
   
   Action:
     Dono conditions TRUE! Peak mil gaya!
     return {max_row_index, mid} => return {3, 3}.
   Function terminates immediately!

   Output: "The position of peak element is (3,3)" (Value = 42, which is a valid 2D peak).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Columns par Binary Search chalta hai: O(log2 M) iterations.
     * Har iteration me max_index() function column ke saare rows scan karta hai: O(N) operations.
     * Total Time Complexity: O(N * log2 M).
     * Agar hum rows par binary search karte aur row ka max dhoondhte toh time O(M * log2 N) hota.
     * Brute Force O(N * M) ke comparison me yeh exponentially faster hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Algorithm sirf kuch scalar pointer variables (low, high, mid, max_row_index, left, right) 
       use karta hai.
     * Zero extra memory allocation.
======================================================================
*/

int max_index(vector<vector<int>> &nums,int n,int mid){     //  n :-  No. of rows
    int max_value= INT_MIN;
    int maxindex=-1;
    for(int i=0;i<n;i++){
        if(nums[i][mid]>max_value){
            max_value=nums[i][mid];
            maxindex=i;
        }
    }
    return maxindex;
}

vector <int>findpeak(vector <vector<int>> &nums){
    int n = nums.size();
    int m = nums[0].size();
    int low=0;
    int high=m-1;
    while(low<=high){
        int mid=(low+high)/2;
        int max_row_index=max_index(nums,n,mid);
        int left = mid-1 >= 0 ? nums[max_row_index][mid-1] : -1;
        int right = mid+1<m ? nums[max_row_index][mid+1] : -1;

        if(nums[max_row_index][mid] > left && nums[max_row_index][mid] > right){
            return {max_row_index,mid};
        }
        else if(nums[max_row_index][mid] < left){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return {-1,-1};
}

int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    vector <int> ans = findpeak(nums);
    cout<<"The position of peak element is ("<<ans[0]<<","<<ans[1]<<")";
    return 0;
}