#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    node(int data,node* next){
        this->data=data;
        this->next=next;
    }
};

node* convert_arr_to_ll(vector <int> &nums){
    node *head = new node(nums[0]);
    node * prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *remove(node *head, int n){
    node *slow = head;
    node *fast = head;
    for(int i=0;i<n;i++){
        fast=fast->next;
    }

    if(fast==NULL){
        node * new_head = head->next;
        delete(head);
        return new_head;
    }

    while(fast->next!=nullptr){
        slow=slow->next;
        fast=fast->next;
    }

    node *temp = slow->next;
    slow->next=slow->next->next;
    delete temp;

    return head;
}

void print(node *head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int main(){
    vector <int> nums={2,3,4,5,6,7};
    node *head=convert_arr_to_ll(nums);
    print(head);
    head=remove(head,2);
    print(head);
    return 0;
}