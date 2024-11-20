// Uncomment was my think :-

#include<iostream>
using namespace std;

void pattern(int n){
    for(int i=1;i<n+1;i++){
        int k=i;
        for(int j=0;j<i;j++){
            cout<<k<<" ";   //  Instead of "k", i could have directly even wrote "i".
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