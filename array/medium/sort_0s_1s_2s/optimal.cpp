/*
It follows DUTCH-FLAG rule :-
for a given array nums = [0,1,2,0,1,2,1,2,0,0,0,1]
i will use    3 POINTER APPROACH :-
low = l
mid = m
high = h

Hamesha array ko niche dikhaya hua layout hi follow karna hai :-

0,0,0,0,0,0,1,1,1,1,........,2,2,2,2,2
^         ^ ^     ^ ^      ^ ^       ^
|         | |     | |      | |       |
0     (l-1) l (m-1) m      h h+1     n-1

upar ka layout ye bata raha hai ki 
index 0 -> low-1 tak ke saare elments mein 0 hoga ----> ye part SORTED hai
index l -> mid-1 tak ke saare elements mein 1 hoga ----> ye part SORTED hai
index mid -> high take ke saare elements mein 0/1/2 kuch bhi hoga -----> ye part UNSORTED HAI {nums}
index high+1 -> n-1 tak ke saare elements mein 2 hoga ----> ye part SORTED hai

if nums[mid] == 0 to use left sorted array mein bhejna hai so swap(nums[mid], nums[low])
kyuki tab :-
0,0,0,0,0,0,1,1,1,1,0.......,2,2,2,2,2
^         ^ ^     ^ ^      ^ ^       ^
|         | |     | |      | |       |
0     (l-1) l (m-1) m      h h+1     n-1

ye ban jayega :-
0,0,0,0,0,0,0,1,1,1,1.......,2,2,2,2,2
^         ^ ^     ^ ^      ^ ^       ^
|         | |     | |      | |       |
0     (l-1) l (m-1) m      h h+1     n-1

tab bhi dono 0s aur 1s ke part sorted hain bas low++ karna hai kyuki 0s sirf index 0 to low-1 tak hote hain aur mid++ taaki unsorted array mein aage badh saku

if nums[mid] == 1 to use left sorted array mein bhejna hai wo bi 1s ke array part mein ---> SWAP KI KOI ZARURAT HI NAHI
kyuki tab :-
0,0,0,0,0,0,1,1,1,1,1.......,2,2,2,2,2
^         ^ ^     ^ ^      ^ ^       ^
|         | |     | |      | |       |
0     (l-1) l (m-1) m      h h+1     n-1

pehle se hi SORTED HAI KYUKI 1S EK SAATH HI HAIN bas mujhe mid++ karna padega kyuki 1s sirf array ke index low-> mid-1 tak hi hain ,aur saath hi unsorted array mein bhi aage badhna hai

if nums[mid] == 2 to use right sorted array mein bhejna hai ---> swap(nums[mid], nums[high])
unsorted array -> mid to high to swap karne ke baad mid++ kyuki array mein aage badhna hai aur saath hi high-- kyuki sorted 2s index high+1 -> n-1 tak hote hain aur swap ke baad ab index high mein bhi 2 aa gaya isliye high-- karna zaroori hai
kyuki tab :-
0,0,0,0,0,0,1,1,1,1,2......0/1/2,2,2,2,2,2
^         ^ ^     ^ ^        ^   ^       ^
|         | |     | |        |   |       |
0     (l-1) l (m-1) m        h  h+1     n-1
swap(nums[mid],nums[high])
kyuki tab :-
0,0,0,0,0,0,1,1,1,1,0/1/2......2,2,2,2,2,2,2
^         ^ ^     ^   ^        ^ ^         ^
|         | |     |   |        | |         |
0     (l-1) l (m-1)   m        h h+1      n-1
fir high-- ke baad :-
0,0,0,0,0,0,1,1,1,1,0/1/2......,2,2,2,2,2,2,2
^         ^ ^     ^   ^       ^ ^       ^
|         | |     |   |       | |       |
0     (l-1) l (m-1)   m       h h+1     n-1
ISME mid++ NAHI KARTE

DRY RUN :-
nums = [0, 1, 2, 0, 1, 2, 1, 2, 0, 0, 0, 1]
n = 12
low = 0
mid = 0
high = 11

pass 1 :-
{index} :- low = 0 mid = 0 high = 11
0       1       2       0       1       2       1       2       0       0       0       1
low                                                                                     high
mid

since, nums[mid] == 0 ---> swap(nums[mid], nums[low]), low++, mid++
0       1       2       0       1       2       1       2       0       0       0       1
        low                                                                             high
        mid

pass 2 :-
{index} :- low = 1 mid = 1 high = 11
since, nums[mid] == 1 ---> NO SWAP, only mid++
0       1       2       0       1       2       1       2       0       0       0       1
        low                                                                             high
                mid

pass 3 :-
{index} :- low = 1 mid = 2 high = 11
since, nums[mid] == 2 ---> swap(nums[mid], nums[high]), ONLY high-- (mid remains same)
0       1       1       0       1       2       1       2       0       0       0       2
        low                                                                     high
                mid

pass 4 :-
{index} :- low = 1 mid = 2 high = 10
since, nums[mid] == 1 ---> NO SWAP, only mid++
0       1       1       0       1       2       1       2       0       0       0       2
        low                                                                     high
                        mid

pass 5 :-
{index} :- low = 1 mid = 3 high = 10
since, nums[mid] == 0 ---> swap(nums[mid], nums[low]), low++, mid++
0       0       1       1       1       2       1       2       0       0       0       2
                low                                                             high
                                mid

pass 6 :-
{index} :- low = 2 mid = 4 high = 10
since, nums[mid] == 1 ---> NO SWAP, only mid++
0       0       1       1       1       2       1       2       0       0       0       2
                low                                                             high
                                        mid

pass 7 :-
{index} :- low = 2 mid = 5 high = 10
since, nums[mid] == 2 ---> swap(nums[mid], nums[high]), ONLY high-- (mid remains same)
0       0       1       1       1       0       1       2       0       0       2       2
                low                                                     high
                                        mid

pass 8 :-
{index} :- low = 2 mid = 5 high = 9
since, nums[mid] == 0 ---> swap(nums[mid], nums[low]), low++, mid++
0       0       0       1       1       1       1       2       0       0       2       2
                        low                                             high
                                                mid

pass 9 :-
{index} :- low = 3 mid = 6 high = 9
since, nums[mid] == 1 ---> NO SWAP, only mid++
0       0       0       1       1       1       1       2       0       0       2       2
                        low                                             high
                                                        mid

pass 10 :-
{index} :- low = 3 mid = 7 high = 9
since, nums[mid] == 2 ---> swap(nums[mid], nums[high]), ONLY high-- (mid remains same)
0       0       0       1       1       1       1       0       0       2       2       2
                        low                                     high
                                                        mid

pass 11 :-
{index} :- low = 3 mid = 7 high = 8
since, nums[mid] == 0 ---> swap(nums[mid], nums[low]), low++, mid++
0       0       0       0       1       1       1       1       0       2       2       2
                                low                             high
                                                                mid

pass 12 :-
{index} :- low = 4 mid = 8 high = 8
since, nums[mid] == 0 ---> swap(nums[mid], nums[low]), low++, mid++
0       0       0       0       0       1       1       1       1       2       2       2
                                        low                     high
                                                                        mid

Loop terminates because mid > high (mid = 9, high = 8).

Final Sorted Array:
[0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2]
*/

#include<bits/stdc++.h>
using namespace std;

void sort_0s_1s_2s(vector <int> &nums){
    int n = nums.size();
    int low = 0, mid = 0, high = n-1;

    while(mid <= high){
        if(nums[mid] == 0){
            swap(nums[mid], nums[low]);
            low++;
            mid++;
        }
        else if(nums[mid] == 1){
            mid++;
        }
        else{
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

int main(){
    vector <int> nums = {0,1,2,0,1,2,1,2,0,0,0,1};
    int n = nums.size();
    cout<<"Before sorting :-"<<endl;
    for(int i = 0;i < n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    sort_0s_1s_2s(nums);
    cout<<"After sorting :-"<<endl;
    for(int i = 0;i < n;i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}

/*
TC :- O(N) ---> As, in each pass either mid is moving or high is moving for reducing array size {low movement is not counted as low moves along with mid so considering mid movement covers low movement too} so total N elements are covered
SC :- O(1) ---> As, no extra space is required
*/