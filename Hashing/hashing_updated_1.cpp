#include<iostream>
#include<string>
#include<stdexcept>
using namespace std;
int main(){
    int arr[]={2,2,3,2,4,3,5,4,3,2,9,8,5,4,0,0,3,0};
    string inp;
    int max=arr[0];
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        if(max<arr[i]){
            max=arr[i];
        }
        else{
            continue;
        }
    }
    int hash[max]={0};
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        hash[arr[i]]++;
    }
    while(1){
        cout<<"Enter the value whose repition is required :- ";
        getline(cin,inp);
        if(inp.empty()){
            cout<<"Done"<<endl;
            break;
        }
        try{
            auto value=stoi(inp);   
            cout<<"The repetition of "<<inp<<" is "<<hash[value]<<endl; 
        }
        catch(invalid_argument){
            cout<<"Invalid argument"<<endl;
        }
        catch(out_of_range){        // It will not check whether inserted input is within index, if it gets large number as 6767676676767 then it will display this
            cout<<"Index out of range"<<endl;
        }
    }
    return 0;
}


/*
The correct way of using catch is :-

catch (const invalid_argument& e) {
    cout << "Invalid argument! Please enter a valid integer." << endl;
}
catch (const out_of_range& e) {
    cout << "Input is out of range! Please enter a valid integer within the acceptable range." << endl;
}


*/