#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node *next;
    node *back;

    node(int data){
        this->data=data;
        this->next=nullptr;
        this->back=nullptr;
    }

    node(int data,node *next,node*back){
        this->data=data;
        this->next=next;
        this->back=back;
    }
};

node* convert_arr_to_dll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp=new node(nums[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

void print(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

node *Insert_before_head(node *head,int val){       // Look comment to know why also used Insert_before_head
    node *new_node=new node(val,head,nullptr);
    head->back=new_node;
    head=new_node;
    return head;
}

node *Insert_before_tail(node *head,int val){
    if(head->next==nullptr){
        return Insert_before_head(head,val);
    }
    node* tail=head;
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    node *new_node = new node(val,tail,tail->back);
    tail->back->next=new_node;
    tail->back=new_node;
    return head;
}

int main(){
    vector <int> nums={2};
    node *head=convert_arr_to_dll(nums);
    print(head);
    head = Insert_before_tail(head,4);
    // cout<<"The deleted node is "<<ans->data<<endl;
    print(head);
    return 0;
}

/*
=================================================================
WHY WE MUST HANDLE THE SINGLE-ELEMENT CASE IN DOUBLY LINKED LIST
=================================================================

Consider a doubly linked list with ONLY ONE node:

    head
     ↓
   [2 | back = NULL | next = NULL]

In this case:
- head is also the tail
- There is NO node before tail
- tail->back == NULL

---------------------------------------------------------------
PROBLEM:
---------------------------------------------------------------

If we try to "insert before tail" using general logic:

    tail->back->next = new_node;

This becomes:

    NULL->next = new_node;

Which causes:
❌ segmentation fault
❌ undefined behavior

So the general logic FAILS for a single-node list.
*/


/*
=================================================================
WHAT TO DO WHEN ONLY A SINGLE ELEMENT IS PRESENT
=================================================================

Condition to detect single-node list:

    head->next == NULL

This means:
- Only one node exists
- head == tail

---------------------------------------------------------------
CORRECT ACTION:
---------------------------------------------------------------

If we want to insert BEFORE the tail:

    Before:  [2]
    After :  [4] <-> [2]

Steps:
1. Create a new node
2. new_node->next = head
3. new_node->back = NULL
4. head->back = new_node
5. Update head to new_node

The new node becomes the NEW HEAD.
*/


/*
=================================================================
WHY WE CALL Insert_before_head IN THIS CASE
=================================================================

For a single-node list:
- "Insert before tail"
- and "Insert before head"

are EFFECTIVELY THE SAME operation.

So instead of duplicating logic, we simply:

    return Insert_before_head(head, val);

This:
✔ avoids crashes
✔ keeps code clean
✔ handles edge case correctly
*/


/*
=================================================================
SUMMARY (REMEMBER THIS)
=================================================================

1. A single-node list has:
       head->next == NULL
       head->back == NULL

2. General DLL insertion logic assumes:
       a node BEFORE tail exists

3. Single-node case BREAKS that assumption

4. Therefore:
   - ALWAYS check single-node case
   - Handle it separately
   - Treat it as insertion before head
*/

