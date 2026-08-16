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

node* remove_duplicates(node* head){        //  1   1   1   2   3   3   4
    node* temp = head;
    node* next_node;
    while(temp!=nullptr){
        next_node = temp->next;
        while(next_node != nullptr && next_node->data == temp->data){
            node* duplicate = next_node;
            next_node = next_node->next;
            delete(duplicate);
        }
        temp->next = next_node;
        if(next_node){
            next_node->back == temp;
        }
        temp = temp->next;
    }
    return head;
}

int main(){
    vector <int> nums = {1,1,1,2,3,3,4};
    node* head = convert_arr_to_dll(nums);
    print(head);
    remove_duplicates(head);
    print(head);
    return 0;
}