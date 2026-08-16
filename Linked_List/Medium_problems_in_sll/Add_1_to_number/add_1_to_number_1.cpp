#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data = data;
        this->next = nullptr;
    }
    node(int data,node* next){
        this->data = data;
        this->next = next;
    }
};

node *convert_arr_to_ll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

void print(node* head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

node* reverse(node* head){          // ITERATIVE
    if(head==NULL || head->next == nullptr){
        return head;
    }
    node *temp = head;              // 2    3     null
    node *prev = nullptr;
    node* front;
    while(temp!=NULL){
        front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}               

node* add_1(node *head){
    int carry = 1;
    head = reverse(head);     // 918
    node *temp = head;
    while(temp!=nullptr){            //      For condition like      "carry!=0"      it may go to infinite loop as for adding carry to 999, carry will not be 0, unless i manually handle that case
        temp->data+=1;
        if(temp->data < 10){
            carry = 0;
            break;
        }
        else{
            temp->data = 0;
            carry = 1;
        }
        temp = temp->next;
    }

    if(carry == 1){
        head = reverse(head);
        node *new_head = new node(1);
        new_head->next = head;
        return new_head;
    }
    else{               // This is written because in condition when temp->>data < 10, i am just updating the carry to 0 and breaking the "loop" due to which i have to write else so that head could be returned
        head = reverse(head);
        return head;
    }
}

int main(){
    vector <int> nums = {9,9};
    node *head = convert_arr_to_ll(nums);
    cout<<"Before adding :-\n";
    print(head);
    cout<<"After adding 1 :-\n";
    head = add_1(head);            // If i just do   add_1(head), then it will just print head as in main "head" has always being pointed to the "9" itself, which now became "0", so that's why i have to do head = add_1(head), so that head would point to correct node
    print(head);
    return 0;
}