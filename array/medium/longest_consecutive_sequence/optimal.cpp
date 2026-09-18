#include<bits/stdc++.h>
using namespace std;

/*
Yaha suppose nums = {100, 102, 100, 101, 101, 4, 3, 2, 3, 2, 1, 1, 1, 2}
in sabko mein set mein daal dunga kyuki waha REPEATED ELEMENTS NAHI REH SAKTE
uske baad pure set se traverse karte huye mein waise elements khojunga jo ki starting point ho subsequence ke jisse true length of subsequence mil sake
aur agar wo element subsequence ke beech ka hua to aage us element ko chod ke aage traverse karunga

uske baad mein ek logic pe kaam karunga :-
suppose arr = [3,2,4]

case 1 :-
x = 3
---> To agar (x-1) = (3-1) = 2 arr mein exist karta hai iska matlab hai ki ----> x = 3 consecutive subsequence ka STARTING POINT NAHI HAI
---> To aage is subsequence ke elements khoj ke fayda nahi hai kyuki x beech ka element hai to true count nahi pata chalega

case 2 :-
x = 2 
----> To agar (x-1) = (2-1) = 1 arr mein exist nahi karta hai iska matlab hai ki ----> x = 2 consecutive subsequnce ka STARTING POINT HAI
----> To yaha se subseequence ke elements khojna fayda hai kyuki x = 2 hi is subsequence ka starting position hai to true length mil jayega

case 3 :-
x = 4
-----> To agar (x-1) = (4-1) = 3 arr mein exist karta hai iska matlab hai ki ----> x = 4 consecutive subsequence ka STARTING POINT NAHI HAI
---> To aage is subsequence ke elements khoj ke fayda nahi hai kyuki x beech ka element hai to true count nahi pata chalega

/*
======================================================================================
INITIAL SETUP:
Input array: nums = {100, 102, 100, 101, 101, 4, 3, 2, 3, 2, 1, 1, 1, 2}

Duplicates remove hone ke baad unordered_set me Unique Elements:
st = { 1, 2, 3, 4, 100, 101, 102 }   (Note: Hash set un-ordered hota hai)

Total unique elements = 7
Initial Variables: longest = 1
======================================================================================

PASS 1: it = 1
--------------------------------------------------------------------------------------
* Check: st.find(1 - 1) == st.end() -> st.find(0) == st.end()? 
    -> 0 set me nahi hai: TRUE! (Matlab 1 sequence ka START hai)
* Initialization: count = 1, x = 1
* While loop start:
    - Check st.find(x + 1) -> st.find(2) milta hai? YES
        count = 2, x = 2
    - Check st.find(x + 1) -> st.find(3) milta hai? YES
        count = 3, x = 3
    - Check st.find(x + 1) -> st.find(4) milta hai? YES
        count = 4, x = 4
    - Check st.find(x + 1) -> st.find(5) milta hai? NO
        While loop ends.
* Streak Mili: [1 -> 2 -> 3 -> 4] (Length = 4)
* longest = max(1, 4) = 4
* State: [it = 1, count = 4, longest = 4]

PASS 2: it = 2
--------------------------------------------------------------------------------------
* Check: st.find(2 - 1) == st.end() -> st.find(1) == st.end()? 
    -> 1 set me already maujood hai: FALSE!
* Action: 2 sequence ka start nahi hai (1 pehle hi ise count kar chuka hai).
* If-block skip ho gaya.
* State: [it = 2, longest = 4]

PASS 3: it = 3
--------------------------------------------------------------------------------------
* Check: st.find(3 - 1) == st.end() -> st.find(2) == st.end()? 
    -> 2 set me maujood hai: FALSE!
* Action: 3 start nahi hai, If-block skip ho gaya.
* State: [it = 3, longest = 4]

PASS 4: it = 4
--------------------------------------------------------------------------------------
* Check: st.find(4 - 1) == st.end() -> st.find(3) == st.end()? 
    -> 3 set me maujood hai: FALSE!
* Action: 4 start nahi hai, If-block skip ho gaya.
* State: [it = 4, longest = 4]

PASS 5: it = 100
--------------------------------------------------------------------------------------
* Check: st.find(100 - 1) == st.end() -> st.find(99) == st.end()? 
    -> 99 set me nahi hai: TRUE! (Matlab 100 sequence ka START hai)
* Initialization: count = 1, x = 100
* While loop start:
    - Check st.find(x + 1) -> st.find(101) milta hai? YES
        count = 2, x = 101
    - Check st.find(x + 1) -> st.find(102) milta hai? YES
        count = 3, x = 102
    - Check st.find(x + 1) -> st.find(103) milta hai? NO
        While loop ends.
* Streak Mili: [100 -> 101 -> 102] (Length = 3)
* longest = max(4, 3) = 4
* State: [it = 100, count = 3, longest = 4]

PASS 6: it = 101
--------------------------------------------------------------------------------------
* Check: st.find(101 - 1) == st.end() -> st.find(100) == st.end()? 
    -> 100 set me maujood hai: FALSE!
* Action: 101 start nahi hai, If-block skip ho gaya.
* State: [it = 101, longest = 4]

PASS 7: it = 102
--------------------------------------------------------------------------------------
* Check: st.find(102 - 1) == st.end() -> st.find(101) == st.end()? 
    -> 101 set me maujood hai: FALSE!
* Action: 102 start nahi hai, If-block skip ho gaya.
* State: [it = 102, longest = 4]

======================================================================================
FINAL RESULT:
Loop khatam hua. 
Total unique elements checked = 7
Sabse lambi consecutive sequence = 4  (Sequence: {1, 2, 3, 4})
Return value = 4
======================================================================================
*/

int longest_consecutive_subsequence(vector <int> &nums){
    int n = nums.size();
    if(n == 0) return 0; // Empty edge case
    int longest = 1;
    unordered_set <int> st;
    for(int i = 0;i < n;i++){
        st.insert(nums[i]);
    }

    for(int it : st){
        // if "it" is the start of the sequence :-
        if(st.find(it - 1) == st.end()){
            int count = 1;
            int x = it;
            while(st.find(x + 1) != st.end()){
                count++;
                x = x + 1;
            }
            longest = max(longest, count);
        }
    }
    return longest;
}

int main(){
    vector <int> nums = {100, 102, 100, 101, 101, 4, 3, 2, 3, 2, 1, 1, 1, 2};
    cout<<"The length of longest subsequence is "<<longest_consecutive_subsequence(nums);
    return 0;
}

/*
TC :- O(N) + O(2N) ----> First O(N) is due to putting elements from nums to set
                   ----> second_first O(N) due to traversing whole set
                   ----> second_second O(N) isloye kyuki mein sirf unhi elements se traversing kar raha hu joki sstartiing element ho jaise ki upar wale example mein {100, 101, 102} and (1,2,3,4) ----> Total 2 times 1st time for 3 and 2nd time for 4 = 7 = N

SC :- O(N) ---- . for worst case if all elements are unique and same "N" numbers are stored in st from nums
*/