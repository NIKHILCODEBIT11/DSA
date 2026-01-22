#include<bits/stdc++.h>
using namespace std;

// BRUTE FORCE APPROACH :-
/*

void left_rotate_d(vector <int> &arr,int d){
    d=d%arr.size();
    int temp[d];

    for(int i=0;i<d;i++){
        temp[i]=arr[i];     // 0,1,2
    }

    for(int i=d;i<arr.size();i++){
        arr[i-d]=arr[i];        //0=3,1=4,2=5,3=6,4=7
    }

    for(int i=0;i<d;i++){
        arr[arr.size()-d+i]=temp[i];     // 5=0,6=1,7=2
    }
}

*/


// OPTIMAL APPROACH :-
void reverse(vector <int> &arr,int start,int end){
    while(start<end){
        int temp=arr[start];   
        arr[start]=arr[end];
        arr[end]=temp;
        start++;
        end--;
    }
}
void left_rotate_d(vector <int> &arr,int d){
    reverse(arr,0,d-1);
    reverse(arr,d,arr.size()-1);
    reverse(arr,0,arr.size()-1);
}

int main(){
    vector <int> arr={1,2,3,4,5,5,6,7};
    int d;
    cout<<"Enter value of d : ";
    cin>>d;
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    left_rotate_d(arr,d);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}

