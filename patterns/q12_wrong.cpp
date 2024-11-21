#include<iostream>
using namespace std;

void pattern(int n){
    for(int i=1;i<n+1;i++){
        if(i%2==0){
            for(int j=0;j<i;j++){
                cout<<j+1;
            }
            for(int j2=0;j2<2*n-(2*i);j2++){
                cout<<" ";
            }
            for(int k2=n;k2>i+1;k2--){
                cout<<n-k2+1;
            }
            cout<<endl;
        }
        else{
            for(int k=1;k<i+1;k++){
                cout<<k;
            }
            for(int j1=0;j1<2*n-(2*i);j1++){
                cout<<" ";
            }
            for(int k=0;k<i;k++){
                cout<<k;
            }
            cout<<endl;
        }
    }
}
int main(){
    int n;
    cout<<"Enter n : ";
    cin>>n;
    pattern(n);
    return 0;
}