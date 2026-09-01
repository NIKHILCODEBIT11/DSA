// Here, i am going to use two-pointer approach where i will be iterating only over nums_1 and j will be iterating only over nums_2

#include<bits/stdc++.h>
using namespace std;

vector <int> union_of_two_sorted_array(vector <int> &nums_1, vector <int> &nums_2){
    int n1 = nums_1.size();
    int n2 = nums_2.size();
    int i = 0, j = 0;
    vector <int> union_array;

    while(i < n1 && j < n2){
        if(nums_1[i] <= nums_2[j]){
            if(union_array.size() == 0 || union_array.back() != nums_1[i]){
                union_array.push_back(nums_1[i]);
            }
            i++;
        }
        else{
            if(union_array.empty() || union_array.back() != nums_2[j]){
                union_array.push_back(nums_2[j]);
            }
            j++;
        }
    }

    // What if either of n1 or n2 gets exhausted or reches beyond its size :-
    while(i < n1){     // if j reaches beyond n2
        if(union_array.empty() || union_array.back() != nums_1[i]){
            union_array.push_back(nums_1[i]);
        }
        i++;
    }    
    
    while(j < n2){
        if(union_array.size() == 0 || union_array.back() != nums_2[j]){
            union_array.push_back(nums_2[j]);
        }
        j++;
    }
    return union_array;
}

int main(){
    int n1, n2;
    cout<<"Enter size of first vector :-";
    cin>>n1;
    vector <int> nums_1(n1);
    cout<<"Enter elements for first vector :- ";
    for(int i = 0; i < n1; i++){
        cin>>nums_1[i];
    }
    cout<<"Enter size of second vector :-";
    cin>>n2;
    vector <int> nums_2;     // It gets created of size 0
    cout<<"Enter elements for second vector :- ";
    for(int i = 0; i < n2; i++){
        int input;
        cin>>input;
        nums_2.push_back(input);   // And then each element is pushed back till n2 size
    }
    vector <int> final = union_of_two_sorted_array(nums_1, nums_2);
    for(auto it : final){
        cout<<it<<" ";
    }
    return 0;
}

// vector.size() == 0 is same as doing vector.empty()

