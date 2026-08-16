#include<bits/stdc++.h>
using namespace std;

/*

APPROACH :-

Calculating length of each ll, and then based on whether n1<n2 or n1>n2 or n1=n2
perform collision

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

node *collision(node* head_1,node* head_2,int diff){        //  head_1 is smaller
    node *temp_2 = head_2;
    while(diff!=0){
        diff--;
        temp_2 = temp_2->next;
    }
    node *temp_1 = head_1;
    while(temp_1 != temp_2){
        temp_1 = temp_1->next;
        temp_2 = temp_2->next;
    }
    // if(temp_1 == nullptr && temp_2 == nullptr){
    //     return NULL;
    // }                This is not required as if both ll don't have any inters point then also temp_1 and temp_2 points to null after above while traversal, so not exactly required is this if condition
    return temp_1;
}

node *intersection(node *head_1,node *head_2){
    node* temp = head_1;
    int n1=0, n2=0;          // n1 -> size of ll having head_1 and n2-> size of ll having head_2
    while(temp!=NULL){
        n1++;
        temp = temp->next;
    }
    temp = head_2;
    while(temp!=NULL){
        n2++;
        temp = temp->next;
    }
    if(n1<n2){
        return collision(head_1,head_2,n2-n1);
    }
    else{
        return collision(head_2,head_1,n1-n2);
    }
   
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