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

node* delete_head(node* head){

    // What if the ll is empty :-
    if(head == nullptr){
        return nullptr;
    }
    node* temp = head;
    head = temp->next;      // I could also write      head = head->next 
    delete temp;     // I could also write       temp->next = nullptr;
    return head;
}

int main(){
    vector <int> nums = {2,3,5,6,7,9};
    node* head = convert_arr_to_ll(nums);
    print(head);
    head = delete_head(head);
    print(head);
    return 0;
}

/*
1. What temp->next = nullptr; does:
This only breaks the link connecting the first node to the second node. It modifies a variable 
inside the node. However, the node itself still sits alive on the heap. If you don't call delete, 
you are still leaking that memory.

2. What delete temp; does:
This completely blows up the entire node object on the heap and returns that memory back to the 
computer.

Because delete temp; completely destroys the node anyway, you don't need to clean up its internal 
variables beforehand. Setting temp->next = nullptr right before deleting it is redundant work. 
The computer doesn't care what was inside the box right before it smashes the box.

*/