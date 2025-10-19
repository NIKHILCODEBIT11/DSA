#include<iostream>
using namespace std;

int main(){
    string s;
    cout<<"Enter the string ";
    cin>>s;

    int arr[256]={};
    for(int i=0;i<s.length();i++){
        int j=s[i];
        arr[j]++;
    }

    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        if(arr[i]==0){
            break;
        }
        else{
            cout<<"The reprtition of "<<char(i)<<" is "<<arr[i]<<endl;
        }
    }
    return 0;
}