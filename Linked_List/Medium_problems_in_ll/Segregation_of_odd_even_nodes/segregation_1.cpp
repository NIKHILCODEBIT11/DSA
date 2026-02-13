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

void print(node *head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

node *segregate(node * head){           //    2    3   5    7   9   10
    vector <int> nums;
    node *temp = head;

    // Inserting odd nodes to arr
    while(temp!=NULL && temp->next!=NULL){
        nums.push_back(temp->data);
        temp=temp->next->next;
    }
    if(temp){
        nums.push_back(temp->data);
    }

    // Inserting even nodes to arr
    temp = head->next;
    while(temp!=NULL && temp->next!=NULL){
        nums.push_back(temp->data);
        temp=temp->next->next;
    }
    if(temp){
        nums.push_back(temp->data);
    }

    // Segregation :-
    temp = head;
    int i=0;
    while(temp!=NULL){
        temp->data=nums[i];
        i++;
        temp=temp->next;
    }
    return head;
}

int main(){
    vector <int> nums={2,3,3,4,3,3,7};
    node *head=convert_arr_to_ll(nums);
    print(head);
    node *ans=segregate(head);
    print(head);
    return 0;
}