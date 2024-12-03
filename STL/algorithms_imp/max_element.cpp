// It will return the "Memory address of the location of the element from an array where max or min value is present

#include<iostream>
#include<algorithm>

using namespace std;

int main(){
    int a[]={2,3,-1,3,-2,-22,4,-2,0,-23};
    cout<<"Printing the max element from the array a :-"<<endl;
   // int a1 = *max_element(a,a+sizeof(a)-1);       // It shows error as if i add sizeof(a), because sizeof(a) gives me size of array "a" in bytes, not the number of elements
    int a1 = *max_element(a,a+sizeof(a)/sizeof(a[0]));
    cout<<a1;
    cout<<"\nPrinting the min element from the array a :-"<<endl;
//  int a2 = *min_element(a,a+sizeof(a)/sizeof(a[0])-1);    ---->   This will show error as it will be [a,a+sizeof(a)/sizeof(a[0])-1)
    int a2 = *min_element(a,a+sizeof(a)/sizeof(a[0]));
    cout<<a2;
    return 0;
}