#include<bits/stdc++.h>
using namespace std;

/*

APPROACH :-

I will keep three counter vars count_),count_1,count_2 initialized to 0 each.
Then i will traverse through the ll and will update the counter variable for occurence of each od 0 1 or 2
Then i will ahain traverse from haed and will update the "data" in nodes without chaning the links

*/

class node{
    public:
    int data;
    node *next;

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    node(int data, node *next){
        this->data = data;
        this-> next = next;
    }
};

node *convert_arr_to_ll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i]);
        prev->next = temp;
        prev=temp;
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

node *sort_ll(node *head){
    int count_0=0,count_1=0,count_2=0;
    node * temp = head;
    while(temp!=NULL){
        if(temp->data == 0){
            count_0++;
        }
        else if(temp->data == 1){
            count_1++;
        }
        else{
            count_2++;
        }
        temp = temp->next;
    }
    temp=head;
    while(temp!=NULL){
        if(count_0!=0){
            temp->data = 0;
            count_0--;
        }
        else if(count_1!=0){
            temp->data = 1;
            count_1--;
        }
        else{
            temp->data = 2;
            count_2--;
        }
        temp = temp->next;
    }
    return head;
}

int main(){
    vector <int> nums = {1,2,0,0,2,2,1,2,1,1,0,1,0,2,1};
    node *head = convert_arr_to_ll(nums);
    print(head);
    head = sort_ll(head);
    print(head);
    return 0;
}