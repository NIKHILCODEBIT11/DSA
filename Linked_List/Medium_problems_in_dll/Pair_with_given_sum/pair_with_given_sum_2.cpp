#include<bits/stdc++.h>
using namespace std;

// Sorted dll

class node{
    public:
    int data;
    node *next;
    node* back;

    node(int data){
        this->data = data;
        this->next = nullptr;
        this->back = nullptr;
    }
    node(int data,node* next,node* back){
        this->data = data;
        this->next = next;
        this->back = back;
    }
};

node *convert_arr_to_dll(vector <int>&nums){
    node *head = new node(nums[0]);
    node *prev = head;
    for(int i=1;i<nums.size();i++){
        node *temp = new node(nums[i],nullptr,prev);
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

node* find_tail(node* head){
    node* temp = head;
    while(temp!=NULL){
        if(temp->next == NULL){
            return temp;
        }
        temp = temp->next;
    }
}

vector<pair<int,int>> pair_with_given_sum(node* head,int sum){      //  1   2   3   4   9
    node* left = head;
    vector<pair<int,int>> res;
    node *right = find_tail(head);
    while(left->data < right->data){
        if(left->data + right->data == sum){
            res.push_back({left->data,right->data});
            left = left->next;
            right = right->back;
        }
        else if(left->data + right->data < sum){
            left = left->next;
        }
        else{
            right = right->back;
        }
    }
    return res;
}

int main(){
    vector <int> nums = {1,2,3,4,9};
    node *head = convert_arr_to_dll(nums);
    print(head);
    vector<pair<int,int>> ans = pair_with_given_sum(head,5);
    for(int i=0;i<ans.size();i++){
        cout<<"{"<<ans[i].first<<" "<<ans[i].second<<"}"<<endl;
    }
    return 0;
}