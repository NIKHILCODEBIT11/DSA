// For better understaning i am finding "second_largest" and also "second_smallest"
// I will set "largest" as array 1st element and "second_largest" as "INT_MIN" and will traverse whole array and will look for elements > largest and if that is greater than largest then automatically it it will be new largest and previous largest value will become 2nd largest
// and if not above case tehn i will check if element is less than largest and greater than 2nd largest then i will update "second_largest" to that element

#include<bits/stdc++.h>

using namespace std;

int get_second_largest(vector <int> &nums){
    if(nums.size() < 2){   // It means array contains only a single element
        return -1;
    }

    int largest = INT_MIN;
    int second_largest = INT_MIN;
    
    for(int i = 0; i < nums.size(); i++){
        if(largest < nums[i]){
            second_largest=largest;
            largest=nums[i];
        }
        else if(nums[i] > second_largest && nums[i] < largest){  // Reason of this :-   [1, 2, 4, 7, 7, 5]
            second_largest=nums[i];
        }
    }

    return (second_largest == INT_MIN) ? -1 :second_largest;
}

int get_second_smallest(vector <int> &nums){
    if(nums.size() < 2){   // It means array contains only a single element
        return -1;
    }

    int smallest = INT_MAX;
    int second_smallest = INT_MAX;

    for(int i = 0; i < nums.size(); i++){
        if(nums[i] < smallest){
            second_smallest = smallest;
            smallest = nums[i];
        }
        else if(nums[i] < second_smallest && nums[i] > smallest){
            second_smallest = nums[i];
        }
    }
    
    return (second_smallest == INT_MAX) ? -1 : second_smallest;
}

int main(){
    vector <int> nums={2,3,4,2,3,1,7,5,6,9};
    cout<<"The second largest element is "<<get_second_largest(nums)<<endl;
    cout<<"The second smallest element is "<<get_second_smallest(nums);
    return 0;
}


/*

Pass Vector by Reference: 
In get_second_largest, pass the vector by reference (const vector<int>& nums) just like in 
get_second_smallest. Passing by value creates a full copy of the vector, incurring O(N)
extra memory overhead for each call.
*/

// Time complexity :- O(N) ----> As, i am conidering only calculation of "second_largest" for which only 1 pass is done