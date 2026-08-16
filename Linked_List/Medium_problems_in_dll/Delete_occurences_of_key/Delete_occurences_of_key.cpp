#include<bits/stdc++.h>
using namespace std;

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

node* delete_key(node* head,int key){
    node* temp = head;
    node* next_node,* prev_node;
    while(temp!=NULL){
        if(temp->data == key){
            if(temp == head){
                head = head->next;
            }
            next_node = temp->next;
            prev_node = temp->back;
            if(next_node){
                next_node->back = prev_node;
            }
            if(prev_node){
                prev_node->next = next_node;
            }
            delete(temp);
            temp = next_node;
        }
        else{
            temp = temp->next;
        }
    }
    return head;
}

int main(){
    vector <int> nums = {2,3,2,4,6,2};
    node *head = convert_arr_to_dll(nums);
    print(head);
    head = delete_key(head,2);
    print(head);
    return 0;
}