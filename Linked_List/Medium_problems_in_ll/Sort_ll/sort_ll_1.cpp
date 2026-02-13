#include<bits/stdc++.h>
using namespace std;

// In this approach, i will put all data of ll in a vector and then sort that vector then will traverse through both ll and vector and will put value from vector to ll

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

node* sort_ll(node * head){
    vector <int> nums;
    node *temp = head;
    while(temp!=NULL){
        nums.push_back(temp->data);
        temp = temp->next;
    }
    sort(nums.begin() , nums.end());

    temp = head;
    int i=0;
    while(temp!=NULL){
        temp->data = nums[i];
        i++;
        temp=temp->next;
    }
    return head;
}


int main(){
    vector <int> nums = {4,3,7,9,2};
    node * head = convert_arr_to_ll(nums);
    print(head);
    head = sort_ll(head);
    print(head);
    return 0;
}