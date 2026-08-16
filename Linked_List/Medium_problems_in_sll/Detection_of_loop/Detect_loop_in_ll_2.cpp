#include<bits/stdc++.h>
using namespace std;

// Optimal approach :-   Tortoise and hare approach

// Explaination :-

/*
FLOYD'S CYCLE DETECTION (TORTOISE & HARE)

Example Linked List:

2 → 3 → 3 → 4 → 7 → 9
            ↑       ↓
            ← ← ← ← ←

Loop starts at 3 (3rd node)

-------------------------------------------------------
STEP 1: Two pointers start at head

slow → moves 1 step
fast → moves 2 steps

-------------------------------------------------------
WHY WILL THEY MEET?

Let:

L = distance from head to loop start
C = length of cycle

In our case:

Nodes before loop = 2 → 3  (2 nodes)
So L = 2

Cycle nodes = 3 → 4 → 7 → 9
So C = 4

-------------------------------------------------------
POINTER MOVEMENT VISUALIZATION

Initial:
slow = 2
fast = 2

Iteration 1:
slow → 3
fast → 3 (2 steps)

Iteration 2:
slow → 3 (loop start)
fast → 7

Iteration 3:
slow → 4
fast → 3

Iteration 4:
slow → 7
fast → 7   <-- MEETING POINT

-------------------------------------------------------
WHY DO THEY MEET?

Inside the loop:

slow speed = 1
fast speed = 2

Relative speed = (2 - 1) = 1

That means:
fast gains 1 node per iteration over slow.

Since loop is circular,
fast must eventually catch slow.

Like two runners on circular track:
One runs faster → eventually catches slower runner.

-------------------------------------------------------
WHY "slow == fast" MEANS LOOP?

In a normal linked list (no loop):

1 → 2 → 3 → 4 → 5 → NULL

fast will eventually become NULL.

But if there is a loop:

Traversal never reaches NULL.

So if slow and fast point to SAME MEMORY ADDRESS,
the only possibility is that we are inside a cycle.

Because:
Without cycle, fast can never go backwards
and cannot revisit a node.

-------------------------------------------------------
IMPORTANT MATHEMATICAL INTUITION

After k iterations:

slow distance = k
fast distance = 2k

When they meet:

2k - k = multiple of C
k = multiple of C

Meaning:
Distance difference becomes exactly
cycle length multiple.

So they collide.
*/


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

void print(node *head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

node * convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i]);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

bool detect_loop(node *head){

    /*
    FLOYD'S CYCLE DETECTION ALGORITHM
    ----------------------------------
    Also called:
    Tortoise 🐢 and Hare 🐇 method

    IDEA:
    -----
    Use two pointers:

    slow  -> moves 1 step at a time
    fast  -> moves 2 steps at a time

    If there is NO loop:
        fast will reach NULL.

    If there IS a loop:
        fast will eventually catch slow
        inside the cycle.
    */

    node* slow = head;   // 🐢 moves 1 step
    node* fast = head;   // 🐇 moves 2 steps


    /*
    WHY this condition?

    fast moves 2 steps:
        fast = fast->next->next

    So we must ensure:
        1) fast is not NULL
        2) fast->next is not NULL

    Otherwise segmentation fault.
    */

    while(fast != NULL && fast->next != NULL){

        slow = slow->next;           // move 1 step
        fast = fast->next->next;     // move 2 steps

        /*
        If at any moment:
            slow == fast

        That means both pointers
        are at same memory address.

        This is only possible
        if there is a cycle.
        */

        if(slow == fast){
            return true;   // Loop detected
        }
    }

    /*
    If fast reaches NULL:
        That means list ended normally.
        No cycle exists.
    */

    return false;
}


int main(){
    vector <int>nums={2,3,3,4,7,9};
    node* head = convert_arr_to_ll(nums);

    // Creating a loop manually
    node* temp = head;
    node* thirdNode = NULL;

    int count = 1;
    while(temp->next != NULL){

        if(count == 3){
            thirdNode = temp;  // store 3rd node
        }

        temp = temp->next;
        count++;
    }

    temp->next = thirdNode;  // last node points to 3rd node
    cout<<boolalpha;
    cout<<"The ll is looped : "<<detect_loop(head);
    return 0;
}