// Even this think by me :-

#include<iostream>
using namespace std;

void pattern(int n){
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            cout<<"* ";
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