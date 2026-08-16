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

node* delete_kthnode(node* head , int position){

    // What if the ll is empty :-
    if(head == nullptr){
        return head;
    }
    if( position == 1){
        node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    
    int count = 0;
    node* temp = head;
    node* prev = nullptr;

    while(temp!=NULL){
        count++;
        if( count == position){
            prev->next = temp->next;
            delete(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

int main(){
    vector <int> nums = {2,3,5,6,7,9};
    node* head = convert_arr_to_ll(nums);
    print(head);
    head = delete_kthnode(head , 1);
    print(head);
    return 0;
}
