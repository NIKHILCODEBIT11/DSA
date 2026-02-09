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

node *deletetail(node *head){

    if(head==NULL || head->next == NULL){
        return NULL;
    }
    node *tail = head;

    // Traverse to the end
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    node *prev = tail->back;
    tail->back = nullptr;
    prev->next=nullptr;
    delete tail;
    tail=prev;
    return tail;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_dll(nums);
    print(head);
    node *tail = deletetail(head);
    cout<<"The new tail is "<<tail->data<<endl;
    print(head);
    return 0;
}