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

node *reverse(node *head){              // 2   3    4   7   9    10
    if(head == NULL || head->next==nullptr){
        return head;
    }

    node *new_head = reverse(head->next);
    node *front = head->next;
    front->next = head;
    head->next = nullptr;
    return new_head;
}

node *middle(node *head){
    node * slow = head;
    node * fast = head;

    while(fast->next!=nullptr && fast->next->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

bool check_palindrome(node *head){
    node *mid = middle(head);
    node *new_head=reverse(mid->next);

    node *first=head;
    node *second = new_head;

    while(second!=NULL){
        if(first->data!=second->data){
            reverse(new_head);              // So, that linked list won't get altered   {ORIGINALITY OF GIVEN DATA}
            return false;
        }
        first=first->next;
        second=second->next;
    }
    reverse(new_head);          // So, that linked list won't get altered  {ORIGINALITY OF GIVEN DATA}
    return true;
}

int main(){
    vector <int> nums={2,3,3,4,3,3};
    node *head=convert_arr_to_ll(nums);
    cout<<boolalpha;
    cout<<"Palindrome exists :- "<<check_palindrome(head);
    return 0;
}