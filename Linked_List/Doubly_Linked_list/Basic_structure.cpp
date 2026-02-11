#include<bits/stdc++.h>
using namespace std;


/*
SINGLY LINKED LIST

head
 ↓
[data | next] → [data | next] → [data | next] → nullptr


DOUBLY LINKED LIST

nullptr ← [prev | data | next] ⇄ [prev | data | next] ⇄ [prev | data | next] → nullptr
                   ↑
                 head
*/


/*

A doubly linked list is a linear data structure in which each node contains:

-----> data

-----> a pointer to the previous node

-----> a pointer to the next node

This allows bidirectional traversal (forward and backward).

*/

class node{
    public :
    int data;
    node *next;
    node *back;

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

int main(){
    vector <int> nums={2,3,4,6,7,9};
    node *head = new node(nums[0]);
    cout<<head->data;
    return 0;
}


/*

To convert array to         "DLL"       use this :-

node * convert_arr_to_dll(vector <int>& nums){

    node* head = new node(nums[0]);
    node* prev = head;

    for(int i = 1; i < nums.size(); i++){

        node* temp = new node(nums[i]);

        prev->next = temp;   // forward link
        temp->back = prev;   // backward link  🔥 IMPORTANT

        prev = temp;
    }

    return head;
}


*/