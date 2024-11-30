#include<iostream>
#include<set>
#include<functional>

using namespace std;

void input(){
    set <int, greater <int>> s ={5,3,4,88,12,32};

    for(auto it : s){
        cout<<it<<" ";
    }
    cout<<endl;

    auto i = s.key_comp();

    if(i(88,4)){
        cout<<"88 is greater than 4"<<endl;
    }

    if(i(3,4)){
        cout<<"3 is greater than 4"<<endl;
    }

    set <int,equal_to <int>> s1 = {3,4,2,3,22,66,44};       // equal_to is not useful for set as no duplicate items are present.        In case of set, even value_comp() works same, as in set elements themselves are "key" as well as "values".

    for(auto it : s1){
        cout<<it<<" ";
    }
    cout<<endl;

    auto i2=s1.key_comp();

    if(i2(12,5)){
        cout<<"12 is equal to 5"<<endl;
    }
    if(i2(5,5)){
        cout<<"5 is equal to 5"<<endl;
    }

    set <int,not_equal_to<int>> s2 = {33,44,22,33,442};

    for(auto it : s2){
        cout<<it<<" ";
    }

    auto i3 = s2.value_comp();

    if(i3(44,22)){
        cout<<endl<<"44 is not equal to 22"<<endl;
    }
    else{
        cout<<"44 is equal to 22";
    }
}

int main(){
    input();
    return 0;
}

// key_comp() and value_comp() don't bother even if the elements given are not the elements of set, there only work is to compare those and execute the program, even if elements passed are the members of set or not, it doesn't matter.