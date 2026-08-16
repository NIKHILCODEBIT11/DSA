#include<bits/stdc++.h>
using namespace std;

// In this approach, i will put all data of ll in a vector and then sort that vector then will traverse through both ll and vector and will put value from vector to ll

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


node *convert_arr_to_ll(vector <int> &nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i]);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

void print(node *head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

node * middle(node *head){
    node *slow = head;
    node * fast = head->next;

    while(fast!=NULL && fast->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

node *merge2lists(node *list_1, node* list_2){
    node *dummy = new node(0);
    node *temp = dummy;

    while(list_1!=NULL && list_2!=NULL){
        if(list_1->data < list_2->data){
            temp->next = list_1;
            list_1=list_1->next;
        }
        else{
            temp->next = list_2;
            list_2 = list_2->next;
        }
        temp = temp->next;
    }

    if(list_1){         // If some element is left in list_1, then if (list_1) is same as list_1(true)
        temp->next = list_1;
    }
    else{           // If some element is left in list_1, then if (list_1) is same as list_1(true)
        temp->next = list_2;
    }
    return dummy->next;
}

node *sort_ll(node *head){
    if(head == NULL || head->next == nullptr){
        return head;
    }

    // step 1 :-   finding middle
    node * mid = middle(head);

    // Step 2 :-   splitting list into 2 halves
    node *left = head;
    node *right = mid->next;
    mid->next = NULL;

    // Step 3 :-   Recursively sorting both halves
    left = sort_ll(left);
    right = sort_ll(right);
    return merge2lists(left,right);
}


int main(){
    vector <int> nums = {4,3,7,9,2,6};
    node * head = convert_arr_to_ll(nums);
    print(head);
    head = sort_ll(head);
    print(head);
    return 0;
}