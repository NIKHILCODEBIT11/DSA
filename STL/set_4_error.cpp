//      Using   rbegin()   instead of   ++e2.

#include<iostream>
#include<set>

using namespace std;

void erase(set <int> &);

void output(set <int> &a){
    for(auto it : a){
        cout<<it<<" ";
    }
    erase(a);
}

void erase(set <int> &a){
    int range[2];
    cout<<"Enter the range of elements :- "<<endl;
    cin>>range[0]>>range[1];

    auto rev_1=a.rbegin();
    auto rev_2=a.rbegin();

    // while(rev_1 != a.rend() && *rev_1!=*a.rend()){
    //     rev_1++;
    // }

    // while(rev_1 != a.rend() && *rev_2!=*a.rend()){
    //     rev_2++;
    // }

    while(rev_1 != a.rend() && *rev_1!=range[0]){
        ++rev_1;
    }

    while(rev_2 != a.rend() && *rev_2!=range[1]){
        ++rev_2;
    }

/*

For output as :-

Inputting of elements in set :-
Enter element 1 :- 3
Enter element 2 :- 4
Enter element 3 :- 5
Enter element 4 :- 6
Enter element 5 :- 7
3 4 5 6 7 Enter the range of elements :-
4
6
3 7

*/
    cout<<"Value of rev_1 is "<<*rev_1<<endl;
    cout<<"Value of *rev_2 is "<<*rev_2<<endl;
    a.erase(rev_1.base(),rev_2.base());       // This syntax follows    (4,6]         written in chrome   [7,4)

    cout<<"Value of rev_1 is "<<*rev_1<<endl;
    cout<<"Value of *rev_2 is "<<*rev_2<<endl;

//  output(a); ---->  If i do this then functions will keep on calling again and again
    
    for(auto it : a){
        cout<<it<<" ";
    }

}

void input(){
    set <int> s ={3,4,5,6,7};
    output(s);
}

int main(){
    input();
    return 0;
}