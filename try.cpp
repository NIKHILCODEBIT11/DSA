#include<iostream>
using namespace std;
int func(int a,int b);
int main(){
    int a=3,b=4;
    int k=func(a,b);
    cout<<"The value is "<<k<<endl;
}
int func(int a,int b){
    return a+b*b;
}