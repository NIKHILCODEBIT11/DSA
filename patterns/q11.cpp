#include<iostream>
using namespace std;

int s;
void pattern(int n){
    for(int i=0;i<n;i++){
        if(i%2==0){
            s=1;
        }
        else{
            s=0;
        }
        for(int j=n;j>=n-i;j--){
            cout<<s<<" ";
            s=1-s;
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