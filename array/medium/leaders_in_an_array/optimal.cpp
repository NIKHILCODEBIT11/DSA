/*
Suppose nums = [10, 22, 12, 3, 0, 6]

EX :-
Suppose mein 12 ko consider karta hu :-
tab 12 leader hai ye tabhi pata chalega jab 12 APNE RIGHT MEIN AANE WALE SABHI NUMBERS SE BADA HO
iske liye mein :- maximum = INT_MIN consider karuunga 
aur 12 ke baad yaani [3,0,6] mein jo maximum ho usko maximum mein store kar lunga 
to agar 12 us maximum se bada hoga to automatically wo leader hoga

DRY RUN :-
ans = []
i = 5
maximum = INT_MIN

PASS 1 :-
i = 5 --->    6 > maximum{INT_MIN} ----> if condition executes
ans = [6]
maximum = 6

PASS 2 :-
i = 4 --->     0  < maximum{6}  ----> if condition fails
ans = [6]
maximum = 6

PASS 3 :-
i = 3 --->     3  < maximum{6}   ----> if condition fails
ans = [6]
maximum = 6

PASS 4 :-
i = 2 --->     12  >  maximum{6}   ----> if condition executes
ans = [6, 12]
maximum = 12

PASS 5 :-
i = 1 ---->     22 > maximum{12} ----> if condition executes
ans = [6, 12, 22]
maximum = 22

PASS 6 :-
i = 0 ---->       10 < maximum{22}----> if condition fails
ans = [6, 12, 22] 
maximum = 22

reverse(ans.begin(), ans.end())
ans = [22, 12, 6]
*/

#include<bits/stdc++.h>
using namespace std;

vector <int> leaders(vector <int> &nums){
    int n = nums.size();
    int maximum = INT_MIN;
    // int counter = 0;
    vector <int> ans;
    for(int i = n-1;i >= 0;i--){
        if(nums[i] > maximum){
            /*
            ans.insert(ans.begin() + counter, nums[i]);
            maximum = max(maximum, nums[i]);
            counter++;

            ans.push_back(nums[i]);
            maximum = max(maximum, nums[i]);


            I was doing above 2 parts and getting output as 
            Leaders are :-
            6 12 22
            because i am traversing from n-1 to 0
            */

            ans.push_back(nums[i]);
            maximum = nums[i];
            // mein maximum = max(maximum, nums[i]) use nahi kar raha kyuki if consition se ye prove ho hi gaya hai ki nums[i] jo hai wo maximum se bada hi hai to comparision ki koi zarurat hi nahi hai
        }
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

int main(){
    vector <int> nums = {10, 22, 12, 3, 0, 6};
    cout<<"Leaders are :-"<<endl;
    vector <int> ans = leaders(nums);
    for(int x : ans){
        cout<<x<<" ";
    }
    return 0;
}

/*
(Note: Commented code me jo ans.insert(ans.begin() + counter, nums[i]); tha, 
wo vector me shift operation karta hai jisse time complexity wapas O(N**2) ho jati hai. 
Isliye push_back() + reverse() hi optimal O(N) approach hai).
*/

/*
TC :- O(N) ----> As, i am traversing whole array
SC :- O(N) ----> As, in worst case nums will have all elements in descending order like :- [6,4,3,2]
*/