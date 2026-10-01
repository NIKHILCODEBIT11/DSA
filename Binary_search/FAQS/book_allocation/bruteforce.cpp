#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BOOK ALLOCATION PROBLEM - BRUTE FORCE):
   - Problem:
     Hume `nums` array diya hai jisme books ke pages hain. Hume `assigned_student` (m) 
     students me ye saari books baantni hain.
     Rules:
     1. Har student ko kam se kam 1 book milni zaroori hai.
     2. Allocation CONTIGUOUS (lagataar) hona chahiye (e.g., student 1 ko book 0, 1 mili, 
        toh student 2 ko book 2 se hi shuru karni padegi).
     3. Objective: "Minimize the Maximum Pages Allocated".
        Matlab kisi bhi student ke paas jo pages ka bojh (load) hai, 
        us maximum bojh ko jitna ho sake utna CHHOTA (minimize) karna hai.

   - Real-Life Analogy:
     Tum ek class monitor ho aur 4 bacchon me books baant rahe ho taaki kisi bhi 
     ek bacche par bohot zyada load na aaye.
     Tum ek imaginary ceiling (limit = `pages`) tay karte ho ki "kisi bhi bacche ko 
     is limit se zyada pages nahi milenge".
     - Pehle bacche ko books dena shuru kiya jab tak uske total pages limit ke andar hain.
     - Jaise hi agli book dene se uske pages limit se bahar jayein, tum agle bacche ko 
       books dena shuru kar dete ho (`student++`).

   - Search Space Boundary Ka Exact Logic:
     1. Minimum Possible Limit (`low` = `max_element(nums)`):
        Array ki sabse moti book (highest pages) 49 pages ki hai.
        Agar hum ceiling limit 48 rakh dein, toh 49 pages wali book kisi bhi student 
        ko nahi di ja sakegi! Isliye limit kam se kam `max_element` honi hi chahiye.
     2. Maximum Possible Limit (`high` = `accumulate(nums)`):
        Agar sirf 1 hi student hota, toh saari books usi akele ko milti. 
        Us case me total load = array ka sum = 172. Isse badi limit ka koi matlab nahi.
     - Search range: `[max_element ... sum_of_elements]`.

   - CRITICAL BUG / LOGICAL FLAW IN CURRENT CODE:
     Code me check likha hai:
         `if (count_student == assigned_student) return i;`
     Yeh line kuch test cases me galat answer de sakti hai ya loop se bina return hue 
     bahar nikal sakti hai!
     Kyun?
     - Maan lo `assigned_student = 4` hai.
     - Kisi limit `i` ke liye agar `count_student <= assigned_student` aa raha hai (e.g., 2 ya 3 students me hi kaam ho gaya), 
       toh iska matlab wo limit VALID hai! Kyunki agar 2 ya 3 students me kaam ho sakta hai, 
       toh unhi partitions ko aur todkar 4 students me aasaani se baanta ja sakta hai 
       bina maximum page limit ko badhaye!
     - Isliye sahi condition hoti hai:
         `if (count_student <= assigned_student) return i;`
     - Kyunki hum `low` (sabse chhoti limit) se chalte hain, pehli baar jahan 
       `count_student <= assigned_student` satisfy ho gaya, wahi humara minimum answer hai!
     - Function ke aakhir me safe side ke liye `return low;` ya `return -1;` likhna zaroori hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `number_of_students(nums, pages)` ---
   - `int student = 1, student_pages = 0;`:
     Pehle student se distribution shuru kiya (`student = 1`), aur uska current page count 0 rakha.
   - `if (student_pages + nums[i] <= pages) student_pages += nums[i];`:
     Limit exceed nahi hui, usi current student ko agli book bhi de di.
   - `else { student += 1; student_pages = nums[i]; }`:
     Limit exceed ho gayi! Current student ka quota band, agle student ko bulaya (`student += 1`), 
     aur nayi book naye student ke account me add ki.
   - `return student;`:
     Given limit `pages` maintain karne ke liye total kitne students ki zaroorat padi.

   --- `pages(nums, assigned_student)` ---
   - `if (nums.size() < assigned_student) return -1;`:
     Agar books hi students se kam hain, toh pigeonhole principle ke hisab se kisi na kisi 
     student ko 0 books milengi, jo allowed nahi hai -> return -1.
   - `for(int i = low; i <= high; i++)`:
     Minimum possible barrier (49) se maximum possible barrier (172) tak 
     ek-ek limit linearly check ki.
   - `if (count_student <= assigned_student) return i;`:
     Pehli aisi limit milte hi return kiya jahan saari books target students me sama jayein.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [25, 46, 28, 49, 24], student = 4
   n = 5 books
   low  = max_element = 49
   high = sum = 25 + 46 + 28 + 49 + 24 = 172

   -------------------------------------------------------------------
   --- Test Limit i = 49 ---
   Call number_of_students(nums, pages = 49):
   - Book 0 (25): student 1 -> pages = 25
   - Book 1 (46): 25 + 46 = 71 > 49 -> student 2 -> pages = 46
   - Book 2 (28): 46 + 28 = 74 > 49 -> student 3 -> pages = 28
   - Book 3 (49): 28 + 49 = 77 > 49 -> student 4 -> pages = 49
   - Book 4 (24): 49 + 24 = 73 > 49 -> student 5 -> pages = 24
   Total students needed = 5.
   Check: count_student <= assigned_student (5 <= 4) -> FALSE. (49 pages ki limit par 5 bacche lag rahe hain, limit badhao)

   --- Test Limits i = 50 to 70 ---
   In sabhi limits par total students > 4 rahenge -> All FALSE.

   --- Test Limit i = 71 ---
   Call number_of_students(nums, pages = 71):
   - Book 0 (25): student 1 -> pages = 25
   - Book 1 (46): 25 + 46 = 71 <= 71 -> student 1 le sakta hai! pages = 71
   - Book 2 (28): 71 + 28 = 99 > 71 -> student 2 -> pages = 28
   - Book 3 (49): 28 + 49 = 77 > 71 -> student 3 -> pages = 49
   - Book 4 (24): 49 + 24 = 73 > 71 -> student 4 -> pages = 24
   Total students needed = 4.
   Check: count_student <= assigned_student (4 <= 4) -> TRUE!

   Allocation Breakdown at Limit 71:
     Student 1: [25, 46]     -> 71 pages
     Student 2: [28]         -> 28 pages
     Student 3: [49]         -> 49 pages
     Student 4: [24]         -> 24 pages
     Maximum pages assigned to any student = max(71, 28, 49, 24) = 71.

   Action:
     Pehli valid limit = 71 mil gayi!
     Return 71 immediately.
     Output: "The maximum number of pages assigned to any student is :- 71"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Sum = sum of all pages, Max = max pages in a single book.
     * Search space range = (Sum - Max + 1).
     * Linear loop runs: O(Sum - Max + 1) times.
     * Har step par `number_of_students()` pure array ko scan karta hai: O(N) operations.
     * Total Time Complexity: O(N * (Sum - Max + 1)).
     * For large constraints (e.g., Sum = 10^9), yeh TLE de dega.
       (Is linear search ko Binary Search on Answers se O(N * log(Sum - Max)) me optimize kiya jata hai).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf scalar variables (`student`, `student_pages`, `low`, `high`, `i`) 
       use hue hain, koi auxiliary array ya memory allocation nahi hui.
======================================================================
*/

int number_of_students(vector <int>&nums,int pages){
    int student=1, student_pages=0;
    for(int i=0;i<nums.size();i++){
        if(student_pages+nums[i]<=pages){
            student_pages+=nums[i];
        }
        else{
            student+=1;
            student_pages=nums[i];
        }
    }
    return student;
}

int pages(vector <int>&nums,int assigned_student){
    if(nums.size() < assigned_student){   // kyuki har student ko kam se kam ek book to milni hi chhiye par agar total 5 books hain lekin bacche 6 hain us case mein koi ek bacha to hoga jise koi book nahi milega us case mein ye return book allocation nahi kiya ja sakta
        return -1;
    }

    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    for(int i=low;i<=high;i++){
        int count_student=number_of_students(nums,i);
        if(count_student==assigned_student){
            return i;
        }
    }
}

int main(){
    vector <int> nums={25,46,28,49,24};
    int student=4;
    cout<<"The maximum number of pages assigned to any student is :-"<<pages(nums,student);
    return 0;
}