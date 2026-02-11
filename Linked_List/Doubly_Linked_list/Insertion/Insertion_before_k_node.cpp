#include<bits/stdc++.h>
using namespace std;


// See below comment for understanding

class node{
    public :
    int data;
    node *back;
    node *next;

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

void print(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

node *convert_arr_to_dll(vector <int> &nums){
    node *head = new node(nums[0]);
    node *prev=head;
    for(int i=1;i<nums.size();i++){
        node *temp=new node(nums[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

node *Insert_before_head(node *head,int val){       // Look comment to know why also used Insert_before_head
    node *new_node=new node(val,head,nullptr);
    head->back=new_node;
    head=new_node;
    return head;
}

node *Insert_before_tail(node *head,int val){
    if(head->next==nullptr){
        return Insert_before_head(head,val);
    }
    node* tail=head;
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    node *new_node = new node(val,tail,tail->back);
    tail->back->next=new_node;
    tail->back=new_node;
    return head;
}

node *Insertion_before_knode(node *head,int k,int val){
    node*temp = head;
    int count=0;
    while(temp->next!=nullptr){
        count++;
        if(count==k){
            break;
        }
        temp=temp->next;
    }
    node *knode = new node(val,temp,temp->back);
    temp->back->next=knode;
    temp->back = knode;
    return head;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_dll(nums);
    print(head);
    Insertion_before_knode(head,3,4);
    // cout<<"The deleted node is "<<ans->data<<endl;
    print(head);
    return 0;
}