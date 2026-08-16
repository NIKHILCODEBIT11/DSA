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
    node(int data,node* next){

        this->data=data;
        this->next=next;
    }
};

node* convert_arr_to_ll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

void print(node * head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

bool check_palindrome(node *head){

    /*
    What is a palindrome?

    A linked list is palindrome if:
    First value == Last value
    Second value == Second last value
    and so on.

    Example:
    2 → 3 → 3 → 4 → 3 → 3 → 2

    Read forward  : 2 3 3 4 3 3 2
    Read backward : 2 3 3 4 3 3 2
    Same → So palindrome.
    */


    stack<int> st;     // We store VALUES, not nodes.

    node* temp = head;

    /*
    STEP 1:
    Push all node values into stack.

    Why stack?
    Because stack gives reverse order (LIFO).
    */

    while(temp != NULL){
        st.push(temp->data);   // store data only
        temp = temp->next;
    }


    /*
    Now stack contains:

    top → 2
           3
           3
           4
           3
           3
           2
    */

    temp = head;

    /*
    STEP 2:
    Traverse list again.
    Compare each node's data with stack top.

    Stack top gives last element.
    So we are comparing:
        first with last
        second with second-last
    */

    while(temp != NULL){

        /*
        ❓ YOUR QUESTION:
        Why can’t we use:

            temp != st.top()

        ANSWER:
        Because that compares memory addresses (node identity).

        In palindrome we don’t care if nodes are same object.
        We only care if their VALUES are same.

        Example:
        First 2 and Last 2 are different nodes
        (different memory addresses),
        but values are same.
        */

        if(temp->data != st.top()){
            return false;   // values not matching → not palindrome
        }

        st.pop();          // remove matched value
        temp = temp->next;
    }

    return true;   // All values matched
}

int main(){
    vector <int> nums={2,3,3,4,3,3,2};
    node *head=convert_arr_to_ll(nums);
    cout<<boolalpha;
    cout<<"Palindrome exists :- "<<check_palindrome(head);
    return 0;
}