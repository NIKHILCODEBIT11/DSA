#include<iostream>
using namespace std;
void pattern(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            cout<<"  ";     // Double space is given in cout statement for good visualization and also as i gave a " " after "*" in 3rd for loop.
        }
        for(int k=0;k<2*i+1;k++){
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