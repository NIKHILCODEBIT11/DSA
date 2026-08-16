#include<bits/stdc++.h>
using namespace std;

// Bruteforce approach :-    using          "map"
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
    node *temp=head;
    map <node*,int> m;
    while(temp!=NULL){
        if(m.find(temp)!=m.end()){
            return temp;
        }
        m[temp]=1;
        temp=temp->next;
    }
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