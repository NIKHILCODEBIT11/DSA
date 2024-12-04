//  Extracting all the digits of a number

#include<iostream>
using namespace std;

int main(){
    int a,count=0,a_;
    cout<<"Enter number : ";
    cin>>a;
    a_=a;
    cout<<"The digits that are available in "<<a<<" are :-"<<endl;
    while(a>0){
        int last_digit=a%10;
        a=a/10;     // The role of this is that it will check when "a" will become "0", as the condition given in "while"
        cout<<last_digit<<" ";
        count++;
    }
    cout<<endl<<"The number of digits in "<<a_<<" is "<<count;
    return 0;
}

/*
I can also say that number of times, i am dividing "a" with 10, to get the last digit each time, the same number of digits
 are present in "a", in such case, i can even use log with base 10, shown in program   "digits_count.cpp"
 */
