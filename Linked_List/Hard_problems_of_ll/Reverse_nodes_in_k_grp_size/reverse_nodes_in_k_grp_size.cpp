#include<bits/stdc++.h>
using namespace std;

// Sorted dll

class node{
    public:
    int data;
    node *next;
    node* back;

    node(int data){
        this->data = data;
        this->next = nullptr;
        this->back = nullptr;
    }
    node(int data,node* next,node* back){
        this->data = data;
        this->next = next;
        this->back = back;
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

void print(node* head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

node* kth_node(node* temp,int k){
    k--;
    while(temp!=NULL && k>0){
        k--;
        temp = temp->next;
    }
    return temp;
}

node* reverse(node* temp){          //      1   3   4
    node* temp_1 = temp;
    node* previous = nullptr;
    node* front = temp_1->next;
    while(temp_1 != NULL){
        temp_1->next = previous;
        temp_1->back = front;
        previous = temp_1;
        temp_1 = temp_1->next;
        front = temp_1->next;
    }
    return temp;
}

node* reverse_nodes_k_size(node* head,int k){
    node* temp = head;
    node* k_node;
    node* prev_reversed_node = NULL;
    node* next_unreversed_node;
    while(temp!=NULL){
        k_node = kth_node(temp,k);
        if(k_node){
            prev_reversed_node = temp;
            break;
        }
        next_unreversed_node = k_node->next;
        k_node->next = NULL;
        reverse(temp);  

    }
}