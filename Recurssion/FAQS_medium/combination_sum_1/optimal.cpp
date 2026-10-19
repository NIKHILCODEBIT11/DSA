#include<bits/stdc++.h>
using namespace std;

// isme hamesha unique elements wale hi array liya gaya tha leetcode pe [1,2,3] jaisa naa ki [1,1,1] jaisa
/*
combinaions mein order matter nahi karta lekin :-
yaha arr = [2,3,6,7] ke liye sum = 7 aane wale combinations hain
2 2 3
2 3 2 
3 2 2
7

lekin kyuki ham index ko aage hi badha rahe isliye kabhi bhi 3 ke baad 2 aane ka chance hi nahi ban raha
isliye output aat hai 
2 2 3
7
*/

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (COMBINATION SUM - LEETCODE 39):
   - Problem:
     Hume distinct positive integers ki ek array 'arr' di gayi hai aur ek 'target'.
     Hume wo saare unique combinations dhoondhne hain jinka sum 'target' ke barabar ho.
     Twist: Kisi bhi element ko UNLIMITED times (kitni bhi baar) choose kar sakte hain.

   - Key Recursion Insight (Pick / Not-Pick with Infinite Supply):
     Normal Subsequence me Pick karne par hum 'index + 1' par chale jaate the
     kyunki har element sirf ek baar use ho sakta tha.
     
     Yahan:
     1. PICK CHOICE:
        - Agar current element target se chhota ya barabar hai (arr[index] <= target):
          * Usko vector 'ds' me push karo.
          * RECURSIVE CALL: Agle call me index ko 'index' hi rehne do (index + 1 nahi!).
            Target ko ghatakar 'target - arr[index]' kar do.
            Isse recursion usi element ko dubara explore kar sakega jab tak wo valid hai.
          * BACKTRACK: ds.pop_back() karke us element ko hatao taaki doosri branch explore ho sake.
          
     2. NOT-PICK CHOICE:
        - Current element ko chhod do aur aage badho.
        - RECURSIVE CALL: Agle index par jao (index + 1).
        - Target waisa ka waisa pass hoga (target change nahi hoga).

   - Base Case:
     - Jab `index == n` ho jaye (saare elements traverse ho gaye):
       * Check karo: kya `target == 0` bana?
         - Agar haan -> `result.push_back(ds)` (valid combination mil gaya).
       * HAMESHA `return;` karo taaki stack frame safely pop ho aur out-of-bounds access na ho.

======================================================================
2. CODE IMPLEMENTATION WITH INLINE COMMENTS:
*/

#include<bits/stdc++.h>
using namespace std;

void combination_sum(int index, vector<int> &arr, int n, vector<int> &ds, int target, vector<vector<int>> &result){

    // Base Case: Saare indices exhaust ho chuke hain
    if(index == n){
        // Agar target exactly 0 bacha, matlab elements ka sum target ke barabar ho gaya
        if(target == 0){
            result.push_back(ds);
        }
        // Chahe target 0 bana ho ya na bana ho, array khatam ho chuki hai, toh return karna mandatory hai
        return;
    }

    // CHOICE 1: PICK ELEMENT
    // Sirf tabhi pick kar sakte hain agar current value target se badi na ho
    if(arr[index] <= target){
        ds.push_back(arr[index]); // Jhole me element daala
        
        // CRITICAL LINE: index wahi ka wahi (index) pass kiya, taaki same element dubara reuse ho sake
        combination_sum(index, arr, n, ds, target - arr[index], result);
        
        ds.pop_back(); // Backtrack: state restore kiya taaki Not-Pick branch clean run ho
    }

    // CHOICE 2: NOT-PICK ELEMENT
    // Is element se man bhar gaya / skip kar diya, ab agle counter (index + 1) par badho
    // Yahan target me koi subtraction nahi hoga kyunki humne element nahi liya
    combination_sum(index + 1, arr, n, ds, target, result);
}

int main(){
    vector <int> arr = {1,1,1};
    int target = 2;
    vector <int> ds;
    vector <vector<int>> result;

    combination_sum(0, arr, arr.size(), ds, target, result);
    for(auto ans : result){
    cout << "[ ";
    for(auto num : ans){
        cout << num << " ";
    }
    cout << "] ";
    
    }

    return 0;
}

/*
======================================================================
3. DRY RUN (arr = {2, 3, 6, 7}, target = 7):

   Level 0: index=0 (val=2), target=7
   ├── Pick 2 -> ds=[2], target=5, call F(index=0, target=5)
   │   ├── Pick 2 -> ds=[2, 2], target=3, call F(index=0, target=3)
   │   │   ├── Pick 2 -> ds=[2, 2, 2], target=1, call F(index=0, target=1)
   │   │   │   ├── arr[0]=2 <= 1 (False, pick nahi ho sakta)
   │   │   │   └── Not-pick 2 -> call F(index=1 (val=3), target=1)
   │   │   │       └── arr[1]=3 <= 1 (False) -> ... aage badhkar index=4 par target!=0 -> return
   │   │   └── Not-pick 2 -> call F(index=1 (val=3), target=3)
   │   │       ├── Pick 3 -> ds=[2, 2, 3], target=0, call F(index=1, target=0)
   │   │       │   └── arr[1]=3 <= 0 (False) -> Not-pick ... -> index=4, target==0 -> MATCH! Push [2, 2, 3]
   │   │       └── Backtrack...
   └── ...
   Right Branch: index=3 (val=7), target=7
   └── Pick 7 -> ds=[7], target=0 -> MATCH! Push [7]

   Final Result: [2, 2, 3], [7]

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity: O(2^t * k)
     Jahan 't' = target / (minimum element in arr). Minimum element ko maximum baar pick karne se
     recursion tree ki depth banegi (jaise 7 / 2 = 3.5 calls).
     'k' = average length of combination jo 'result' vector me copy hoti hai.
   - Space Complexity: O(k) auxiliary recursion stack space and buffer vector 'ds'.
======================================================================
*/



/*
input :- arr = [1,1,1] target = 2

output :-
[ 1 1 ] [ 1 1 ] [ 1 1 ] [ 1 1 ] [ 1 1 ] [ 1 1 ] 

yaha pe is tarike se bana hai :-

index 0 and index 0 -> [1,1]
index 1 and inex 1 -> [1,1]
index 2 and index 2 -> [1,1]
index 0 and index 1 -> [1,1]
index 0 and index 2 -> [1,1]
index 1 and index 2 -> [1,1]

kabhi bhi index (i+1) and index i se [1,1] nahi bana kyuki index aage hi badh raha
*/