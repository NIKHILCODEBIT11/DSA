#include<bits/stdc++.h>
using namespace std;

class node{

    public:
    int data;
    node *next;
    node(int data,node * next){
        this->data=data;
        this->next=next;
    }

    node(int data){
        this->data=data;
        this->next=nullptr;
    }
};

node* convert_arr_to_1D(vector <int>&nums){
    node* head=new node(nums[0]);
    node* mover = head;

    for(int i=1;i<nums.size();i++){
        node *temp= new node(nums[i]);
        mover->next=temp;
        mover = temp;
    }
    return head;
}

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head=convert_arr_to_1D(nums);
    cout<<"The data of head is "<<head->data;
    return 0;
}


/*
How does inside main there is a pointer named    "head"   and also inside covert_arr_to_ll there is node with same name     "head"    :-

No, this will not cause any problem! C++ handles this perfectly because of a concept called Scope.
Even though both variables are named head, they live in entirely different "worlds" (scopes) 
inside your program. They do not know each other exists.

Here is exactly why it is completely safe :-

1. Local Scope (What happens in the function, stays there) :-
Any variable declared inside a function is local to that function. It is completely isolated.

node* convert_arr_to_1D(vector <int>&nums){
    node* head = new node(nums[0]); // 🏠 This 'head' belongs ONLY to this function
    ...
    return head; // It passes the ADDRESS out, and then this local 'head' variable dies.
}
The head inside convert_arr_to_1D is created when the function starts, and it is completely 
destroyed the moment the function reaches its final return statement.


2. A Different Scope in main() :-
Now look at your main() function :-

int main(){
    vector <int> nums={2,3,3,4,7,9};
    node *head = convert_arr_to_1D(nums); // 🏢 This 'head' belongs ONLY to main()
    ...
}

The head inside main() is a brand-new variable. It only exists inside the boundaries of main().

When convert_arr_to_1D(nums) finishes running, it sends back a memory address (e.g., 0x100). 
The head inside main() simply catches that address and stores it.

Summary
In C++, as long as two variables with the same name are declared inside different sets of 
curly braces { }, they are completely independent. It is a very common and clean practice to name 
both of these head because they both serve the same purpose: pointing to the start of your 
linked list!
*/