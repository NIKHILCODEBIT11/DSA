#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    node(int data,node* next){
        this->data=data;
        this->next=next;
    }
};

node* convert_arr_to_ll(vector <int> &nums){
    node *head = new node(nums[0]);
    node * prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *remove(node *head, int n){
    node *temp = head;
    int size = 0;
    while(temp!=NULL){          // For getting size of linkedlist
        size++;
        temp=temp->next;
    }

    if(n == size){
        node* new_head=head->next;
        free(head);         // Use delete(head)
        return new_head;
    }

    int count = size - n;
    temp = head;
    while(temp!=NULL){           // 2   3   4   7   9   6
        count--;
        if(count == 0){
            node * delete_node = temp->next;
            temp->next = temp->next->next;
            free(delete_node);
            break;
        }
        temp=temp->next;
    }
    return head;
}

void print(node *head){
    node *temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int main(){
    vector <int> nums={2,3,4,5,6,7};
    node *head=convert_arr_to_ll(nums);
    print(head);
    node *ans=remove(head,4);
    print(ans);
    return 0;
}