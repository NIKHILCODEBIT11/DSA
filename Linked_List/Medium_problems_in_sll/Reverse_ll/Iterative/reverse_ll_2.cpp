#include<bits/stdc++.h>
using namespace std;

// Optimal approach :-

// The bruteforce approach is of using stack as did for doublylinkedlist
class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    node(int data,node *next){
        this->data=data;
        this->next=next;
    }
};

node * convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i]);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *reverse(node *head){
    node *temp=head;
    node *prev=nullptr;
    node* front;
    while(temp!=NULL){
        front=temp->next;
        temp->next=prev;
        prev=temp;
        temp=front;
    }
    return prev;
}


void print(node *head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_ll(nums);
    print(head);
    node * ans = reverse(head);
    cout<<"The new head node is "<<ans->data<<endl;
    print(ans);
    return 0;
}