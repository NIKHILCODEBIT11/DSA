#include<bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node* next;

    node(int data){
        this->data = data;
        this->next = nullptr;
    }
};


// Convert vector to linked list
node* convert_arr_to_ll(vector<int> &nums){

    node* head = new node(nums[0]);
    node* prev = head;

    for(int i = 1; i < nums.size(); i++){
        node* temp = new node(nums[i]);
        prev->next = temp;
        prev = temp;
    }

    return head;
}



// ---------------------------------------------------------
// Remove Nth node from end using Dummy Node (One Pass)
// ---------------------------------------------------------
node* removeNthFromEnd(node* head, int n){

    /*
        Step 1: Create dummy node
        This removes the special case of deleting the first node.
    */
    node dummy(0);
    dummy.next = head;

    node* slow = &dummy;
    node* fast = &dummy;

    /*
        Step 2: Move fast pointer n+1 steps ahead.

        Why n+1 ?
        Because we want slow to stop at the node
        BEFORE the node to be deleted.
    */
    for(int i = 0; i <= n; i++){
        fast = fast->next;
    }

    /*
        Step 3: Move both pointers together.

        IMPORTANT:
        We use:
            while(fast != nullptr)

        NOT:
            while(fast->next != nullptr)

        WHY?

        Because fast might become nullptr
        (especially when deleting the first node).

        If we use fast->next,
        and fast is already nullptr,
        it will cause segmentation fault.

        Using (fast != nullptr) is SAFE,
        because we are not accessing fast->next
        unless fast exists.
    */
    while(fast != nullptr){
        slow = slow->next;
        fast = fast->next;
    }

    /*
        Now slow is pointing to the node
        BEFORE the one we need to delete.
    */
    node* nodeToDelete = slow->next;
    slow->next = slow->next->next;

    delete nodeToDelete;

    // Return the real head (dummy was temporary)
    return dummy.next;
}



// Print function
void print(node* head){

    node* temp = head;

    while(temp != nullptr){
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}



// Main
int main(){

    vector<int> nums = {2,3,4,5,6,7};

    node* head = convert_arr_to_ll(nums);

    cout << "Original List: ";
    print(head);

    head = removeNthFromEnd(head, 6);

    cout << "After Deletion: ";
    print(head);

    return 0;
}