#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }
    node(int data,node* next){

        this->data=data;
        this->next=next;
    }
};

node* convert_arr_to_ll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

void print(node * head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int length(node *head){
    node *slow=head;
    node *fast=head;
    int length=1;
    while(fast != NULL && fast->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;

        if(slow==fast){
            // while(slow!=fast){          // This condition won't work because slow is already equal to first in first pass
            slow=slow->next;
            while(slow!=fast){
                length++;
                slow=slow->next;
            }
            return length;
        }
    }
    return 0;
}

int main(){
    vector <int>nums={2,3,3,4,7,9};
    node* head = convert_arr_to_ll(nums);

    // Creating a loop manually
    node* temp = head;
    node* thirdNode = NULL;

    int count = 1;
    while(temp->next != NULL){

        if(count == 3){
            thirdNode = temp;  // store 3rd node
        }

        temp = temp->next;
        count++;
    }

    temp->next = thirdNode;  // last node points to 3rd node
    cout<<boolalpha;
    cout<<"The length of the loop is : "<<length(head);
    return 0;
}