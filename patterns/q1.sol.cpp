#include<iostream>
using namespace std;

void pattern(int n){
    for(int i=0;i<n;i++){
        int j=0;
        while(j<n){
            cout<<"* ";
            j++;
        }
        cout<<endl;
    }
}
int main(){
    int n;
    cout<<"Enter n : ";
    cin>>n;
    pattern(n);
    return 0;
}

/*

Time complexity : O(n^2)
Space complexity : O(1) ----> That means constant

*/