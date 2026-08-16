#include<bits/stdc++.h>
using namespace std;

// Sorted dll

class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data = data;
        this->next = nullptr;
    }
    node(int data,node* next){
        this->data = data;
        this->next = next;
    }
};

node *convert_arr_to_ll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
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

node* find_kth_node(node* head,int n){
    node* temp = head;
    n--;
    while(n>0){
        n--;
        temp = temp->next;
    }
    return temp;
}

node* rotate(node* head,int k){
    // calculate length and tail in a single traversal
    node* tail = head;
    int len = 1;
    while(tail->next!=NULL){
        tail = tail->next;
        len++;
    }
    cout<<"Length is "<<len<<endl;
    cout<<"Tail is "<<tail->data<<endl;

    // Edge case for handling "k" as multiples of len
    if(k%len == 0){
        return head;
    }
    k=k%len;

    // Rest all cases
    tail->next = head;
    node* new_tail = find_kth_node(head,len-k);
    node* new_head = new_tail->next;
    new_tail->next = nullptr;
    head = new_head;
    return head;
}

int main(){
    vector<int> nums = {2,3,6,7,9,3,4};
    node* head = convert_arr_to_ll(nums);
    print(head);
    head = rotate(head,49);
    print(head);
    return 0;
}