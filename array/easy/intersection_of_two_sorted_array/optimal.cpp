// Here, i am going to use a 2-pointer approach
// i always point and traverse in nums_1 and j always point and traverse in nums_2

#include<bits/stdc++.h>
using namespace std;

vector <int> intersection_of_two_sorted_arrays(vector <int> &nums_1, vector <int> &nums_2){
    int n1 = nums_1.size();
    int n2 = nums_2.size();

    int i = 0, j = 0;
    vector <int> ans;

    while(i < n1 && j < n2){
        if(nums_1[i] == nums_2[j]){
            ans.push_back(nums_1[i]);
            i++;
            j++;
        }
        else if(nums_1[i] < nums_2[j]){
            i++;
        }
        else{   // The left out case of nums_1[i] > nums_2[j]
            j++;
        }
    }
    return ans;
}

int main(){
    int n1, n2;
    cout<<"Enter size of first vector :-";
    cin>>n1;
    vector <int> nums_1(n1);      // nums_1 is created with size 4: [0, 0, 0, 0]
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
    vector <int> final = intersection_of_two_sorted_arrays(nums_1, nums_2);
    for(auto it : final){
        cout<<it<<" ";
    }
    return 0;
}

/*

Consider nums_1 = [2,3,3,4,5,6,6]
cosnider nums_2 = [3,6,7]

Step 1: i = 0, j = 0
Values: nums_1[0] = 2, nums_2[0] = 3
Comparison: 2 < 3 (nums_1[i] < nums_2[j])
Action: Increment i to 1.
Resulting ans: []

Step 2: i = 1, j = 0
Values: nums_1[1] = 3, nums_2[0] = 3
Comparison: 3 == 3 (nums_1[i] == nums_2[j])
Action: Push 3 into ans, increment i to 2 and j to 1.
Resulting ans: [3]

Step 3: i = 2, j = 1
Values: nums_1[2] = 3, nums_2[1] = 6
Comparison: 3 < 6 (nums_1[i] < nums_2[j])
Action: Increment i to 3.
Resulting ans: [3]

Step 4: i = 3, j = 1
Values: nums_1[3] = 4, nums_2[1] = 6
Comparison: 4 < 6 (nums_1[i] < nums_2[j])
Action: Increment i to 4.
Resulting ans: [3]

Step 5: i = 4, j = 1
Values: nums_1[4] = 5, nums_2[1] = 6
Comparison: 5 < 6 (nums_1[i] < nums_2[j])
Action: Increment i to 5.
Resulting ans: [3]

Step 6: i = 5, j = 1
Values: nums_1[5] = 6, nums_2[1] = 6
Comparison: 6 == 6 (nums_1[i] == nums_2[j])
Action: Push 6 into ans, increment i to 6 and j to 2.
Resulting ans: [3, 6]

Step 7: i = 6, j = 2
Values: nums_1[6] = 6, nums_2[2] = 7
Comparison: 6 < 7 (nums_1[i] < nums_2[j])
Action: Increment i to 7.
Resulting ans: [3, 6]

Step 8: i = 7, j = 2
Loop condition check: i < n1 fails because 7 < 7 is false.
Loop terminates.

*/

// TC :- O(N1 + N2) ----> As, in worst case  i travel whole array n1 then n2 likefirst else if condition matches then else
// SC :- O(N1 + N2) ----> As, i am using ans array to return which in worst case as above would be storing all the elements of both array