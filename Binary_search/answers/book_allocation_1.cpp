#include<bits/stdc++.h>
using namespace std;

int number_of_students(vector <int>&nums,int pages){
    int student=1,student_pages=0;
    for(int i=0;i<nums.size();i++){
        if (nums[i] > pages) return INT_MAX;
        if(student_pages+nums[i]<=pages){
            student_pages+=nums[i];
        }
        else{
            student+=1;
            student_pages=nums[i];
        }
    }
    return student;
}

int pages(vector <int>&nums,int assigned_student){
    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    for(int i=low;i<high;i++){
        int count_student=number_of_students(nums,i);
        if(count_student==assigned_student){
            return i;
        }
    }
}

int main(){
    vector <int> nums={25,46,28,49,24};
    int student=4;
    cout<<"The maximum number of pages assigned to any student is :-"<<pages(nums,student);
    return 0;
}