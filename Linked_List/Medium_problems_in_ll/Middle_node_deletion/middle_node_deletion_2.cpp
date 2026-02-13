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

// The logic used is skip the first time fast moves 2 steps and after first step from next step onward perform general approach of lsow moves  step and fast moves 2 steps
node *middle_deletion(node * head){

    if(head == NULL || head->next == nullptr){
        delete head;            //     or can be written as     delete(head)
        return NULL;
    }
    
    node * slow =head;
    node * fast = head;
    fast = fast->next->next;        // I wrote it here because i want to skip "slow" from moving for one time, so i am stopping "slow" to move in 1st step
    while(fast!=NULL && fast->next!=nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    node * middle = slow->next;
    slow->next = slow->next->next;
    delete(middle);
    return head;
}

int main(){
    vector <int> nums = {2,3,4,7,9,7};
    node * head = convert_arr_to_ll(nums);
    print(head);
    head = middle_deletion(head);
    print(head);
    return 0;
}