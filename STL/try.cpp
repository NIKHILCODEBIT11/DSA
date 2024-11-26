#include<iostream>
#include<stack>

using namespace std;

void print_(stack <int> &); // Forward declaration of print_ function

void explain_stack() {
    // Create a stack of integers
    stack <int> st;

    // Pushing elements to the stack in order: 1 -> 2 -> 3 -> 4 -> 5
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.emplace(5);

    // Print the top element (which is 5)
    cout << st.top() << endl;

    // Pop the top element (removes 5), now the top is 4
    st.pop();
    cout << st.top() << endl;  // Should print 4

    // Print size of the stack after popping
    cout << endl << "After popping the size of stack is: " << st.size() << endl;

    // Check if the stack is empty
    cout << "Is the stack empty: " << st.empty() << endl;

    // Print all elements of the stack from top to bottom using a loop
    cout << "Printing all elements of stack from top to bottom:" << endl;
    while (!st.empty()) {
        cout << st.top() << endl;  // Print the top element
        st.pop();  // Pop the element from the stack
    }

    // Call the print_ function to print the elements from bottom to top
    print_(st);
}

// Recursive function to print stack elements from bottom to top
void print_(stack <int> &st) {
    cout << "Printing all elements of stack from bottom to top:" << endl;
    if (st.empty()) {
        return;  // Base case: when the stack is empty, return
    }
    // Temporarily store the top element and pop it
    auto top = st.top();
    st.pop();

    // Recursively call print_ on the remaining stack
    print_(st);

    // After recursion, print the stored top element
    cout << top << " ";
}

int main() {
    explain_stack();  // Call the explain_stack function to demonstrate stack operations
    return 0;
}
