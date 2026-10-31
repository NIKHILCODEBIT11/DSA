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
        this->data = data;  // hum yaha this.data = data NAHI LIKH SAKTE
        this->next = next;  // this ek pointer hota hai: C++ me this keyword current object ka pointer (Node*) hota hai, actual object reference nahi.
    }

    node(int data){
        this->data=data;
        this->next=nullptr;
    }

    /*
    DIFF between "." and "->" :-
    Jab aap kisi pointer ke zariye member variables ko access karte hain, toh arrow operator (->) use hota hai.
    Dot operator (.) sirf tab use hota hai jab aapke paas direct object ya reference ho.
    Agar aapko dot (.) use karna hi hai, toh pehle pointer ko dereference karna padega:
    (*this).data = data;
    (*this).next = next;

    ALTERNATIVE :-
    
    1. Parameter ka naam alag rakh kar (jo screenshot me tha):
    Node(int data1, Node* next1) {
    data = data1;
    next = next1;
    }

    2. Member Initializer List use karke (Best C++ Practice):
    Yaha parameter ka naam same data rakhne ke baad bhi confusion nahi hota aur performance bhi better hoti hai:
    Node(int data, Node* next) : data(data), next(next) {}

    Node(int data) : data(data), next(nullptr) {}


    */
};

// Sirf ek best practice yaad rakhna: jab kaam poora ho jaye ya program end ho, toh heap memory leak avoid karne ke liye delete y; lagana acchi aadat hoti hai. Baaki aapke notes revision ke liye perfect hain.

int main(){
    vector <int> nums={2,3,6,7,9};

    // 1. Is tarike se node y banta hai STACK mein jo ki jaise hi uska function (yaha main) khatam hoga tab wo khatam ho jayega JIS WAJAH SE HUM JO BHI INSERT DELETE KIYE HONGE US FUNCTION MEIN HONE KE BAAD BAHAR WAPAS USI NORMAL FORM MEIN AA JAYEGA
    // node y = node(nums[0]);             //   y exists only inside main()   and     Destroyed automatically when main() ends
    // cout<<y.data;

    // 2. YE UPAR WALE TARIKE JAISA HI HAI
    // node y(nums[0], nullptr);

    // 3. new keyword address return karta hai:
    // C++ me jab aap new Node(...) likhte hain, toh memory Heap me allocate hoti hai, aur new us allocated node ka memory address (pointer) return karta hai.
    // Isiliye us address ko catch karne ke liye left side me pointer variable hi chahiye, jo ki Node* y hai.   
    node *y = new node(nums[0]);         // 'new' ne address diya, 'Node* y' ne use store kiya
    cout<<y->data;


    // Agar sirf Node y likhte toh kya hota?
    // Node y ka matlab hota ek actual object jo Stack memory me banta hai.
    // Node y = new Node(arr[0], nullptr); // ❌ Error!
    // Toh compiler error dega kyunki right side se memory address (Node*) mil raha hai, jabki left side me data type simple Node hai. Type mismatch ho jayega.

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