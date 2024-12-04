#include<iostream>
#include<math.h>
using namespace std;
int count(int a){
    auto a_ = int(log10(a));
    return a_+1;
}
int main(){
    int n;
    cout<<"Enter n : ";
    cin>>n;
    cout<<"The number of digits in "<<n<<" is "<<count(n);
    return 0;
}