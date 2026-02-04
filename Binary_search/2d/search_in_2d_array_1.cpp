#include<bits/stdc++.h>
using namespace std;

// I am given a sorted array and have to search a target and if it is present return true or else return false

// BRUTEFORCE :-

bool search_2d(vector <vector<int>> &nums,int target){
    for(int i=0;i<nums.size();i++){
        for(int j=0;j<nums[0].size();j++){
            if(nums[i][j]==target){
                return true;
            }
            // else{            This is redundant as if block so no need
            //     continue;
            // }
        }
    }
    return false;
}

int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=33;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    cout<<"The target value of "<<target<<" is present : "<<search_2d(nums,target);
    return 0;
}