#include<iostream>
#include<vector>
using namespace std;

// Syntax of vector :-
vector <int> v1;    // It creates an empty container

// Methods to add elements in vector
vector <int> v2={4};
//v2.push_back(6);    // Getting error as push_back must be called within a function only.

// methods to add elements in vector
void input(){
    vector <int> v3={5};
    v3.push_back(6);        // Generally  emplace_back() is faster than   push_back()
    v3.emplace_back(7);
}

// Way to define vector of pair data type :-
vector <pair <int,int>> v4;   
// v4.push_back({2,3});   // Showing error as i am calling push_back and emblace_back outside of the function.

void input_2(){
    vector <pair<int,int>> v5 = {{4,5}};    // I have to insert the values for pair inside curly braces for push_back.
    v5.push_back({3,4});    // The pair value for push_back must be bounded  inside ( ).
    v5.emplace_back(6,7);   // The pair value for emblace_back doesn't require { }, put the pair values inside ( ).
}

// vector <int> v6={5,100};    // It creates a container of vector "v6" with "5" instances of "100".   {100,100,100,100,100}

vector <int> v6{5,100};    // It creates a container of vector "v6" with "5" instances of "100".   {100,100,100,100,100}
// One doubt may arise that once i declared above line of creating vector "v6", then can i increase the size of "v6" ????
// The answer is    YES,    I can do it by using "push_back()" or "emplace_back()".

vector <int> v7{5};     // It creates a vector "v7" with "5" instances of "0".
vector <int> v8(v7);    // "v8" is nothing but a "copy" of vector "v7". 


// Accessing elements of vector :-
vector <int> v9(5,33);

// Method - 1 :-    Using array format.
void output_arr(){
    for(int i=0;i<v9.size();i++){
        cout<<v9[i]<<" or "<<v9.at(i);
        cout<<endl;
    }
}

// Method - 2 :-    using iterator
vector <int> :: iterator iter = v9.begin();     // v.begin() points to the "first" element of the vector.
void output_iter(){
    for(iter;iter!=v9.end();iter++){        // v.end() points to the next postion after "last" element of the vector.
        cout<<*iter<<" ";
    }
    cout<<endl;
}

// Method - 3 :-   Using "auto" as iterator
void output_auto_iter(){
    for(auto it=v9.begin();it !=v9.end();it++){     // Here, as using "auto", so automatically "it" is getting the memory address of first element of "v9".
        cout<<*it<<" ";
    }
    cout<<endl;
}

// Method - 4 :-    using "auto" but as "integer"   called as   "for-each loop"
void output_auto_int(){     
    for(auto it : v9){      // By this syntax, "it" instead of pointing to memory address, it will directlt point to value of first element.
        cout<<it;
    }
    cout<<endl;
}

// Erasing of elements in a vector :-

vector <int> v10 = {33,44,55,66,44,55,34,34,23,31};

// Method - 1 :-    Deletion of single element :-
void erase_single(){
    cout<<"Erasing single element :-"<<endl;
    v10.erase(v10.begin()+2);
    for(auto it = v10.begin();it != v10.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

// Method - 2 :-
void erase_multiple(){
    cout<<"Erasing multiple elements :-"<<endl;
    v10.erase(v10.begin(),v10.begin()+4);
    for(auto it : v10){
        cout<<it<<" ";
    }
    cout<<endl;
}

// Insert elements into a vector :-
// Method - 1 :-    Inserting single element into a vector  v.insert(position,element)
void insert_single(){
    vector<int> v = {33,22,43,46,76};
    v.insert(v.begin()+2,222);
    cout<<"Printing vector after inserting 222 into the vector :-"<<endl;
    for(auto it : v){
        cout<<it<<" ";
    }
    cout<<endl;
}

// Method - 2 :-    Inserting multiple elements into a vector   v.insert(position,no. of instances,element)
void insert_multiple(){
    vector<int> v = {33,22,43,46,76};
    v.insert(v.begin()+2,4,222);
    cout<<"Printing vector after inserting 222 for 4 times into the vector :-"<<endl;
    for(auto it : v){
        cout<<it<<" ";
    }
    cout<<endl;
}

// Method - 3 :-       Inserting some elements of vector v_ into another vector v at specified position.
void insert_copy(){
    vector <int> v ={33,43,34};
    vector <int> v_ ={22,334};
    v.insert(v.begin(),v_.begin(),v_.end()-1);
    cout<<"Printing vector after inserting a vector v_ into the vector v :-"<<endl;
    for(auto it : v){
        cout<<it<<" ";
    }
    cout<<endl<<"The size of v is "<<v.size();
    cout<<endl;
}

// pop_back() :-    Pops or deletes the last element of the vector.
void pop_vector(){
    vector <int> v= {33,44,23,54};
    v.pop_back();
    cout<<"Printing vector after using pop_back() :-"<<endl;
    for(auto it =v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

// Swapping vectors :-
void swap_vectors(){
    vector <int> v1(4,5);
    vector <int> v2(3,3);
    cout<<"Vector v1 before swapping :-"<<endl;
    for(auto it =v1.begin();it!=v1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl; 
    cout<<"Printing v2 before swapping :-"<<endl;
    for(auto it =v2.begin();it!=v2.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    v2.swap(v1);
    cout<<"Printing v1 after swapping :-"<<endl;
    for(auto it =v1.begin();it!=v1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl; 
    cout<<"Printing v2 after swapping :-"<<endl;
    for(auto it =v2.begin();it!=v2.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

// Clearing the whole vector :-
void clear(){
    vector <int> v ={23,43,45};
    cout<<"Printing vector v before clearing :-"<<endl;
    for(auto it =v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    v.clear();   
    cout<<"Printing vector v after clearing :-"<<endl;      // I am getting output as "blank line"
    for(auto it =v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

// Checks whether a vector is empty or not :-
void vector_empty(){
    vector <int> v ={23,43,45};
    cout<<"Before clearing vector v :-"<<endl;
    cout<<"Is the vector v empty before clearing :- "<<v.empty()<<endl;
    v.clear();
    cout<<"Is the vector v empty after clearing :- "<<v.empty()<<endl;
}

int main(){
    cout<<"Printing using array method :- "<<endl;
    output_arr();
    cout<<"Printing using iterator :- "<<endl;
    output_iter();
    cout<<"Print using auto iterator :-"<<endl;
    output_auto_iter();
    erase_single();
    erase_multiple();
    insert_single();
    insert_multiple();
    insert_copy();
    pop_vector();
    swap_vectors();
    clear();
    vector_empty();
    return 0;
}