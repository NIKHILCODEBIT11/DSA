// Here, i will start from index 1 and will go till n-1 index and will compare each element to 
// it's previous element and will continue

#include<bits/stdc++.h>
using namespace std;

bool check(vector <int> arr){
    for(int i = 1; i < arr.size(); i++){
        if(arr[i] >= arr[i-1]){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

int main(){
    vector <int> arr={1,2,3,41,4,55,65,66};
    cout<<"The array is sorted : "<<std::boolalpha<<check(arr);
    return 0;
}

// Time complexity :- O(N)  ----> As, i am traversing through the whole array from index 1 till end 
// It has a single solution no BRUTEFORCE, BETTER, OPTIMAL