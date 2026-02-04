#include<bits/stdc++.h>
using namespace std;

pair<int,int> search_2d(vector <vector<int>> &nums,int target){
    int n=nums.size();
    int m=nums[0].size();
    int row=0;
    int column=m-1;
    while(row<n && column>=0){
        if(nums[row][column] == target){
            return {row,column};
        }
        else if(nums[row][column]<target){
            row++;
        }
        else{
            column--;
        }
    }
    return {-1,-1};
}

/*
    STAIRCASE SEARCH VISUALIZATION
    Target: 34
    
    Matrix Structure:
    [  2,   4,   6,   7,   9  ]  <-- Row 0
    [ 21,  23,  25,  26,  27  ]  <-- Row 1
    [ 29,  32,  33,  34,  36  ]  <-- Row 2
    [ 37,  39,  40,  42,  46* ]  <-- Row 3 (Note: Fixed 26 to 46 for sorted logic)
    
    Search Path:
    1. Start at Top-Right: (0, 4) -> Value: 9
       9 < 34 ? Yes -> Move Down (row++)
       
    2. Current: (1, 4) -> Value: 27
       27 < 34 ? Yes -> Move Down (row++)
       
    3. Current: (2, 4) -> Value: 36
       36 > 34 ? Yes -> Move Left (column--)
       
    4. Current: (2, 3) -> Value: 34
       34 == 34 ? MATCH FOUND! -> Return {2, 3}
       
    Complexity:
    - Time: O(N + M) where N = rows, M = columns.
    - Space: O(1)
*/


int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=34;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    pair <int,int> ans = search_2d(nums,target);
    cout<<"The position of target is ("<<ans.first<<","<<ans.second<<")";
    return 0;
}