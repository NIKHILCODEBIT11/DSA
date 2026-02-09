#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node *next;

    node(int data,node *next){
        this->data=data;
        this->next=next;
    }
    node(int data){
        this->data=data;
        this->next=nullptr;
    }
};

node *convert_arr_to_1D(vector <int>&nums){
    node *head=new node(nums[0]);
    node *mover = head;
    for(int i=1;i<nums.size();i++){
        node *temp=new node(nums[i]);
        mover->next=temp;
        mover=temp;
    }
    return head;
}

bool search_element(node *head,int target){
    node *temp=head;
    while(temp){
        if(temp->data == target){
            return true;
        }
        temp=temp->next;
    }
    return false;
}

int main(){
    vector <int>nums={2,3,4,7,9};
    node* head=convert_arr_to_1D(nums);
    cout<<boolalpha;
    cout<<"The target value is present :- "<<search_element(head,4);
    return 0;
}