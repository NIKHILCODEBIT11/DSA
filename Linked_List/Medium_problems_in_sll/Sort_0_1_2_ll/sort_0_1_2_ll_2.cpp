#include<bits/stdc++.h>
using namespace std;

/*

APPROACH :-
I will create 3 ll with DUMMY HEAD NODES with name of head "zero_head" ....
and make three temp node pointing to head of each created ll named as "zero" .....
Then i will traverse from the og ll using temp and will check for data if it's 0 then zero->next points to temp .....
after completing traversal in og node, "zero","one","two" will be present at end of respective ll, then only i have to point "zero" to the next node of "one", as first node is dummy .....

*/

class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    node(int data, node *next){
        this->data = data;
        this-> next = next;
    }
};

node *convert_arr_to_ll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i]);
        prev->next = temp;
        prev=temp;
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

node *sort_ll(node *head){

    if(head==NULL || head->next == nullptr){            // if(!head || !head->next)         can also be written
        return head;
    }

    node *zero_head = new node(-1);
    node * one_head = new node(-1);
    node * two_head = new node(-1);
    node *zero = zero_head,*one = one_head,*two = two_head;
    node *temp = head;
    while(temp!=NULL){
        if(temp->data == 0){
            zero->next = temp;
            zero = temp;
        }
        else if(temp -> data == 1){
            one->next = temp;
            one = temp;
        }
        else{
            two->next = temp;
            two = temp;
        }
        temp = temp->next;
    }
    zero->next = (one_head->next!=NULL) ? one_head->next : two_head->next;

    /*
    
    if (one_head->next != NULL) {
    zero->next = one_head->next;
}
else {
    zero->next = two_head->next;
}

    
    */

    one->next = two_head->next;

    two->next = NULL;

    // Returning head
    node *new_head = (zero_head->next!=NULL) ?
                     zero_head->next :
                     (one_head->next!=NULL) ? one_head->next : two_head->next;

    return new_head;
    delete(zero_head);
    delete one_head;
    delete(two_head);
}

// Above ternary operator for new_head is same as below :-

/*

node *new_head;

if (zero_head->next != NULL) {
    new_head = zero_head->next;
}
else {
    if (one_head->next != NULL) {
        new_head = one_head->next;
    }
    else {
        new_head = two_head->next;
    }
}

*/

int main(){
    vector <int> nums = {1,2,0,0,2,2,1,2,1,1,0,1,0,2,1};
    node *head = convert_arr_to_ll(nums);
    print(head);
    head = sort_ll(head);
    print(head);
    return 0;
}

