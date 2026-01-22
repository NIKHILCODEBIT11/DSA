#include<bits/stdc++.h>
using namespace std;

void left_rotate(vector <int> &arr){
    auto temp=arr[0];
    for(int i=1;i<arr.size();i++){
        arr[i-1]=arr[i];
    }
    arr[arr.size()-1]=temp;
}

int main(){
    vector <int> arr={1,2,3,4,5};
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    left_rotate(arr);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;

}

//1,2,3,4,5