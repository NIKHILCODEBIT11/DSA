//      Sorting elements of a "pair", but not in an "in-built way" but a "customized way"

// Sort it according to second element
// If second element is same, then sort it according to the first element but in descending order

#include<iostream>
#include<functional>
#include<algorithm>

using namespace std;

bool com(pair <int,int> p1,pair <int,int> p2){      // customized "COMPARATOR" or "FUNCTOR"
    if(p1.second<p2.second){        // I can also write :-    if(p1.second<p2.second) return true;      ---->   Syntax of for loop
        return true;
    }
    else if(p1.second>p2.second){
        return false;
    }
    else{
        if(p1.first>p2.first){
            return true;
        }
        else{
            return false;
        }
    }
}

int main(){
    pair <int,int> a[] = {{1,2},{2,2},{1,4},{2,4},{5,2},{3,2}};
    cout<<"Printing elements of pair before sorting :-"<<endl;
    for(auto i : a){
        cout<<i.first<<","<<i.second<<endl;
    }

    // Sorting elements of an array using "customized" comparator :-

    int a1=sizeof(a)/sizeof(a[0]);      // Because sizeof(a) gives size of array in bytes and to get number of elements, i must divide the size of array by size of each element
    sort(a,a+a1,com);
    cout<<"Printing elements of pair after sorting :-"<<endl;
    for(auto i : a){
        cout<<i.first<<","<<i.second<<endl;
    }
    return 0;
}


//   "Customized comparator" must always be of type "BOOLEAN" and should only return "TRUE" or "FALSE"