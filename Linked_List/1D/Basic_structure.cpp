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

/*

Why i didn't used      node y = node(nums[0])       and used     node *y = new node(nums[0]) :-

1. Stack Variables Have a Short Lifetime (The "Death" Problem) :-
Variables created like node y are stored on the Stack. The Stack is managed automatically by 
functions. The moment a function finishes and hits its closing bracket }, every stack variable 
inside it is instantly destroyed.

Imagine you want to write a helper function to add a new node to your list :-
void addNode(node* head, int value) {
    node newNode = node(value); // 1. Created on the STACK
    head->next = &newNode;      // 2. Link your list to its address
} // ❌ CRASH! newNode is automatically destroyed HERE!

If you do this, the node vanishes the millisecond addNode finishes. Your head->next is now 
pointing to a dead zone in memory (called a dangling pointer). The next time you try to read 
your list, your program will crash.

How new fixes this:
When you use new node(), the object is created on the Heap. Heap memory stays alive forever until 
you explicitly choose to delete it. It doesn't care if a function ends; your data remains perfectly 
safe.

2. You Lose Dynamic Chaining (The "Variable Name" Problem) :-
If you create nodes on the stack without pointers, you have to give every single node its own 
manual variable name in your code :-

node node1 = node(2);
node node2 = node(3);
node node3 = node(6);

This completely defeats the purpose of a data structure like a linked list! We use linked lists 
so our data can grow dynamically at runtime (for example, reading 1,000 numbers from a file where 
we don't know the count beforehand). You can't hardcode 1,000 variable names.

With new, you don't need a unique variable name for every node. You just need one pointer (head) 
to hold the starting address. Every other node is created anonymously on the heap and chained 
together using addresses.
*/