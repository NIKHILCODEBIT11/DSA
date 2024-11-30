#include<iostream>
#include<map>

using namespace std;

void output(map <int,int> &a){
    for(auto it : a){
        cout<<"("<<it.first<<" "<<it.second<<")"<<" ";
    }
    cout<<endl;
}

void output(map <int,pair<int,int>> &b){
    map <int,pair<int,int>> :: iterator it = b.begin();
    for(it;it!=b.end();it++){
        // cout<<"("<<*it.first<<" "<<*it.second<<")"<<" "; ------>  This will show error as more than one value present in value, so use arrow operator.
        cout<<"("<<it->first<<" "<<it->second.first<<" "<<it->second.second<<")"<<" ";
    }
    cout<<endl;
}

void output(map <pair<int,int>,int> &c){
    for(auto it = c.begin();it!=c.end();it++){
        cout<<"("<<it->first.first<<" "<<it->first.second<<" "<<it->second<<")"<<" ";
    }
    cout<<endl;
}

void input(){
    map <int,int> m1={{1,2},{3,4},{2,2}};

    map <int,pair<int,int>> m2 = {{3,{2,2}},{2,{3,2}}};

    map <pair<int,int>,int> m3 = {{{1,2},3},{{3,4},5}};

    m1[4]=4;
    m1.insert({5,5});
    m1.emplace(6,5);
    m1.emplace(pair <int,int>(7,7));        // Sometimes, emplace can't know that pair is given inside {7,7}, so to explicitly call it as pair is much easy.
    cout<<"Printing map of <int,int> :-"<<endl;
    output(m1);
    cout<<"The value stored at key 6 is :- "<<m1[6]<<endl;
    auto it = m1.find(6);
    cout<<"Using find() to get the iterator pointing to the key {6} :- ("<<(*it).first<<" "<<(*it).second<<")"<<endl;
    cout<<"Using lower_bound() :-"<<endl;
    auto i1 = m1.lower_bound(3);
    cout<<"("<<(*i1).first<<","<<(*i1).second<<")"<<endl;

    m2[1]={1,2};
    m2.insert({4,{4,4}});
//  m2.emplace(5,5,5);        //  If i uncomment this then i am getting a tons of error not showing in code editot but showing after i compile,       as it is wrong syntax
//  m2.insert(5,(5,5));         // Even this is showing error
    m2.emplace(6,pair<int,int>(6,6));
    cout<<"Printing map of <int,pair<int,int>> :-"<<endl;
    output(m2);
//  cout<<"The value stored at key 6 is :- "<<m2[6]<<endl;   ----->   This will show error as although there is only a single key of type <int>, but still it has 2 values, and if i do m2[6], then compiler will get confuse of which value to print
    cout<<"The value stored at key 6 is :- ("<<m2[6].first<<","<<m2[6].second<<")"<<endl;
    auto it_ = m2.find(4);
    cout<<"Using find() to get the iterator poiting to the key {4} :- ("<<(*it_).first<<" "<<(*it_).second.first<<","<<(*it_).second.second<<")"<<endl;
    cout<<"Using upper_bound() :-"<<endl;
    auto i2 = m2.upper_bound(4);
    cout<<"("<<(*i2).first<<","<<(*i2).second.first<<","<<(*i2).second.second<<")"<<endl;
/*
    m3[1,2]=2; -----> This will show error as, if i write m3[1,2], then it won't create pair<int,int> with 1 and 2 as key.
    Instead   1,2     will be treated as "COMMA OPERATOR".
    This comma operator will first of all evaluate the expression "1" and will discard it, and then evaluates and returns the second
    expression "2".   Thus, m3[1,2] is equivalent to m3[2]
*/

    m3[{1,2}]=2;        // Since "key" must be unique, but {1,2} is already present in above declaration of m3
    m3.insert({{2,2},2});
    m3.emplace(pair <int,int>(3,3),4);
    cout<<"Printing map of <pair<int,int>,int> :-"<<endl;
    output(m3);
    cout<<"The value stored at key {3,4} is :- ("<<m3[{3,4}]<<")"<<endl;
    cout<<"Printing the value for such key which doesn't exists :- ("<<m3[{2,3}]<<")"<<endl;        // Since such "key" doesn't exists, so it will return "0"
    output(m3);
    auto it__=m3.find({2,2});
    cout<<"Using find() to get iterator poiting to key {2,2} :- ("<<(*it__).first.first<<","<<(*it__).first.second<<","<<(*it__).second<<")"<<endl; 
    cout<<"Using upper_bound() :-"<<endl;
    auto i3 = m3.upper_bound({2,2});
    cout<<"("<<(*i3).first.first<<","<<(*i3).first.second<<","<<(*i3).second<<")"<<endl;        // Here, instead of (3 3 4) i am getting (2,3,0) because look reason below this code 
}

int main(){
    input();
    return 0;
}

/*
"MAP" is like "DICTIONARY" of python, as it stores "key-value" pair. The important point is "KEY" must be "UNIQUE", "VALUE" may be "REPETITIVE", 
And according to the value of "KEY", the "MAP" is sorted.
That means "MAP" stores "KEY-VALUE" pair with "UNIQUE" and "SORTED KEY".
Both "key" and "value" can be of any "DATA TYPE", maybe both same or both different.




Reason :-

Since in "m3" only at a line i did      cout<<"Printing the value for such key which doesn't exists :- ("<<m3[{2,3}]<<")"<<endl; 
and since previously, such "KEY" was not present, so it returns "0". But, the interseting thing is that once, it return "0" signifying
that no such "KEY" exists, after that, "KEY {2,3} GETS ADDED WITH VALUE 0", because it returns "0", which will act as it's value
which i can see in the 2nd output(m3) function i wrote
*/