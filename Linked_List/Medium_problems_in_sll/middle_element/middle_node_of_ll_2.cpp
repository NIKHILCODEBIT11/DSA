#include<bits/stdc++.h>
using namespace std;

// Optimal approach   :-    Tortoise hare method
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

node * convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *middle(node *head){

    // Edge case:
    // If list is empty OR only one node is present,
    // head itself is the middle.
    if(head == NULL || head->next == NULL){
        return head;
    }

    /*
    TORTOISE–HARE METHOD (Slow–Fast Pointer Technique)

    IDEA:
    -----
    We use two pointers:
        slow  -> moves 1 step at a time (like tortoise 🐢)
        fast  -> moves 2 steps at a time (like hare 🐇)

    Since fast moves twice as quickly,
    when fast reaches the end,
    slow will be exactly at the middle.

    WHY IT WORKS?
    -------------
    If fast moves 2 nodes per iteration
    and slow moves 1 node per iteration,

    That means:
        distance covered by fast = 2 × distance covered by slow

    So when fast finishes traversing the list,
    slow would have covered half the list.
    Therefore slow = middle node.
    */

    node *slow = head;   // 🐢 moves 1 step
    node *fast = head;   // 🐇 moves 2 steps


    /*
    LOOP CONDITION:
    ----------------
    fast != NULL           → ensures fast is valid
    fast->next != NULL     → ensures fast can move 2 steps safely

    We check this because fast moves two steps:
        fast = fast->next->next
    */

    while(fast != NULL && fast->next != NULL){

        slow = slow->next;            // move 1 step
        fast = fast->next->next;      // move 2 steps
    }

    /*
    WHEN LOOP ENDS:
    ---------------
    fast becomes NULL OR fast->next becomes NULL

    At that moment:
        slow is at middle node.

    IMPORTANT:
    ----------
    If number of nodes is EVEN:
        It returns (n/2 + 1)th node
        → i.e., SECOND middle

    If number of nodes is ODD:
        It returns exact middle node
    */

    return slow;
}


void print(node *head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_ll(nums);
    print(head);
    node * ans = middle(head);
    cout<<"The middle node is "<<ans->data<<endl;
    return 0;
}