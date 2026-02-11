#include<bits/stdc++.h>
using namespace std;

// OPTIMAL approach :-        Used concept of      SWAP    using a temp variable

class node{
    public:
    int data;
    node *next;
    node* back;

    node(int data){
        this->data=data;
        this->next=nullptr;
        this->back=nullptr;
    }

    node(int data,node *next,node *back){
        this->data=data;
        this->next=next;
        this->back=back;
    }
};

node * convert_arr_to_ll(vector <int>&nums){
    node* head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *reverse_ll(node *head){
    node *current=head;
    node *last = nullptr;
    while(current!=NULL){
        last = current->back;
        current->back = current->next;
        current->next = last;
        current = current->back;       // As, i updated    current->back to current->next
    }
    // When the while loop finishes:
    //
    // - 'current' becomes NULL, which means we have processed
    //   all the nodes of the list.
    //
    // - In the last iteration, 'current' was pointing to the
    //   original last node of the list.
    //
    // - Before swapping pointers, we stored:
    //       last = current->back
    //   So 'last' now points to the second last node
    //   (in the original list).
    //
    // - After swapping next and back pointers,
    //   the original last node becomes the NEW HEAD
    //   of the reversed list.
    //
    // - But since 'last' is one step behind that node,
    //   the new head can be accessed using:
    //       last->back
    //
    // Therefore, we return last->back because
    // it correctly points to the new head
    // of the reversed doubly linked list.
    return last->back;

}

void print(node* head){
    node *temp=head;
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

    node *ans = reverse_ll(head);
    // Do NOT print using old 'head'
    // because after reversing,
    // 'head' still points to the old first node,
    // which is now the last node of the reversed list.
    //
    // The function returns the new head,
    // so we must print using 'ans'.
    print(ans);   // Correct

    cout<<"The new head is "<<ans->data<<endl;
    return 0;
}