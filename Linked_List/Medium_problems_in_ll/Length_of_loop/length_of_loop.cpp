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

int length(node *head){

    node* temp = head;

    int timer = 0;

    // map stores:
    // key   -> node address
    // value -> step number when node was first visited
    map<node*, int> m;


    /*
    Example Linked List with Loop:

           1 → 2 → 3 → 4 → 5
                    ↑       ↓
                    ← ← ← ← ←

    Suppose memory addresses are:

    1 -> 100
    2 -> 200
    3 -> 300
    4 -> 400
    5 -> 500

    Loop starts at node 3 (address 300)

    Goal:
    Find length of loop = number of nodes inside cycle
    Here: 3 → 4 → 5 → back to 3
    Length = 3
    */


    while(temp != NULL){

        /*
        STEP 1:
        Check if we have already visited this node.
        If yes → loop detected.
        */

        if(m.find(temp) != m.end()){

            /*
            Suppose we revisit node 3 again.

            First time we visited 3:
                timer = 2
                m[300] = 2

            When we come back again:
                current timer = 5

            Loop length = current_timer - first_timer

            = 5 - 2
            = 3

            Which is correct loop size.
            */

            return timer - m[temp];
        }

        /*
        STEP 2:
        If not visited before,
        store node address and current step.
        */

        m[temp] = timer;

        /*
        Map after each iteration (example):

        Iteration 0:
            temp = 1
            m = {100 → 0}

        Iteration 1:
            temp = 2
            m = {100 → 0, 200 → 1}

        Iteration 2:
            temp = 3
            m = {100 → 0, 200 → 1, 300 → 2}

        Iteration 3:
            temp = 4
            m = {100 → 0, 200 → 1, 300 → 2, 400 → 3}

        Iteration 4:
            temp = 5
            m = {100 → 0, 200 → 1, 300 → 2, 400 → 3, 500 → 4}

        Iteration 5:
            temp = 3 again
            300 already exists in map
            LOOP FOUND
        */


        timer++;               // move step counter forward
        temp = temp->next;     // move to next node
    }

    /*
    If we reach NULL,
    that means no loop exists.
    */

    return 0;
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
    cout<<"The length of the loop is : "<<length(head);
    return 0;
}