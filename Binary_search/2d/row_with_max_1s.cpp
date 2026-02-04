#include<bits/stdc++.h>
using namespace std;

int max1s(vector <vector<int>> &matrix){
    int max_sum=-1,index=-1;
    int no_of_rows=matrix.size();
    int no_of_columns=matrix[0].size();
    for(int i=0;i<no_of_rows;i++){
        int sum=0;
        for(int j=0;j<no_of_columns;j++){
            sum+=matrix[i][j];
        }
        if(sum>max_sum){
            max_sum=sum;
            index=i;
        }
    }
    return index;
}

int main(){
    vector<vector<int>> mat = {
    {0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1}
};

    cout<<"The maximum 1s are at "<<max1s(mat);
}