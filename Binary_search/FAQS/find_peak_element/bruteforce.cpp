#include<bits/stdc++.h>
using namespace std;

// agar ek se zyada peak hain to unme se kisi ek peak ko return karunga
int peak_element(vector <int> &nums){
    int n = nums.size();
    for(int i = 0; i < n ; i++){
        if(((i == 0) || nums[i] > nums[i - 1]) && ((i == n - 1 || nums[i] > nums[i + 1]))){
            return nums[i];
        }
    }
}

int main(){
    vector <int> nums = {1,2,3,4,5,6,7,8,5,1};
    cout<<"The peak element is "<<peak_element(nums);
    return 0;
}