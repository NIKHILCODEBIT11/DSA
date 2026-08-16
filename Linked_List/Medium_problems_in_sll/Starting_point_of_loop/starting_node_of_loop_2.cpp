#include<bits/stdc++.h>
using namespace std;

// Optimal approach :-    using          "Tortoise and hare"       algorithm
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

node* start_loop(node *head){

    // Step 1: Initialize two pointers
    // slow  -> moves 1 step at a time (Tortoise)
    // fast  -> moves 2 steps at a time (Hare)

    node *slow = head;
    node *fast = head;

    /*
        Imagine linked list:

        2 → 3 → 3 → 4 → 7 → 9
                 ↑           ↓
                 ← ← ← ← ← ← ←

        Suppose loop starts at 3 (3rd node)
    */

    // STEP A: Detect if loop exists
    while(fast != NULL && fast->next != NULL){

        slow = slow->next;          // move 1 step
        fast = fast->next->next;    // move 2 steps

        /*
            Why does this detect loop?

            If there is NO loop:
            fast will reach NULL first.
            So loop does not exist.

            If there IS a loop:
            fast moves faster than slow,
            so inside the loop it will
            eventually catch slow.

            Just like running on circular track:
            Fast runner will meet slow runner.
        */

        if(slow == fast){   // They met inside loop
            /*
                IMPORTANT:
                This meeting point is NOT
                necessarily the starting node.

                Now we use mathematical trick
                to find starting node.
            */

            // STEP B: Move slow back to head
            slow = head;

            /*
                Now:

                slow → at head
                fast → at meeting point

                Move BOTH one step at a time.

                The point where they meet again
                will be the START of the loop.
            */

            while(slow != fast){
                slow = slow->next;
                fast = fast->next;
            }

            // Both are now at starting node of loop
            return slow;   // (or return fast)
        }
    }

    // If fast reached NULL → no loop
    return NULL;
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
    node* loopNode = start_loop(head);
    if(loopNode != NULL){
        cout << "The loop in ll starts from " << loopNode->data;
    }
    else{
        cout << "No loop present";
    }
    return 0;
}