#include<bits/stdc++.h>
using namespace std;

void generate_sequences(int index, string &ds, vector <string> &result, int n){
    if(index == n){
        result.push_back(ds);
        return;
    }

    ds.push_back('0');
    generate_sequences(index + 1, ds, result, n);
    ds.pop_back();

    if(ds.empty() || ds.back() != '1'){
        ds.push_back('1');
        generate_sequences(index + 1, ds, result, n);
        ds.pop_back(); // Backtrack
    }
}

int main(){
    string ds = "";
    vector <string> result;
    int n = 3;
    generate_sequences(0, ds, result, n);
    for(auto ans : result){
        cout<<ans<<" ";
    }
    return 0;
}