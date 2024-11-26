//  Printing elements of stack in bottom to top :-
#include<iostream>
#include<stack>

using namespace std;

void print(stack <int> &);
void explain_stack(){
    stack <int> st;
    st.push(3);
    st.push(4);
    st.push(6);
    st.push(7);

    cout<<"printing elements of stack in bottom to top order :-"<<endl;
    print(st);
}

void print(stack <int> &s){
    if(s.empty()){
        return;
    }
    auto top = s.top();
    s.pop();
    print(s);
    cout<<top<<" ";
}

/*

One doubt maybe that how the above function     print(s) is acting as recurssive function ????

----> The answer is :-
Since, here the function    "print" is "void",  and a magical thing about "void" is that it doesn't require an "IMPLICIT return" 
statement, rather it automatically returns back after last line of code, and thus after     cout<<top<<" ";
it returns back to the previous calling function.

One more doubt maybe that why did i write     cout<<top<<" "; after print(s) ?????

----> The reason is that i need to print elements in BOTTOM TO TOP, so i will need to print "top" from the last accessible element
that will be the last element or bottom most available element in stack,    as stack is     LIFO.

*/

int main(){
    explain_stack();
    return 0;
}