// Here, i am going to take 2 SORTED ARRAYS of size n1 and n2 and will fnd intersection fro both the arrays and store it in ans vector
// i will be iterating over nums_1 of size n1 and j will be iterating over nums_2 of size n2
// i will take element from nums_1 and iterate over the whole nums_2 and if i find any repetition then i will add it to ans
// Also, sice both vectors are sorted so as sson as i reach a certain index in nums_2 whose value is GREATER then the corresponding indexed value of nums_1 ith index then i will break as both arrays are sorted so once in nums_2[j] i reach the value which is greater than nums_1[i] then there is no point in moving ahead
// I will keep an array of size n_2 named visited to keep track of the value from nums_2 which has been repeated or not

#include<bits/stdc++.h>
using namespace std;

vector <int> intersection_of_two_sorted_arrays(vector <int> &nums_1, vector <int> &nums_2){
    int n1 = nums_1.size();
    int n2 = nums_2.size();

    int visited[n2] = {0};
    vector <int> intersection_array;

    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            if(nums_1[i] == nums_2[j] && visited[j] == 0){
                intersection_array.push_back(nums_1[i]);
                visited[j] = 1;
                break;
            }
            if(nums_2[j] > nums_1[i]){
                break;    // If value in nums_2 is itself greater then value in A SORTED ARRAY then there is no point in moving forward
            }
        }
    }
    return intersection_array;
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
Full dry run of above code :-

nums_1 = [1, 2, 2, 3] (n_1 = 4)
nums_2 = [2, 2, 3, 4] (n_2 = 4)

Loop iteration walkthrough :-

Outer Loop i = 0 (nums_1[0] = 1)
1. Inner Loop j = 0 (nums_2[0] = 2):
----> Condition nums_1[0] == nums_2[0] ----> 1 == 2 (False).
----> Early exit check nums_2[0] > nums_1[0] ----> 2 > 1 (True).
----> Action: Inner loop breaks immediately.
State: intersection_array = [], visited = [0, 0, 0, 0]

Outer Loop i = 1 (nums_1[1] = 2)
1. Inner Loop j = 0 (nums_2[0] = 2):
----> Condition nums_1[1] == nums_2[0] && visited[0] == 0 ----> 2 == 2 && 0 == 0 (True).
----> Action: Push 2 into intersection_array, set visited[0] = 1, and break inner loop.
State: intersection_array = [2], visited = [1, 0, 0, 0]

Outer Loop i = 2 (nums_1[2] = 2)
1. Inner Loop j = 0 (nums_2[0] = 2):
----> Condition check: nums_1[2] == nums_2[0] is true (2 == 2), but visited[0] == 0 is False (already used by i=1).
----> Moves to next j.

2. Inner Loop j = 1 (nums_2[1] = 2):
----> Condition nums_1[2] == nums_2[1] && visited[1] == 0 ----> 2 == 2 && 0 == 0 (True).
----> Action: Push 2 into intersection_array, set visited[1] = 1, and break inner loop.
State: intersection_array = [2, 2], visited = [1, 1, 0, 0]

Outer Loop i = 3 (nums_1[3] = 3)
1. Inner Loop j = 0 (nums_2[0] = 2): No match (3 != 2).
2. Inner Loop j = 1 (nums_2[1] = 2): No match (3 != 2).
3. Inner Loop j = 2 (nums_2[2] = 3):
----> Condition nums_1[3] == nums_2[2] && visited[2] == 0 ----> 3 == 3 && 0 == 0 (True).
----> Action: Push 3 into intersection_array, set visited[2] = 1, and break inner loop.
State: intersection_array = [2, 2, 3], visited = [1, 1, 1, 0]


*/

// TC :- O(N1 * N2) ----> As, for worst case i will have to traverse the whole n1 array and also n2 array
// SC :- O(N2) -----> As, i a using a vector visited of size n2