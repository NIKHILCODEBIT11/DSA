#include<bits/stdc++.h>
using namespace std;

/*

I took 2 ll and added each individual elements using the condition
1. Till LL_1 gets empty
2. Till LL_2 gets empty
3. Till carray is equal to 0

I initialize sum and carry with 0, and keep on moving

My traversal will stop only if all the condition matches
and  i am storing ans in a new ll starting with dummy node

*/
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

node* add(node* head_1,node* head_2){
    node *temp_1 = head_1;
    node* temp_2 = head_2;
    int sum=0,carry=0;
    node *dummy = new node(0);
    node *temp = dummy;
    while(temp_1!=nullptr || temp_2!=nullptr || carry!=0){
        sum = 0;
        if(temp_1!=NULL){
            sum+=temp_1->data;
            temp_1 = temp_1->next;
        }
        if(temp_2!=NULL){
            sum+=temp_2->data;
            temp_2 = temp_2->next;
        }
        sum+=carry;
        carry = sum/10;
        node *new_node_ans = new node(sum%10);
        temp->next = new_node_ans;
        temp = temp->next;
    }
    return dummy->next;
}

int main(){
    vector <int> nums_1 = {2,3,4,7};
    vector <int> nums_2 = {4,6,9};
    node* head_1 = convert_arr_to_ll(nums_1);
    node* head_2 = convert_arr_to_ll(nums_2);
    node *head = add(head_1,head_2);
    print(head);
    return 0;
}