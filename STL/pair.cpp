#include<iostream>
using namespace std;

void explaine(){
    pair<int,int> p={3,4};
    cout<<p.first;
}

void pair_array(){
    pair<int,pair <int,pair <int,int>>> e[] = { {1,{2,{3,4}}},{1,{2,{3,4}}}, {6,{7,{8,9}}}};
    cout<<"Elements of 0th index : "<<endl;
    cout<<e[0].first<<" "<<e[0].second.first<<" "<<e[0].second.second.first<<" "<<e[0].second.second.second<<endl;
    cout<<"Elements of 1st index : "<<endl;
    cout<<e[1].first<<" "<<e[1].second.first<<" "<<e[1].second.second.first<<" "<<e[1].second.second.second<<endl;
    cout<<"Elements of 2nd index : "<<endl;
    cout<<e[2].first<<" "<<e[2].second.first<<" "<<e[2].second.second.first<<" "<<e[2].second.second.second<<endl;
    cout<<endl;
}
int main(){
    explaine();
    cout<<endl;
    pair <int,pair <int,pair <pair <int,int>,int>>> w= {2,{3,{{3,4},5}}};
    cout<<w.first<<" "<<w.second.first<<" "<<w.second.second.first.first<<" "<<w.second.second.first.second<<" "<<w.second.second.second<<endl;
    pair_array();
    return 0;
}