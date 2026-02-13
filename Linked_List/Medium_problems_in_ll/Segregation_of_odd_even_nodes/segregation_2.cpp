#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    node(int data,node* next){
        this->data=data;
        this->next=next;
    }
};

node* convert_arr_to_ll(vector <int> &nums){
    node *head = new node(nums[0]);
    node * prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

void print(node *head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

node *segregate(node *head){        // 2   3   5  7   9   6
    node *odd = head;
    node *even = head->next;
    node *evenhead = even;            // Try with   evenhead = even;
    while(even!=NULL && even->next!=NULL){            //   "even" is always ahead of "odd"
        odd->next = odd->next->next;
        even->next = even->next->next;

        odd=odd->next;
        even=even->next;
    }
    odd->next = evenhead;
    return head;
}

int main(){
    vector <int> nums={2,3,4,5,6,7};
    node *head=convert_arr_to_ll(nums);
    print(head);
    node *ans=segregate(head);
    print(head);
    return 0;
}