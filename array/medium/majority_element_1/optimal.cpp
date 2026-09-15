/*
Suppose ek array hai :- nums = [7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5]
ab isme moore's voting algo lagayenge :-

iske liye do variable hain :-
int count = 0 {0 se initialize hoga}
int ele   {Bas initialize hua hai}

Ab traversal shurur karte hain kuch aise :-
firstly ele = nums[0] = 7
ab mein pure array mein traverse karunga aur 7 milte hi count++ karunga aur 7 ke alawa kuch bhi mila to count-- karunga
isse conclusion draw karunga 

DRY RUN :-

PASS 1 :- nums under consideration = [7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5]
ele = 7 -> 7 -> 5 -> 7 -> 5 -> 1
count = 1 -> 2 -> 1 -> 2 -> 1 -> 0

Conclusion :-
Agar 7 majority element hota to OBVIOUSLY USE n/2 se jyada baar occur karna padta jis wajah se agar no-7 wale elements aane par 7 ka counter decrase karta tab bhi wo counter 0 to nahi hota
to iska matlab hai ki is particular chote se array mein 7 to MAJORITY NAHI HAI

After pass 1 :-
nums = [7   7   5   7   5   1   5   7   5   5   7   7   5   5   5   5]
       [  done   ispecting  ]


PASS 2 :- nums under consideration = [5,7,5,5,7,7,5,5,5,5]
ele = 5 -> 7
count = 1 -> 0

Conclusion :-
Agar 5 majority element hota to OBVIOUSLY USE n/2 se jyada baar occur karna padta jis wajah se agar no 5 wale elements aane par 5 ka counter decrase karta tab bhi wo counter 0 to nahi hota
to iska matlab hai ki is particular chote se array mein 5 to MAJORITY NAHI HAI

After pass 2 :-
nums = [7   7   5   7   5   1   5   7   5   5   7   7   5   5   5   5]
       [  done   ispecting  ]   [done]


PASS 3 :- nums under consideration = [5,5,7,7,5,5,5,5]
ele = 5 -> 5 -> 7 -> 7
count = 1 -> 2 -> 1 -> 0

Conclusion :-
Agar 5 majority element hota to OBVIOUSLY USE n/2 se jyada baar occur karna padta jis wajah se agar no 5 wale elements aane par 5 ka counter decrase karta tab bhi wo counter 0 to nahi hota
to iska matlab hai ki is particular chote se array mein 5 to MAJORITY NAHI HAI

After pass 2 :-
nums = [7   7   5   7   5   1   5   7   5   5   7   7   5   5   5   5]
       [  done   ispecting  ]   [done]  [done inspect]


PASS 4 :- nums under consideration :- [5,5,5,5]
ele = 5 -> 5 -> 5 -> 5
count = 1 -> 2 -> 3 -> 4

Conclusion :-
Agar 5 majority element hota to OBVIOUSLY USE n/2 se jyada baar occur karna padta jis wajah se agar no 5 wale elements aane par 5 ka counter decrase karta tab bhi wo counter 0 to nahi hota
to iska matlab hai ki is particular chote se array mein 5 to MAJORITY NAHI HAI

After pass 2 :-
nums = [7   7   5   7   5   1   5   7   5   5   7   7   5   5   5   5]
       [  done   ispecting  ]   [done]  [done inspect]  [done inspect]


########## V.V.V.V.V IMPORTANT :-
But the above algorithm doesnt gurrantte that surely there will be a majority element BUT :-
IF AND ONLY IF "MAJORITY ELEMENT EXISTS" THEN SURELY IT WILL BE 5


REASON :- Suppose at last array part under consideration, instead of [5,5,5,5] i had [23,23,23,23]
then also count wouldn't have been 0 
lekin hume to pata hai na ki 
[7,7,5,7,5,1,5,7,5,5,7,7,23,23,23,23]
mein 23 absolutly majority element nahi hai kyuki 
occurence(23) = 4 !> n/2 = 16/2 = 8

isliye hume ye conclude tabhi karna hai ki 5 majority element hai jab hum sure ho jaye ki 5 n/2 se jyada baar occur karta hai 
*/


#include<bits/stdc++.h>
using namespace std;

int majority_element_1(vector <int> &nums){
    int n = nums.size();

    // Applying moore's voting algo :-
    int count = 0;
    int ele;
    for(int i = 0;i < n;i++){
        if(count == 0){
            ele = nums[i];
            count++;
        }
        else if(nums[i] == ele){
            count++;
        }
        else{
            count--;
        }
    }

    // Checling if the "ele" is actually the majority element :-
    int count1 = 0;
    for(int i = 0;i < n;i++){
        if(nums[i] == ele){
            count1++;
        }
    }
    if(count1 > n/2){
        return ele;
    }
    return -1;
}

int main(){
    vector <int> nums = {7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5};
    cout<<"The majority element is "<<majority_element_1(nums);
    return 0;
}

/*
TC :- O(N) + *O(N)
1st O(N) will be due to traversal of array for moore's voting algo
2nd O(N) ho bhi sakta hai nahi bhi kyuki :-
---> agar question mein diya hua hai ki majority element exist karta hai tab is second O(N) traversal ki zarurat hi nahi hogi

SC :- O(1) ---> As, no extra space is used
*/