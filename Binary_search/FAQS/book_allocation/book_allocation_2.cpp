#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BOOK ALLOCATION - OPTIMAL BINARY SEARCH ON ANSWERS):
   - Problem:
     Hume `nums` array me books ke pages diye hain aur `assigned_student` (m) students 
     me ye books contiguously baantni hain taaki har student ko at least 1 book mile, 
     aur kisi bhi student par jo maximum pages ka load aaye, wo MINIMIZE ho sake.

   - Monotonic Search Space:
     - Minimum possible limit (`low` = `max_element(nums)`):
       Array ki sabse moti book (49 pages) kisi na kisi student ko toh deni hi padegi.
       Agar ceiling limit 49 se kam rakhi, toh wo book kabhi allocate hi nahi ho payegi!
     - Maximum possible limit (`high` = `accumulate(nums)`):
       Agar sirf 1 hi student hota, toh saare pages (sum = 172) usi ko milte. 
       Isse badi limit lene ka koi practical sense nahi banta.
     - Search range: `[max_element ... sum_of_elements]`.

   - Monotonic Relationship & Decision Boundary:
     Jaise jaise barrier/limit `mid` BADHTI hai, ek student zyada pages rakh sakta hai, 
     isliye total students required GHAT-te hain (Monotonic function).
     
     Pattern across search space:
     Pages limit:  low ...   mid-1    mid    mid+1 ...  high
     Students:     > m ...    > m   |  <= m   <= m ...   <= m
     Valid?       False...   False  |  True   True ...   True
                                       ^
                                 (Humara target: Smallest True)

   - Polarity Shift & Return `low`:
     - Jab `number_of_students(nums, mid) > assigned_student`:
       Bacche zyada lag gaye! Limit bohot strict (chhoti) hai.
       Limit badhane ke liye right half jao: `low = mid + 1`.
     - Jab `number_of_students(nums, mid) <= assigned_student`:
       Limit sufficient hai! Lekin hume MINIMUM possible barrier chahiye,
       isliye aur chhota barrier explore karne left jao: `high = mid - 1`.
     - Loop termination (`low > high`):
       `high` rukta hai last INVALID barrier par.
       `low` theek pehle VALID (MINIMUM maximum pages) barrier par jump kar jata hai.
       Isliye seedhe `return low;` answer deta hai.

   - Note on Missing Edge Case:
     Function ke top par `if (nums.size() < assigned_student) return -1;` hona chahiye, 
     kyunki agar books bacchon se kam hon, toh allocation impossible hota hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `number_of_students(nums, pages)` ---
   - `int student = 1, student_pages = 0;`:
     Pehle student ki allocation start ki, current student ke paas 0 pages hain.
   - `if (student_pages + nums[i] <= pages) student_pages += nums[i];`:
     Current book lene se limit cross nahi ho rahi, usi student ke account me pages add kiye.
   - `else { student_pages = nums[i]; student += 1; }`:
     Limit exceed ho gayi! Current student ka quota band, naya student bulaya (`student += 1`), 
     aur nayi book naye student ke pages ban gayi.
   - `return student;`:
     Is limit par saari books baantne me total kitne students lage.

   --- `pages(nums, assigned_student)` ---
   - `int low = *max_element(...); int high = accumulate(...);`:
     Binary search boundaries set ki: lowest viable barrier se absolute maximum load tak.
   - `int mid = low + (high - low) / 2;`:
     Overflow-safe candidate barrier calculate kiya.
   - `if (number_of_students(nums, mid) > assigned_student) low = mid + 1;`:
     Students limit se zyada lag rahe hain (Invalid), limit badhao (Right jao).
   - `else high = mid - 1;`:
     Students limit ke barabar ya kam lag rahe hain (Valid), aur chhota barrier dhundho (Left jao).
   - `return low;`:
     Opposite polarity swap ke baad `low` directly minimum valid answer par rukta hai.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [25, 46, 28, 49, 24], student = 4
   low  = max_element = 49
   high = sum = 172

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 49, high = 172
   mid = 49 + (172 - 49) / 2 = 110

   Call number_of_students(nums, pages = 110):
     - Book 0 (25): s1 -> 25
     - Book 1 (46): s1 -> 25 + 46 = 71 <= 110
     - Book 2 (28): s1 -> 71 + 28 = 99 <= 110
     - Book 3 (49): 99 + 49 = 148 > 110 -> s2 -> 49
     - Book 4 (24): s2 -> 49 + 24 = 73 <= 110
     Total students needed = 2
   Check: students > assigned_student (2 > 4) -> FALSE (Valid! 2 students <= 4)
   Action: high = mid - 1 = 110 - 1 = 109
   State: low = 49, high = 109

   --- Iteration 2 ---
   low = 49, high = 109
   mid = 49 + (109 - 49) / 2 = 79

   Call number_of_students(nums, pages = 79):
     - Book 0 (25): s1 -> 25
     - Book 1 (46): s1 -> 25 + 46 = 71 <= 79
     - Book 2 (28): 71 + 28 = 99 > 79 -> s2 -> 28
     - Book 3 (49): s2 -> 28 + 49 = 77 <= 79
     - Book 4 (24): 77 + 24 = 101 > 79 -> s3 -> 24
     Total students needed = 3
   Check: students > assigned_student (3 > 4) -> FALSE (Valid!)
   Action: high = mid - 1 = 79 - 1 = 78
   State: low = 49, high = 78

   --- Iteration 3 ---
   low = 49, high = 78
   mid = 49 + (78 - 49) / 2 = 63

   Call number_of_students(nums, pages = 63):
     - Book 0 (25): s1 -> 25
     - Book 1 (46): 25 + 46 = 71 > 63 -> s2 -> 46
     - Book 2 (28): 46 + 28 = 74 > 63 -> s3 -> 28
     - Book 3 (49): 28 + 49 = 77 > 63 -> s4 -> 49
     - Book 4 (24): 49 + 24 = 73 > 63 -> s5 -> 24
     Total students needed = 5
   Check: students > assigned_student (5 > 4) -> TRUE (Students limit cross ho gayi!)
   Action: low = mid + 1 = 63 + 1 = 64
   State: low = 64, high = 78

   --- Iteration 4 ---
   low = 64, high = 78
   mid = 64 + (78 - 64) / 2 = 71

   Call number_of_students(nums, pages = 71):
     - Book 0 (25): s1 -> 25
     - Book 1 (46): s1 -> 25 + 46 = 71 <= 71
     - Book 2 (28): 71 + 28 = 99 > 71 -> s2 -> 28
     - Book 3 (49): 28 + 49 = 77 > 71 -> s3 -> 49
     - Book 4 (24): 49 + 24 = 73 > 71 -> s4 -> 24
     Total students needed = 4
   Check: students > assigned_student (4 > 4) -> FALSE (Valid!)
   Action: high = mid - 1 = 71 - 1 = 70
   State: low = 64, high = 70

   --- Iteration 5 ---
   low = 64, high = 70
   mid = 64 + (70 - 64) / 2 = 67

   Call number_of_students(nums, pages = 67):
     - Book 0, 1: 25+46 = 71 > 67 -> s1=25, s2=46
     - Book 2: 46+28 = 74 > 67 -> s3=28
     - Book 3: 28+49 = 77 > 67 -> s4=49
     - Book 4: 49+24 = 73 > 67 -> s5=24
     Total students = 5
   Check: 5 > 4 -> TRUE
   Action: low = mid + 1 = 67 + 1 = 68
   State: low = 68, high = 70

   --- Iteration 6 ---
   low = 68, high = 70
   mid = 68 + (70 - 68) / 2 = 69
   Call number_of_students(nums, pages = 69):
     Total students = 5 (> 4) -> TRUE
   Action: low = mid + 1 = 69 + 1 = 70
   State: low = 70, high = 70

   --- Iteration 7 ---
   low = 70, high = 70
   mid = 70
   Call number_of_students(nums, pages = 70):
     Book 0+1: 25 + 46 = 71 > 70 -> s1=25, s2=46...
     Total students = 5 (> 4) -> TRUE
   Action: low = mid + 1 = 70 + 1 = 71
   State: low = 71, high = 70

   --- Loop Terminate ---
   low <= high (71 <= 70) -> FALSE! Loop ends.

   Final Boundaries:
   high = 70 (Last invalid barrier jahan 5 students lag rahe the)
   low  = 71 (First valid barrier jahan 4 students me kaam ho gaya)

   Return low -> 71.
   Output: "The maximum number of pages assigned to any student is :- 71"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Sum = sum of all pages, Max = max element in nums.
     * Initial range computation: `*max_element` is O(N), `accumulate` is O(N).
     * Search space size = (Sum - Max + 1).
     * Binary search loop runs: O(log2(Sum - Max)) iterations.
     * Har iteration me `number_of_students()` N elements traverse karta hai: O(N).
     * Total Time Complexity: O(N * log2(Sum - Max)).
     * Linear search O(N * (Sum - Max)) ke muqable yeh exponentially fast hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard scalar variables (`low`, `high`, `mid`, 
       `student`, `student_pages`) use hue hain. 
       Koi extra auxiliary array, hashmap, ya recursive memory stack nahi lagti.
======================================================================
*/

int number_of_students(vector <int>&nums,int pages){
    int student=1,student_pages=0;
    for(int i=0;i<nums.size();i++){
        if(student_pages+nums[i]<=pages){
            student_pages+=nums[i];
        }
        else{
            student_pages=nums[i];
            student+=1;
        }
    }
    return student;
}

int pages(vector<int>&nums,int assigned_student){

    // added as per in explaination comment
    if(nums.size() < assigned_student){   // kyuki har student ko kam se kam ek book to milni hi chhiye par agar total 5 books hain lekin bacche 6 hain us case mein koi ek bacha to hoga jise koi book nahi milega us case mein ye return book allocation nahi kiya ja sakta
        return -1;
    }

    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    while(low<=high){
        int mid=low+(high-low)/2;
        if(number_of_students(nums,mid)>assigned_student){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return low;
}

int main(){
    vector <int> nums={25,46,28,49,24};
    int student=4;
    cout<<"The maximum number of pages assigned to any student is :-"<<pages(nums,student);
    return 0;
}