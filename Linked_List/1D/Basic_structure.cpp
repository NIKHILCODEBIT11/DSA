#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;              // Key rule in C++   :-    A class cannot contain an object of its own type.

    /*
    “A node contains another full node inside it”

    But that inner node would again contain another node, and so on…

    This creates an infinite size problem
    */



    // We use `node* next` because `next` should store the ADDRESS of the next node,
    // not a full node object. Each node only keeps a pointer (link) to the next node,
    // which avoids infinite size and allows nodes to connect dynamically.
    node(int data, node* next){
        this->data = data;
        this->next = next;
    }

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

};

int main(){
    vector <int> nums={2,3,6,7,9};

    // node y = node(nums[0]);             //   y exists only inside main()   and     Destroyed automatically when main() ends
    // cout<<y.data;

    node *y = new node(nums[0]);         //  ➡ new always returns a pointer
    cout<<y->data;

    //   new allocates memory on the heap, constructs the object there, and returns its address.
    return 0;
}