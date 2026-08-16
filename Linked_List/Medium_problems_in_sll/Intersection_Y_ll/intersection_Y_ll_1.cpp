#include<bits/stdc++.h>
using namespace std;

/*

APPROACH :-

Storing the node from ll1 with head_1 as head in a map
and then initializing temp to head_2 of ll2 and moving ahead and if any node from ll2 matches to 
the node of ll1, then return it

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

node *intersection(node *head_1,node *head_2){
    node *temp = head_1;
    map<node *,int>mp;
    while(temp!=NULL){
        mp[temp] = 1;
        temp = temp->next;
    }
    temp = head_2;
    while(temp!=NULL){
        if(mp.find(temp) != mp.end()){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

int main(){

    vector<int> nums1 = {1, 2, 3};
    vector<int> nums2 = {4, 5};

    node *head_1 = convert_arr_to_ll(nums1);
    node *head_2 = convert_arr_to_ll(nums2);

    // Create common intersection part
    vector<int> commonPart = {7, 8, 9};
    node *common = convert_arr_to_ll(commonPart);

    // Attach common part to list 1
    node *temp = head_1;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = common;

    // Attach same common part to list 2
    temp = head_2;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = common;

    cout << "List 1: ";
    print(head_1);

    cout << "List 2: ";
    print(head_2);

    node *ans = intersection(head_1, head_2);

    if(ans != NULL){
        cout << "Intersection at node with value: " << ans->data << endl;
    }
    else{
        cout << "No intersection found" << endl;
    }

    return 0;
}