/*
Detailed analysis :-

nums_1 = [1, 1, 2, 3, 4, 5] (n_1 = 6)
nums_2 = [2, 3, 4, 4, 5, 6] (n_2 = 6)

Initial State: i = 0, j = 0, union_array = []

Phase 1: Comparing elements while both pointers are within bounds (i < 6 && j < 6) :-

Iteration 1:
State: i = 0 (nums_1[0] = 1), j = 0 (nums_2[0] = 2)
Condition Check: nums_1[0] <= nums_2[0] $\rightarrow$ 1 <= 2 is True.
Duplicate Check: union_array.empty() is True.
Action: Push 1 into union_array and increment i.
Result: union_array = [1], i = 1, j = 0.

Iteration 2:
State: i = 1 (nums_1[1] = 1), j = 0 (nums_2[0] = 2)
Condition Check: nums_1[1] <= nums_2[0] $\rightarrow$ 1 <= 2 is True.
Duplicate Check: union_array.back() is 1, which equals nums_1[1].
Action: 1 is a duplicate, so do not push it. Increment i.
Result: union_array = [1], i = 2, j = 0.

Iteration 3:
State: i = 2 (nums_1[2] = 2), j = 0 (nums_2[0] = 2)
Condition Check: nums_1[2] <= nums_2[0] $\rightarrow$ 2 <= 2 is True.
Duplicate Check: union_array.back() is 1, which is not equal to nums_1[2] (2).
Action: Push 2 into union_array and increment i.
Result: union_array = [1, 2], i = 3, j = 0.

Iteration 4:
State: i = 3 (nums_1[3] = 3), j = 0 (nums_2[0] = 2)
Condition Check: nums_1[3] <= nums_2[0] $\rightarrow$ 3 <= 2 is False. Entering else block.
Duplicate Check: union_array.back() is 2, which equals nums_2[0].
Action: 2 is a duplicate, so do not push it. Increment j.
Result: union_array = [1, 2], i = 3, j = 1.

Iteration 5:
State: i = 3 (nums_1[3] = 3), j = 1 (nums_2[1] = 3)
Condition Check: nums_1[3] <= nums_2[1] $\rightarrow$ 3 <= 3 is True.
Duplicate Check: union_array.back() is 2, which is not equal to nums_1[3] (3).
Action: Push 3 into union_array and increment i.
Result: union_array = [1, 2, 3], i = 4, j = 1.

Iteration 6:
State: i = 4 (nums_1[4] = 4), j = 1 (nums_2[1] = 3)
Condition Check: nums_1[4] <= nums_2[1] $\rightarrow$ 4 <= 3 is False. Entering else block.
Duplicate Check: union_array.back() is 3, which equals nums_2[1].
Action: 3 is a duplicate, so do not push it. Increment j.

Iteration 7:
State: i = 4 (nums_1[4] = 4), j = 2 (nums_2[2] = 4)
Condition Check: nums_1[4] <= nums_2[2] $\rightarrow$ 4 <= 4 is True.
Duplicate Check: union_array.back() is 3, which is not equal to nums_1[4] (4).
Action: Push 4 into union_array and increment i.
Result: union_array = [1, 2, 3, 4], i = 5, j = 2.

Iteration 8:
State: i = 5 (nums_1[5] = 5), j = 2 (nums_2[2] = 4)
Condition Check: nums_1[5] <= nums_2[2] $\rightarrow$ 5 <= 4 is False. Entering else block.
Duplicate Check: union_array.back() is 4, which equals nums_2[2].
Action: 4 is a duplicate, so do not push it. Increment j.
Result: union_array = [1, 2, 3, 4], i = 5, j = 3.

Iteration 9:
State: i = 5 (nums_1[5] = 5), j = 3 (nums_2[3] = 4)
Condition Check: nums_1[5] <= nums_2[3] $\rightarrow$ 5 <= 4 is False. Entering else block.
Duplicate Check: union_array.back() is 4, which equals nums_2[3].
Action: 4 is a duplicate, so do not push it. Increment j.
Result: union_array = [1, 2, 3, 4], i = 5, j = 4.

Iteration 10:
State: i = 5 (nums_1[5] = 5), j = 4 (nums_2[4] = 5)
Condition Check: nums_1[5] <= nums_2[4] $\rightarrow$ 5 <= 5 is True.
Duplicate Check: union_array.back() is 4, which is not equal to nums_1[5] (5).
Action: Push 5 into union_array and increment i.
Result: union_array = [1, 2, 3, 4, 5], i = 6, j = 4.


End of Main Loop
The condition i < n1 && j < n2 evaluates to 6 < 6 && 4 < 6, which is False because vector nums_1 is completely processed. The main loop exits.

Phase 2: Processing remaining elements in nums_1 (while(i < n1))
The loop condition i < 6 evaluates to 6 < 6 (False). This loop is skipped completely.

Phase 3: Processing remaining elements in nums_2 (while(j < n2))

Iteration 11:
State: j = 4 (nums_2[4] = 5)
Duplicate Check: union_array.back() is 5, which equals nums_2[4].
Action: 5 is a duplicate, so do not push it. Increment j.
Result: union_array = [1, 2, 3, 4, 5], j = 5.

Iteration 12:
State: j = 5 (nums_2[5] = 6)
Duplicate Check: union_array.back() is 5, which is not equal to nums_2[5] (6).
Action: Push 6 into union_array and increment j.
Result: union_array = [1, 2, 3, 4, 5, 6], j = 6.


Final Output:
The loop condition j < 6 evaluates to 6 < 6 (False). Function returns union_array = [1, 2, 3, 4, 5, 6].
*/


/*
Time complexity :- O(N1 + N2) ----> As, i only traverse through both the vectors only 
Space complexity :- O(N1 + N2) ----> As, in worst case i am gonna use union_array of size (N1 + N2) if all elements in each vector are unique
*/