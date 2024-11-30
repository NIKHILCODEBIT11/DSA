// Method 1 :- To remove elements from a range :-

#include<iostream>
#include<set>

using namespace std;

void output(set <int> &a){
    for(auto it : a){
        cout<<it<<" ";
    }
}

void erase(set <int> &a){
    int a1[2];          //      I was getting error when i was trying a[2], because i am already using "a" as a refernce of set
    cout<<endl<<"Enter the values including which you want to remove elements from list : ";
    cin>>a1[0]>>a1[1];

    auto e1= a.find(a1[0]);
    auto e2 = a.find(a1[1]);

    if(e1 == a.end() || e2 == a.end()){
        cout<<"Enter the value that is present in set"<<endl;
      //  exit(0);      It works, but abruptly exits the program
        return;     // It will return control to the caller which is input()
    }

    else{
        a.erase(e1,++e2);       // By using     "++e2"  even "e2" will be included in erase()

//      ++e2(pre increment) is incrementing the iterator, not using an index, so it's perfectly valid and i can't do e2++ because if i use e2++, then firstly it will use "e2" and after that it will increment as it is post-increment

    }
}

void input(){
    set <int> s={3,4,6};
    s.insert(-2);
    s.emplace(9);
    output(s);
    erase(s);
    output(s);
}


int main(){
    input();
    return 0;
}