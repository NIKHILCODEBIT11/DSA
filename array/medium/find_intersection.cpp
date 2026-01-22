#include<bits/stdc++.h>
using namespace std;

vector <int> find_intersection(vector <int> a,vector <int> b){
    vector <int> intersection;
    vector <int> visited[b.size()]=(0);
    for(int i=0;i<a.size();i++){
        for(int j=i;j<b.size();j++){
            if(a[i]==b[j]){
                intersection.push_back(a[i]);
                visited=a[i];
            }
        }
    }
    return intersection;
}

int main(){
    vector <int> a={1,2,2,2,3,4,4,5,6,6};
    vector <int> b={1,1,1,2,3,4,4,6,7};
    auto intersect=find_intersection(a,b);
    for(auto i : intersect){
        cout<<i<<" ";
    }
    return 0;
}