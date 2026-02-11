#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE approach :-

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

node *reverse_ll(node *head){
    
    // Step 1 :- Pushing elements to stack;
    stack<int> st;
    node *temp=head;
    while(temp!=NULL){
        st.push(temp->data);
        temp=temp->next;
    }

    // Step 2 :- Popping element from stack
    temp=head;
    while(temp!=NULL){
        temp->data=st.top();
        st.pop();
        temp=temp->next;
    }
    return head;
}

void print(node* head){
    node *temp=head;
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
    node * ans = reverse_ll(head);
    print(head);
    cout<<"The new head is "<<ans->data<<endl;
    return 0;
}