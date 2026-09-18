// For C++ users :- The better solution is USING STL
#include<bits/stdc++.h>
using namespace std;

vector <int> next_perm(vector <int> &nums){
    next_permutation(nums.begin(), nums.end());
    return nums;
}

int main(){
    vector <int> nums = {2,1,5,4,3,0,0};
    cout<<"Before next permutation :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
    nums = next_perm(nums);
    cout<<"After next permutation :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
}

/*
Time Complexity (TC): O(N)
    1.std::next_permutation scans the array from right to left to find the pivot, finds the successor to swap, and then reverses the remaining suffix. Each of these steps takes at most linear time relative to the number of elements N.
    2. Printing the vector in main() also takes $\mathcal{O}(N)$ time.
    3. Overall time complexity is linear, $\mathcal{O}(N)$.

Space Complexity (SC): O(N) as written (O(1) auxiliary if optimized)
    1. As written: The function returns nums by value (vector<int> next_perm(...)), which creates a copy of the $N$-element vector upon return, resulting in O(N) extra space.
    2. Under the hood: std::next_permutation itself operates entirely in-place with O(1) auxiliary space. Changing the function return type to void or returning by reference (vector<int>&) reduces the auxiliary space complexity to O(1).
*/