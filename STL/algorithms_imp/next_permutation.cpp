// The algorithm  "next_permutaion(begin,end)" gives me all the possible permutaions, as just like sort(), even it returns boolean 
//value "true" or "false" and when all possible permutations are done, then it returns false

#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

bool com(string s1){        // I am getting error in here, because it has to be like    std::string s1, because i wrote "using namespace std", below this function definition
    if(s1[s1.size()-2]>s1[s1.size()-1]){
        return true;
    }
    else{
        return false;
    }
}

// using namespace std;

int main(){
    string s = "1234";
    cout<<"Printing all the possible permutaions of the string :-"<<endl;
    do{
        cout<<s<<" ";
    }
    while(next_permutation(s.begin(),s.end()) ||com(s));    //  "&&" is the "AND" operator, which returns true or false based on two boolean expressions, here "next_permutation(s.begin(),s.end())"" is one boolean expression and "com(s)"" is another boolean expression
    return 0;
}

// Just some use of || (or operator) nothing else.