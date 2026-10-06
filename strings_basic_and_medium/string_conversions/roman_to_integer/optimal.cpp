#include<bits/stdc++.h>
using namespace std;

int value(char ch){
    switch(ch){
        case 'I' : return 1;
        case 'V' : return 5;
        case 'X' : return 10;
        case 'L' : return 50;
        case 'C' : return 100;
        case 'D' : return 500;
        case 'M' : return 1000;
        // default is must 
        default : return 0;
    }
}

int romanToInt(string s) {
    int total = 0;
    int n = s.length();
    for(int i = 0; i < s.length(); i++){
        if(i+1 < n && value(s[i]) < value(s[i+1])){
            total -= value(s[i]);
        }
        else{
            total += value(s[i]);
        }
    }
    return total;
}

int main(){
    string s = "MCMXCIV";
    cout<<"The equivalent conversion of "<<s<<" is "<<romanToInt(s);
    return 0;
}