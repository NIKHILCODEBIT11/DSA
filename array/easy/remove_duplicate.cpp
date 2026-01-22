#include <bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int>& arr) {
    int j=0;
    for(int i=1;i<arr.size();i++){
        if(arr[j]!=arr[i]){
            j++;
            arr[j]=arr[i];
        }
    }
    arr.resize(j+1);
    return arr.size();
}

int main() {
    vector<int> arr = {1,1,1,2,2,2,2,2,3,3,3,3,4,5,7};

    for (int x : arr)
        cout << x << " ";
    cout << endl;

    auto in=removeDuplicates(arr);

    for (int x : arr)
        cout << x << " ";
    cout << endl;

    cout<<"The total number of unique elements are "<<in<<endl;

    return 0;
}
