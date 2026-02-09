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

int length_ll(node *head){
    int count=0;
    node *temp=head;
    while(temp){
        cout<<temp->data<<" ";
        temp=temp->next;
        count++;
    }
    return count;
}

int main(){
    vector <int> nums={2,3,4,7,9};
    node *head=convert_arr_to_1D(nums);
    cout<<"The length of linked list is "<<length_ll(head);
    return 0;
}