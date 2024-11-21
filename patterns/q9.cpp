#include<iostream>
using namespace std;

void pattern(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            cout<<"  ";
        }
        for(int k=0;k<2*i+1;k++){
            cout<<"* ";
        }
        cout<<endl;
    }
    for(int i=0;i<n;i++){
        for(int k=n;k>n-i;k--){
            cout<<"  ";
        }
        for(int k=1;k<2*n-(2*i);k++){
            cout<<"* ";
        }
        cout<<endl;
    }
}
int main(){
    int n;
    cout<<"Enter n :";
    cin>>n;
    pattern(n);
    return 0;
}