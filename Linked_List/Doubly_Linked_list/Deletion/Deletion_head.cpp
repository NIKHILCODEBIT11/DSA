#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node *next;
    node *back;

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

node *convert_arr_to_dll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev = head;

    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr,prev);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

void print(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

node *deletehead(node *head){

    if(head==NULL || head->next == NULL){
        return NULL;
    }
    node *prev = head;
    head=head->next;
    head->back=nullptr;

    prev->next=nullptr;         // This can also be ignored written only for concept clarity
    delete prev;
    return head;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_dll(nums);
    print(head);
    head = deletehead(head);
    cout<<"The new head is "<<head->data<<endl;
    print(head);
    return 0;
}