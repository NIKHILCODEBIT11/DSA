#include<bits/stdc++.h>
using namespace std;

/*

APPROACH :-

Instead of calculating lengths, we:
Start two pointers from both heads.
Move them one step at a time.
When one reaches NULL → redirect it to the other list’s head.

Eventually they will either:
Meet at intersection node
Or both become NULL (no intersection)

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
    node *temp_1 = head_1;
    node *temp_2 = head_2;

    if(head_1 == NULL || head_2 == NULL){
        return NULL;
    }
    while(temp_1 != temp_2){
        temp_1 = temp_1->next;
        temp_2 = temp_2->next;

        if(temp_1 == temp_2){
            return temp_1;
        }

        if(temp_1 == nullptr){
            temp_1 = head_2;
        }
        if(temp_2 == nullptr){
            temp_2 = head_1;
        }
    }
    return temp_1;
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