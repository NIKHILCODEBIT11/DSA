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

vector<pair<int,int>> pair_given_sum(node* head,int sum){
    node* temp_1 = head;
    node* temp_2;
    vector<pair<int,int>> res;
    while(temp_1!=NULL && temp_2->data <= sum - temp_1->data){
        temp_2 = temp_1->next;
        while(temp_2!=NULL){
            if(temp_1->data + temp_2->data == sum){
                res.push_back({temp_1->data,temp_2->data});
                temp_2 = temp_2->next;
            }
            else{
                temp_2 = temp_2->next;
            }
        }
        temp_1 = temp_1->next;
    }
    return res;
}

int main(){
    vector <int> nums = {1,2,3,4,9};
    node *head = convert_arr_to_dll(nums);
    print(head);
    vector<pair<int,int>> ans = pair_given_sum(head,5);
    for(int i=0;i<ans.size();i++){
        cout<<"{"<<ans[i].first<<" "<<ans[i].second<<"}"<<endl;
    }
    return 0;
}