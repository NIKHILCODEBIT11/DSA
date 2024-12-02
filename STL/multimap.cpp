// Same as "map", the only differenec is that here duplicate keys { MULTIPLE KEYS } can be stored, but everything remains in "SORTED" manner.

#include<iostream>
#include<map>

using namespace std;


int main(){
   cout<<"Multimap of type <pair<int,int>,int> :-"<<endl;
   multimap <pair<int,int>,int> m = {{{1,1},2}};
   m.insert({{2,3},4});
// m.emplace({{4,5},6});    --------------->   Error
   m.emplace(pair <int,int>(3,4),5);
   auto it=m.equal_range({1,1});
   cout<<"Printing using equal_range() :-"<<endl;
   cout<<"First iterator :-"<<endl;
   cout<<"("<<it.first->first.first<<","<<it.first->first.second<<","<<it.first->second<<")"<<endl;
   cout<<"Second iterator :-"<<endl;
   cout<<"("<<it.second->first.first<<","<<it.second->first.second<<","<<it.second->second<<")";

   cout<<"Multimap of type <int,int> :-"<<endl;
   multimap <int,string> m1 = {{1,"uno"},{1,"one"}};
   m1.emplace(3,"Three");
   m1.insert({2,"two"});
   // it = m1.equal_range(1);      ------>     Showing error as previously, "it" was pointing to a pair of iterator of type <pair<int,int>,int>    and here, "it" is pointing to a pair of iterator of type <int,int>
   auto it_ = m1.equal_range(1);
   cout<<"First iterator :-"<<endl;
   cout<<"("<<it_.first->first<<","<<it_.first->second<<")"<<endl;
   cout<<"Second iterator :-"<<endl;
   cout<<"("<<it_.second->first<<","<<it_.second->second<<")"<<endl;
   cout << "Complete multimap:" << endl;

   cout<<"Printing the whole multimap of <int,int> :-"<<endl;
   for(auto i : m1){
      // cout<<i->first<<","<<i->second<<endl;     ----->      I can't do this as in "for-each" loop i had to use "dot operator" only.
      cout<<i.first<<","<<i.second<<endl;
   }
   return 0;
}


/*
equal_range() is working correctly for m1.

The first iterator must point to the key "GREATER THAN OR EQUAL TO" the key that is specified. -----> As, multimap stores element 
in "UNSORTED" and "NON-UNIQUE" way, so as firstly i gave {1,"uno"} then {1,"one"}, so first iterator will point to {1,"uno"}, which
is equal to the key specified in equal_range()

The second iterator points to the key "STRICTLY GREATER THAN" the key that is specifies, so it can't be {1,"uno"} or {1,"one"} as key
is strictly 1 here, so it points to {2,"two"} whose key is "greater than" 1.


USE "DOT OPERATOR" FOR OBJECT AND REFERENCES

USE "ARROW OPERATOR" FOR POINTERS OR ITERATORS

When accessing the elements in multimap, iterators are pointers to the elements, which are of type pair<int, string>.
To access the members of a pair (which are first and second), you need to dereference the iterator using the arrow operator (->).




Why it_->first.first won't work:
it_ is an iterator (a pointer to a pair), so it_->first would attempt to access the first member of the iterator itself, not the pair it points to.
Since it_ points to a pair<int, string>, the correct way to access the key and value inside the pair is by dereferencing the iterator with -> and then accessing first and second.
Therefore, you must use it_->first to access the first member of the pair, and it_->second to access the second member.
*/