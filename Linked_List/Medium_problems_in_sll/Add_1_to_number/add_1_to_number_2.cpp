#include<bits/stdc++.h>
using namespace std;


/*

Approach :-
I used recursion to get carry for each temp, then returned it to function "add_1" to check if still carry is "0", then no problem otherwise if it is "1", then i would have to add a new head

*/
class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data = data;
        this->next = nullptr;
    }
    node(int data,node *next){
        this->data = data;
        this->next = next;
    }
};

node* convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node *prev = head;
    node* temp;
    for(int i=1;i<nums.size();i++){
        temp = new node(nums[i]);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

void print(node *head){
    node *temp = head;
    while(temp!=0){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

int helper(node* temp){
    if(temp == NULL){
        return 1;
    }
    int carry = helper(temp->next);
    temp->data+=carry;
    if(temp->data < 10){
        return 0;
    }
    else{
        temp->data = 0;
        return 1;
    }
}

node* add_1(node *head){
    int carry = helper(head);
    if(carry == 1){
        node *new_head = new node(1);
        new_head ->next = head;
        return new_head;
    }
    else{
        return head;
    }
}

int main(){
    vector <int> nums = {9,9};
    node *head = convert_arr_to_ll(nums);
    cout<<"Before adding :-\n";
    print(head);
    cout<<"After adding 1 :-\n";
    head = add_1(head);            
    print(head);
    return 0;
}