#include<iostream>
#include<set>

using namespace std;

int main(){
    set <int> s = {3,4,6,7};
    s.insert(3);
    s.insert(-2);
    s.insert(22);

    set <int> :: iterator it =s.begin();
    for(it;it!=s.end();it++){
        cout<<*it<<" ";
    }

   // cout<<"Removing from 4 to 7 :-";
    int a,b;
    cout<<endl<<"Enter the range in which elements to be removed :-"<<endl;
    cin>>a>>b;

    auto e1 = s.find(a);
    auto e2=s.find(b);

//  if(e2 != s.rbegin()){       I can't do this as "e2" is a "NORMAL ITERATOR" designed for iterating in the container from   "START  TO  END", whereas       s.rbegin() is a "REVERSE ITERATOR" made for iterating in the container from    "END TO FIRST"
//      s.erase(2);
//  }

// Method 1 :-      USING s.rbegin() :-

    auto e3 = s.rbegin();       // Here by using auto i am just making "e3" an iterator which is pointing to rbegin of s.

    if(e2 != s.end()){
        s.erase(e1,++e2);

        // for(it;it!=s.end();it++){        ----> This is shwoing error as i had already defined "it" previously with respect to set where, no erase was done.
        // cout<<*it<<" ";
        // }

        // for(auto it : s){        // This even works.
        // cout<<it<<" ";
        // }

        set <int> :: iterator it = s.begin();
        for(it;it!=s.end();it++){
            cout<<*it<<" ";
        }
    }
    return 0;
}

/*
 Although this is working for inputs like a=4 and b=7, but still i will have to check :-

(1) Whether user has given range in proper order or not like a=7 and b=4 is a WRONG ORDER.

(2) Whether "a" or "b" entered is last element or not.
*/