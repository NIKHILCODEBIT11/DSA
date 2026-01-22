#include<bits/stdc++.h>
using namespace std;

// BRUTE FORCE :-
/*
int move_zeroes_end(vector <int> &arr){ // 1 2 0 3 0 0 4 0
    vector <int> temp(arr.size());
    int temp_count=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i]!=0){
            temp[temp_count]=arr[i];
            temp_count++;
        }
    }
    for(int i=0;i<temp_count+1;i++){
        arr[i]=temp[i];
    }
    for(int i=temp_count+1;i<arr.size();i++){
        arr[i]=0;
    }
}
*/

// OPTIMAL APPROACH :-
int move_zeroes_end(vector <int> &arr){
    int j=-1;   // If no 0 present then it will remain -1 so no zeroes to move to end
    for(int i=0;i<arr.size();i++){
        if(arr[i]==0){
            j=i;
            break;
        }
    }
    for(int i=j+1;i<arr.size();i++){
        if(arr[i]!=0){
            swap(arr[i],arr[j]);
            j++;
        }
    }
}
int main(){
    vector <int> arr={1,2,0,3,0,0,4,0};
    cout<<"Original array :- "<<endl;
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    move_zeroes_end(arr);
    cout<<"updated array :- "<<endl;
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}

//      [1,2,3,0,4,0,0,4,3,0]