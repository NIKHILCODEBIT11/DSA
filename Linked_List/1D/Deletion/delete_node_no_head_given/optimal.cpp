#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;

    node(int data){
        this->data = data;
        this->next = nullptr;
    }

    node(int data , node* next){
        this->data = data;
        this->next = next;
    }
};

node* convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node* mover = head;

    for(int i=1 ; i<nums.size() ; i++){
        node* temp = new node(nums[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

void print(node* head){
    node* temp = head;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

void delete_given_node(node* delete_node){
    delete_node->data = delete_node->next->data;
    delete_node->next = delete_node->next->next;
}

int main(){
    vector <int> nums = {2,3,5,6,7,9};
    node* head = convert_arr_to_ll(nums);
    print(head);
    node *node_to_delete = head->next->next->next;
    delete_given_node(node_to_delete);
    print(head);
    return 0;
}