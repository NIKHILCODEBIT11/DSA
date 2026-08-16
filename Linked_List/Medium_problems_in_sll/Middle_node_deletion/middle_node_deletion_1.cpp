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

    node(int data,node *next){
        this->data=data;
        this->next=next;
    }
};


node *convert_arr_to_ll(vector <int> &nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i]);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

void print(node *head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

node *middle_deletion(node *head){

    if(head == NULL || head->next == NULL){
        delete head;
        return NULL;
    }
    
    node *temp = head;
    int size = 0;
    while(temp!=NULL){
        size++;
        temp = temp->next;
    }

    int mid = size/2;
    temp =head;
    // while(temp!=NULL){
    //     mid--;
    //     if(mid == 0){
    //         break;
    //     }
    //     temp = temp->next;
    // }

    while(mid>1){           // I can write this instead of above while loop too
        mid--;
        temp=temp->next;
    }

    node * middle = temp->next;
    temp->next = temp->next->next;
    delete(middle);
    return head;
}

int main(){
    vector <int> nums = {2,3,4,7,9};
    node * head = convert_arr_to_ll(nums);
    print(head);
    head = middle_deletion(head);
    print(head);
    return 0;
}