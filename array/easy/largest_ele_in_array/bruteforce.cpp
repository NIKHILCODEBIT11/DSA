// The Bruteforce solution is :- Sort the elements then the last element will be the largest element
#include<bits/stdc++.h>
using namespace std;

int partition(vector <int> &nums, int low, int high){
    int pivot = nums[low];
    int i = low;
    int j = high;

    while(i < j){
        while(i <= high && nums[i] <= pivot){
            i++;
        }
        while(j >= low && nums[j] > pivot){
            j--;
        }
        if(i < j){
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[low], nums[j]);
    return j;
}

void quick_sort(vector <int> &nums, int low, int high){
    if(low < high){
        int partition_indx = partition(nums, low, high);
        quick_sort(nums, low, partition_indx-1);
        quick_sort(nums, partition_indx+1, high);
    }
}

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i =0; i<n ;i++){
        cin>>nums[i];
    }
    cout<<"Array is :-"<<endl;
    for(int i=0; i<n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    quick_sort(nums, 0, n-1);
    cout<<"The largest element is "<<nums.back();  // Also, nums[nums.size() - 1] and nums.at(nums.size() - 1)
    return 0;
}

// Time complexity :- O(N*logN)
// Space complexity :- O(1)