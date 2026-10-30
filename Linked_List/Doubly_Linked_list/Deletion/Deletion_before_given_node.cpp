#include<bits/stdc++.h>
using namespace std;

// Won't be deleting     "head"         node   yani temp kabhi head nahi hoga, iska temp->back hamesha exist karega
// to is question mein sirf 2 cases bante hain ya to delete karne wala node "tail" ho ya phir beech mein kahi ho

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

void delete_node(node *temp){
    node *prev = temp->back;
    node *front = temp->next;

    if(front == nullptr){     // case 1 :- agar delete karne wala node "tail" ho
        prev->next=nullptr;
        temp->back = nullptr;
        delete temp;
        return;
    }

    prev->next = front;
    front->back = prev;
    temp->back = temp->next =nullptr;
    delete(temp);
    return;
}

void print(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_dll(nums);
    print(head);
    delete_node(head->next);
    // cout<<"The deleted node is "<<ans->data<<endl;
    print(head);
    return 0;
}