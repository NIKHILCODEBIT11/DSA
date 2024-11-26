#include<iostream>
#include<stack>

using namespace std;

void print(stack <int>);

void explain_stack(){
   //  stack <int> st={3,4} ----->    Unlike "vector", "list", "deque", i can't directly initialize a stack with values, i have to use  push() for it,   or   do it by making a constructor and passing values of "vector" or "list" or "deque".
   stack <int> st;

//      Pushing elements to the stack in order      1 ---> 2 ---> 3 ---> 4 ---> 5

    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.emplace(5);

    // for(auto it : st){   --->  This will show error as       in stack, i can access only and only the top element, not the element
    //     cout<<it;            other than the top element because unlike in "vector" or "list", i can't access all elements using
    // }                        iterator.


/*
there is a common misunderstanding regarding how the for loop works with stacks.

In C++, the stack container adapter doesn't provide direct access to its elements for iteration like vectors or lists. The for loop in your code, which uses a range-based for loop (for(auto it : st)), won't work as intended because stacks do not expose iterators in the same way other containers do. Stacks are designed to only allow access to the top element and do not support direct iteration.

To correctly iterate through a stack, you need to pop elements one by one until the stack is empty
*/
    cout<<st.top()<<endl;     // Prints the top element i.e, 5.   st[2] is invalid.

    st.pop();       // Pops or removes the top element.

    cout<<st.top();

    cout<<endl<<"After popping the size of stack is : "<<st.size()<<endl;

    cout<<"Is the stack empty :- "<<st.empty()<<endl;

    cout<<"Printing all elements of stack from top to bottom :-"<<endl;
    while(!st.empty()){
        cout<<st.top();
        st.pop();
        cout<<endl;
    }
    // print_(st);
    // print(st);        Getting error as "more than one instance of overloaded function "print" matches the argument list"
}

// In above void print()  function, i am not getting elements in required order because just above void print_(), i had popped all elements of stack to print it's element in top to bottom order.

void print(stack <int> &s){
    if(s.empty()){
        return;
    }
    auto top = s.top();
    s.pop();
//  print(s);      Getting error as "more than one instance of overloaded function "print" matches the argument list"
    cout<<top<<" ";  
}
int main(){
explain_stack();
return 0;
}

// To resolve error of "print(s)",i have to match the "FUNCTION DECLARATION/PROTOTYPE" and "FUNCTION DEFINITION", a in function definition i have given the PARAMTER as a "REFERENCE STACK", but in function declaration, i have given paramter as "A STACK NOT IT'S REFERENCE"