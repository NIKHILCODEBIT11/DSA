/*
Brute force :- Sort the elements then get the 2nd last element
But what if arr after sorting is 1 7 7 7 7 7
In that case  iw ill have to check that second_largest != largest too
*/

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

void quick_sort(vector<int> &nums, int low, int high){
    if(low < high){
        int partition_indx = partition(nums, low, high);
        quick_sort(nums, low, partition_indx - 1);
        quick_sort(nums, partition_indx + 1, high);
    }
}

int main(){
    vector <int> nums={3,7,4,2,2,7,1,3,7,4,5,7,3,2};  // After sorting   [1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 7, 7, 7, 7]
    // Here, the second largest element is 5 which is far back from largest element
    cout<<"Array is :-";
    for(int i = 0; i < nums.size(); i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    quick_sort(nums, 0, nums.size() - 1);
    int second_largest_element = -1;            // Default if no second_largest_element exist like in   [2,2,2,2,2]
    for(int i = nums.size() - 2; i >= 0; i--){  // For a size 5 array nums.size()-2 returns 3 i.e, 2nd last index
        if(nums[i] != nums.back()){             // nums.back() returns element itself not it's index
            second_largest_element = nums[i];
            break;
        }
    }

    if (second_largest_element != -1) {
        cout << "The second largest element is " << second_largest_element << endl;
    }
    else {
        cout << "No second largest element exists." << endl;
    }
    return 0;
}

/*
Time complexity :- O(N*logN + N)
Reason :- O(N*logN) ----> It is for quicksort
          O(N) ---------> It is for worst case of finding second_largest_element inside main() if i have to travers the whoe array again like in [2,2,2,2,2]
*/