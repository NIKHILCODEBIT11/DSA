#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;
    Node(int data1,Node *next1){
        data=data1;
        next=next1;
    }
    Node(int data1){
        data=data1;
        next=nullptr;
    }
};
int main(){
    cout<<"Using pointer :-"<<endl;
    Node *x=new Node(2);
    cout<<x->data<<endl;      // cout<<x.data;    is throwing error as i will have to use arrow operator in pointer
    cout<<x->next<<endl;

    cout<<"Using & operator :-"<<endl;
//  Node *x_=&Node(3);          //  Node x = &Node(3)     it is throwing error as address needs to be pointed by pointer only.
// One more problem is that here i am not using "new" so it is making a "TEMPORARY OBJECT" x_ but as soon as a temporary object is made it gets out of scope so it can't be used to access data and next
//  cout<<x_->data<<endl;
//  cout<<x_->next<<endl;
    cout<<"It can't be done as here i am not using new so it is making a TEMPORARY OBJECT x_ but as soon as a temporary object is made it gets out of scope so it can't be used to access data and next"<<endl;

    cout<<"Making object :-"<<endl;
    Node x_ = Node(3,x);
    Node *x1=&x_;
    cout<<x_.data<<endl;
    cout<<x_.next<<endl;

    cout<<"Making object :-"<<endl;
    Node y=Node(4,x1);
    cout<<y.data<<endl;
//  cout<<*(y.next)<<endl;      I am getting error as using syntax *(y.next) will work but will show error if y,next will be nullptr, as dereferencing nullptr will show undefined behaviour 
// And also, if i do   *(y.next), then i will get a node not data, and compiler doesn't know how t print a node, that's why it shows error no operator "<<" matches error.
    return 0;
}