// Here, i am gonna do 2 POINTER APPROACH
// In the sorted array i will keep pointer i to 0th positio as the 1 st elemnt in the sorted array will surely be representing the unique number for it's duplicates
// and j poinnter starting from index = 1 and will iterate and as soon as arr element not equal to arr[i] is reached it will update the ith elment 
// and will continue till end of j

#include<bits/stdc++.h>
using namespace std;

int remove_duplicates(vector <int> &arr){
    int i = 0;    // 1st pointer
    for(int j = 1; j < arr.size(); j++){
        if(arr[i] != arr[j]){
            arr[i+1] = arr[j];   // I could have avoided arr[i+1] and i++ by writing arr[++i]
            i++;
        }
        else{
            continue;
        }
    }
    return i+1;
}

int main(){
    int n;
    cin>>n;
    vector <int> arr(n);
    for(int i = 0; i < n; i++){
        cin>>arr[i];
    }
    
    auto k = remove_duplicates(arr);
    cout<<"Unique elements count :-"<<k<<endl;
    cout<<"Modified array :-"<<endl;
    for(auto num : arr){
        cout<<num<<" ";
    }
    return 0;
}

// Time complexity :- O(N) ---> As, for worst case when all elements in arr are unique then it will traverse whole array
// Space complexity :- O(1)