// "SORT" algorithm is basically designed for ----->   Sorting elements of an "ARRAY" or "VECTOR" in ascending order.

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){

    // SORTING THE WHOLE ARRAY :-

    cout<<"Sorting an whole array of elements :-\n"<<endl<<endl;

    int a[]={2,4,1,0,4,-3,6,3,5,6};
    cout<<"Printing elements of a before sorting :-"<<endl;
    for(auto i : a){
        cout<<i<<" ";
    }
    sort(a,a+10);
    cout<<endl<<"Printing elements of a after sorting :-"<<endl;
    for(auto i : a){
        cout<<i<<" ";
    }

    // Sorting a vector in a given range :-

    vector <int> v = {2,3,2,3,1,0,-3,2,6};
    cout<<endl<<"Sorting a vector in a given range :-\n\n"<<endl;
    cout<<"Printing elements of v before sorting :-"<<endl;
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl<<"Printing elements of v after sorting :-"<<endl;
    sort(v.begin(),--(--v.end()));      //  The range is    (2,3,2,3,1,0,-3) not (2,6)
    for(auto i : v){
        cout<<i<<" ";
    }

    cout<<"Sorting the elements of array in reversse or descending order :-\n";
    sort(a,a+10,greater <int>());
    cout<<endl<<"Printing elements of a after sorting :-"<<endl;
    for(auto i : a){
        cout<<i<<" ";
    }
    return 0;
}
