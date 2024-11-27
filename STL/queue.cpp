#include<iostream>
#include<queue>

using namespace std;

//      "QUEUE" follows     FIFO {  First In First Out  }

void print_queue_reverse(queue <int> &);

void explain_queue(){
//  queue <int> q1={2,3,4}; ----->   This will show error as unlike "vector","list","pair" and like "stack", i can't initialize a QUEUE directly with values, i will have to use "push()".
    queue <int> q2;

    q2.push(2);
    q2.push(3);
    q2.push(4);
    q2.emplace(6);

/*
    cout<<"Trying to print elements of queue :-"<<endl;
    for(auto it : q2){
        cout<<it<<" ";
    }
    cout<<endl;

------> Just like in "stack", even in queue i can't directly use an iterator to iterate through all the elements of "queue", rather
just like stack, i will have to "print" the "FRONT" element { As, follows FIFO },then pop it and access the next element which will
become the first element after pop(). 
*/

    cout<<"Printing the back element of queue :-"<<endl;
    cout<<q2.back();

    // Operation with q2.back() shown in video :-

    cout<<endl<<"Printing the front element of the queue :-"<<endl;
    cout<<q2.front();

    cout<<endl<<"Popping the first element as in queue FIFO is being followed :-"<<endl;
    q2.pop();
    cout<<q2.front()<<" and "<<q2.back();   // This verifies that in queue by using pop(), the front element gets popped.

    cout<<endl<<"Printing the queue after popping in reverse order :-"<<endl;
    print_queue_reverse(q2);

}

void print_queue_reverse(queue <int> &q){
    while(!q.empty()){
        auto it = q.front();
        q.pop();
        print_queue_reverse(q);
        cout<<it<<" ";
    }
/*
    cout<<"Adding 4 to the last element of the queue :-";
    cout<<(q.back()+4);

------> Here, i am getting very different output because as i know that in void there is no return statement, but still recurssion occurs 
when the end of function is reached, after which it will automatically return back to the previus call.
*/
}

int main(){
    explain_queue();
    return 0;
}

// The time complexity is   O(1).