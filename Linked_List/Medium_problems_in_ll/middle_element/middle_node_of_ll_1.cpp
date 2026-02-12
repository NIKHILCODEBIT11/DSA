#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE approach :-

// If total nodes are 7(odd) nodes      return    4th node
// If total nodes are 6(even) nodes,then there will be 2 middle nodes   m1=3rd node and m2=4th node   so return m2

// Always i have to return       (n/2)+1 th       node, where n is size of the linkedlist

class node{
    public:
    int data;
    node *next;
    node* back;

    node(int data){
        this->data=data;
        this->next=nullptr;
        this->back=nullptr;
    }

    node(int data,node *next,node *back){
        this->data=data;
        this->next=next;
        this->back=back;
    }
};

node * convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *middle(node *head){
    int size=0;
    node *temp=head;
    while(temp!=NULL){
        size++;
        temp=temp->next;
    }

    temp=head;
    int mid = (size/2)+1;

    while(temp!=NULL){
        mid = mid-1;
        if(mid==0){
            break;
        }
        temp=temp->next;
    }
    return temp;
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
    node * ans = middle(head);
    cout<<"The middle node is "<<ans->data<<endl;
    return 0;
}