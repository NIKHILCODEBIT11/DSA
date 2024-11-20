// #include<iostream>
// using namespace std;

// int main(){
//     char c='*';
//     for(int i=0;i<5;i++){
//         // cout<<5*char('*');  -----> I am getting  210 for this 5times as for loop is running
//         cout<<"* * * * *";
//         cout<<endl;
//     }
//     return 0;
// }


// My think :-

#include<iostream>
using namespace std;

void pattern(int);
int main(){
    int n;
    cout<<"Enter n : "<<endl;
    cin>>n;
    pattern(n);
    return 0;
}
void pattern(int n){
    for(int i=0;i<n;i++){
        for(int j=i;j<i+n;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
}

/*

Time complexity : O(n^2)
Space complexity : O(1) ----> That means constant

*/