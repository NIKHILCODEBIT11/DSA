#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;

    node(int data){
        this->data = data;
        this->next = nullptr;
    }

    node(int data , node* next){
        this->data = data;
        this->next = next;
    }
};

node* convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node* mover = head;

    for(int i=1 ; i<nums.size() ; i++){
        node* temp = new node(nums[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

void print(node* head){
    node* temp = head;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

node* insert_at_kth_pos(node* head , int value , int position){

    if( head == nullptr){
        if( position == 1){
            return new node(value);
        }
        else{
            return head;
        }
    }

    if( position == 1){
        return new node(value , head);
    }

    int count = 0;
    node* temp = head;
    while(temp != nullptr){
        count++;
        if(count == position - 1){
            node* new_node = new node(value , temp->next);
            temp->next = new_node;
            break;
        }
        temp = temp->next;
    }
    return head;
}

int main(){
    vector<int> nums = {2,3,4,6,7};
    node* head = convert_arr_to_ll(nums);
    print(head);
    head = insert_at_kth_pos(head, 4 , 3);
    print(head);
    return 0;
}

/*

You are exactly right! Because this is an insertion function, you don't want to delete anything. 
Your goal is to add new memory to the heap, not free it.

Since you are adding a node to the end of the list, your code is doing exactly what it's supposed 
to do: allocating a new piece of memory (new node(value)) and connecting it to the chain.

The only time you ever need to use delete inside a function is when your goal is to remove data 
(like delete_head, delete_tail, or delete_kth_element). For insertion operations, there is 
absolutely nothing to delete! You nailed it.

*/