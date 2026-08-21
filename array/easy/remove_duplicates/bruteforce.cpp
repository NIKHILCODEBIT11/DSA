// Here, i have to MODIFY the given array and store the unique elements in the start index and return the number of unique elements
// In bruteforce i am gonna use "set"
// I am considering that given input array is sorted otherwise i could also use sorting algo to sort then run main()

#include<bits/stdc++.h>
using namespace std;

int remove_duplicates(vector <int> &arr){
    set <int> st;

    // Insert all elements into the set
    for(auto num : arr){
        st.insert(num);
    }
    // For an element insertion set takes tc of "logn" and since here are n elements so "n*logn"

    // Copy unique elements back to the start of array
    int index = 0;
    for(auto num : st){
        arr[index++] = num;
    }
    // Suppose all were unique elments then st would also contain "n" elements so tc of copying in worst is "n"

    return index;
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

// Time complexity :- O(N*logN)
// Space complexity :- O(N) as set in worst condition would store all elements if all elements in the array are unique