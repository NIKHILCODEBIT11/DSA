#include<bits/stdc++.h>
using namespace std;


// See below comment for understanding

class node{
    public :
    int data;
    node *back;
    node *next;

    node(int data,node *next,node *back){
        this->data=data;
        this->next=next;
        this->back=back;
    }

    node(int data){
        this->data=data;
        this->next=nullptr;
        this->back=nullptr;
    }
};

void print(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

node *convert_arr_to_dll(vector <int> &nums){
    node *head = new node(nums[0]);
    node *prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp=new node(nums[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

void Insert_before_given_node(node *given_node,int val){
    node *prev=given_node->back;
    node *new_node=new node(val,given_node,prev);
    prev->next=new_node;
    given_node->back=new_node;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_dll(nums);
    print(head);
    Insert_before_given_node(head->next,7);
    // cout<<"The deleted node is "<<ans->data<<endl;
    print(head);
    return 0;
}