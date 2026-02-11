#include<bits/stdc++.h>
using namespace std;


// See below comment for understanding

class node{
    public :
    int data;
    node *back;
    node *next;

    node(int data,node *next,node *back){
        this->data=data;
        this->next=next;
        this->back=back;
    }

    node(int data){
        this->data=data;
        this->next=nullptr;
        this->back=nullptr;
    }
};

void print(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

node *convert_arr_to_dll(vector <int> &nums){
    node *head = new node(nums[0]);
    node *prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp=new node(nums[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}


node *deletehead(node *head){

    if(head==NULL || head->next == NULL){
        return NULL;
    }
    node *prev = head;
    head=head->next;
    head->back=nullptr;

    prev->next=nullptr;         // This can also be ignored written only for concept clarity
    delete prev;
    return head;
}

node *deletetail(node *head){

    if(head==NULL || head->next == NULL){
        return NULL;
    }
    node *tail = head;

    // Traverse to the end
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    node *prev = tail->back;
    tail->back = nullptr;
    prev->next=nullptr;
    delete tail;
    tail=prev;
    return tail;
}

node *delete_knode(node *head,int k){
    if(head==NULL){
        return NULL;
    }
    int count=0;
    node *knode = head;
    while(knode!=NULL){
        count++;
        if(count==k){
            break;
        }
        knode=knode->next;
    }

    if(knode->back==nullptr && knode->next==nullptr){
        return NULL;
    }
    else if(knode->next==nullptr){
        return deletetail(head);
    }
    else if(knode->back==nullptr){
        return deletehead(head);
    }
    knode->back->next = knode->next;
    knode->next->back = knode->back;

    knode->next=nullptr;
    knode->back=nullptr;

    // auto ans = knode->data;           Think what can i do to return deleted node value
    delete knode;
    return head;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_dll(nums);
    print(head);
    delete_knode(head,4);
    // cout<<"The deleted node is "<<ans->data<<endl;
    print(head);
    return 0;
}



/*
==============================================
IMPORTANT RULE ABOUT delete AND RETURNING NODES
==============================================

In C++, once you do:

    delete ptr;

the memory pointed by `ptr` is FREED.

After that:
- ptr becomes a dangling pointer
- accessing ptr->data is UNDEFINED BEHAVIOR
- program may crash / print garbage / appear to work

So:
❌ You CANNOT safely return a deleted node pointer
❌ You CANNOT use a node after deleting it
*/

/*
========================================================
WAY 1 (BEST & MOST COMMON): RETURN THE DATA OF THE NODE
========================================================

Idea:
- Delete the node
- But before deleting, store its data
- Return only the value, NOT the node

Why this is good:
- No dangling pointer
- Clean ownership
- Very commonly used in interviews & real code
*/

//int delete_knode_and_return_data(node*& head, int k) {

    /*
    Find k-th node (logic omitted for clarity)
    Suppose `curr` is the k-th node
    */

    //int deletedValue = curr->data;  // save data BEFORE delete
    //delete curr;                    // free memory
    //return deletedValue;            // SAFE
//}

/*
Usage:
int val = delete_knode_and_return_data(head, 4);
cout << val;
*/


/*
========================================================
WAY 2: RETURN A COPY OF THE NODE (RARELY USED)
========================================================

Idea:
- Make a NEW node with same data
- Delete the original node
- Return the COPY

Why this works:
- Returned node lives in new memory
- Deleted memory is not accessed

Why rarely used:
- Extra allocation
- Usually unnecessary
*/

//node* delete_knode_and_return_copy(node*& head, int k) {

    /*
    Find k-th node → curr
    */

    //node* copy = new node(curr->data);  // make copy
    //delete curr;                         // delete original
    //return copy;                         // SAFE (caller must delete)
//}

/*
Caller responsibility:
node* removed = delete_knode_and_return_copy(head, 4);
cout << removed->data;
delete removed;
*/


/*
========================================================
WAY 3: RETURN NODE POINTER BUT DO NOT DELETE IT
(OWNERSHIP TRANSFER)
========================================================

Idea:
- Function ONLY unlinks the node from list
- DOES NOT delete it
- Caller becomes responsible for deletion

Why this works:
- Node is still alive
- No dangling pointer
- Very explicit ownership
*/

//node* detach_knode_and_return(node*& head, int k) {

    /*
    Find k-th node → curr
    */

    // unlink from list
    //if (curr->back) curr->back->next = curr->next;
    //if (curr->next) curr->next->back = curr->back;

    // fully detach node
    //curr->next = nullptr;
    //curr->back = nullptr;

    //return curr;   // SAFE (still allocated)
//}

/*
Caller MUST delete:
node* removed = detach_knode_and_return(head, 4);
cout << removed->data;
delete removed;
*/


/*
========================================================
WHAT IS NEVER ALLOWED (VERY IMPORTANT)
========================================================

❌ NEVER do this:

node* temp = curr;
delete curr;
return temp;   // DANGLING POINTER

❌ NEVER access node after delete:
delete curr;
cout << curr->data;   // UNDEFINED BEHAVIOR

❌ NEVER delete twice:
delete curr;
delete curr;   // CRASH / UB
*/


/*
========================================================
GOLDEN RULE (MEMORIZE THIS)
========================================================

If a function DELETEs memory,
→ it must NOT return that pointer.

If a function RETURNS a pointer,
→ it must NOT delete it.

Ownership must be CLEAR.
*/


/*
========================================================
WHAT PROFESSIONAL CODE USUALLY DOES
========================================================

✔ Return updated head
✔ Return deleted value (int / data)
✔ Or use ownership transfer pattern
✔ Or use smart pointers (unique_ptr)

Returning deleted pointers is NEVER done.
*/
