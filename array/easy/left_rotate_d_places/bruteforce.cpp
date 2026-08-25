/*
Here consider an array [2,3,4,2,5,7] whose size is 6 and suppose i have to rotate it by 6 places so i will get the same array [2,3,4,2,5,7] again
EXAMPLE :- Rotate [2,3,4] by 3 places :-
1ST ROTATION :- [3,4,2]
2ND ROTATION :- [4,2,3]
3RD ROTATION :- [2,3,4]

---> so if size of an array is n then after n rotations i will get the same array again
So, suppose for above array of size 6 i want the array after 23 rotations then i should focus on fact that after each 6 rotation i will get same array again, so no use of going till 23 rotation using a loop rather :0
I will use modulo operator :- d = d % n
like :-    new_d = old_d % n
new_d = 23 % 6 -----> new_d = 5
So the final resulting array after whole 23 rotations will be same as the array after 5 rotations

1.
Here, i am gonna store first new_d elements in another vector like i used to store first element in temp in the case of left_rotate_one_place

2.
then, i am gonna shift (i-d) index to index i where i starts from d to n
Like [2,3,4] rotate by 2 places 
for(int i = d; i < n; i++){
    nums[i-d] = nums[i];
}
Only 1 iteration will occur giving resultant array as [ 4 , _ , _ ]  ---> "_" will be filled by temp array

3.
After shifting, I will put the stored elements in temp to last leftout positions :-
then i am gonna put element of index {i - (n-d)} from temp to index i of nums where i starts from (n-d) to n
for(int i = n-d; i < n; i++){
    nums[i] = temp[i - (n-d)];
}
*/

#include<bits/stdc++.h>
using namespace std;

void left_rotate_d_places(vector <int> &nums, int d){
    if(nums.size() <= 1){     // For vector of size 0 or 1
        return;
    }

    // Finding out actual number of rotations to perform :-
    d = d % nums.size();

    if( d == 0){    // As, if for array of size 6 i want 6 rotations then i am gonna get same array so no use of running all steps to delay
        return;
    }

    // Storing first d elements in temp :-
    vector <int> temp(d);   // It creates an array of size "d" with each element 0 like for size 3 it will create   temp = [0, 0, 0]
    /*
    for(int i = 0; i < d; i++){
        temp.push_back(nums[i]);
    }

    This code will push elements to back like [0, 0, 0, 2]
    then [0, 0, 0, 2, 3]
    then [0, 0, 0, 2, 3, 7]

    So i will have to use direct indexing
    */
    for(int i = 0; i < d; i++){
        temp[i] = nums[i];
    }

    // Shifting leftout elements in vector num to starting positions :-
    for(int i = d; i < nums.size(); i++){
        nums[i - d] = nums[i];
    }

    // Putting back elements from temp to the leftout end poisitons in vector nums after the 2nd step of shifting :-
    for(int i = nums.size() - d; i < nums.size(); i++){
        nums[i] = temp[i - (nums.size() - d)];
    }
}

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }

    int d;
    cout<<"Enter number of places of rotation :- ";
    cin>>d;

    cout<<"Before left rotation by "<<d<<" places :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;

    left_rotate_d_places(nums , d);

    cout<<"After left rotation by "<<d<<" places :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}


/*

Time complexity :-
For 1st step of storing (d) elements in temp ----> O(d)
For 2nd step of shifting (n - d) elements in nums -----> O(n-d)
For final step of putting back (d) elements from temp to leftout end position in nums ----> O(d)

Time complexity :- O(d + (n-d) + d) = O(n+d)
Space complexity :- O(d) ----> As, i am using extra vector temp of size d to store first d elements

*/

/*

I could also do :-
for an array of size 5 ----> [1,2,3,4,5] rotating by 3 places
1st rotation :- Rotate d elements ----> [3,2,1,4,5]
2nd rotation :- Rotate last (n - d) elements -----> [3,2,1,5,4]
3rd rotation :- Rotate complete array -----> [4,5,1,2,3]
SAME RESULT

CODE :-  { USING STL }
#include <iostream>
#include <vector>
#include <algorithm> // for std::reverse

void left_rotate_d_places(std::vector<int> &nums, int d) {
    int n = nums.size();
    if (n <= 1) return;
    
    d = d % n;
    if (d == 0) return;

    // Step 1: Reverse first d elements
    std::reverse(nums.begin(), nums.begin() + d);

    // Step 2: Reverse remaining n - d elements
    std::reverse(nums.begin() + d, nums.end());

    // Step 3: Reverse the entire vector
    std::reverse(nums.begin(), nums.end());
}

*/