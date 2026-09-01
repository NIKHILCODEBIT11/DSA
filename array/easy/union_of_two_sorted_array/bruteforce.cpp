// Here, i am going to take a set data structure and traverse over both the SORTED array num1 and num2
// and add each element to the set, and since it is a set so it wont be having repeating values
// Then i will traverse over the set and put each element in vector union and will return it

#include<bits/stdc++.h>
using namespace std;

vector <int> union_of_two_sorted_array(vector <int> &nums_1, vector <int> &nums_2){
    int n1 = nums_1.size();
    int n2 = nums_2.size();
    set <int> st;

    for(int i = 0; i < n1; i++){
        st.insert(nums_1[i]);
    }
    for(int i = 0; i < n2; i++){
        st.insert(nums_2[i]);
    }

    vector <int> union_array;
    int i = 0;
    for(auto it : st){
        union_array.push_back(it);
    }

    return union_array;
}

int main(){
    int n1, n2;
    cout<<"Enter size of first vector :-";
    cin>>n1;
    vector <int> nums_1(n1);
    cout<<"Enter elements for first vector :- ";
    for(int i = 0; i < n1; i++){
        cin>>nums_1[i];
    }
    cout<<"Enter size of second vector :-";
    cin>>n2;
    vector <int> nums_2;     // It gets created of size 0
    cout<<"Enter elements for second vector :- ";
    for(int i = 0; i < n2; i++){
        int input;
        cin>>input;
        nums_2.push_back(input);   // And then each element is pushed back till n2 size
    }
    vector <int> final = union_of_two_sorted_array(nums_1, nums_2);
    for(auto it : final){
        cout<<it<<" ";
    }
    return 0;
}

// Yes, exactly! In C++, std::set automatically keeps elements both unique and sorted in ascending order by default.

// Doubt :-
// Why does when insertion in set takes O(logN) tc then why in final it is O(N1*logN1) :-
/*
for (int i = 0; i < n1; i++) {
    st.insert(nums_1[i]);
}

The tree grows with each step, changing the set size ($K$):
1st insertion: set size is 0 ---> cost is (log 1)
2nd insertion: set size is 1 ---> cost is (log 2)
3rd insertion: set size is 2 ---> cost is (log 3)
N_1th insertion: set size is N_1 - 1 ---> cost is O(log N_1)

To find the total time spent across the entire loop, you add up the work done at every single step:
{Total Time} = log(1) + log(2) + log(3) + .... + log(N_1)

Applying Log Rules
Using logarithmic rules, a sum of logarithms equals the logarithm of their product:
$$\sum_{i=1}^{N_1} \log(i) = \log(1 * 2 * 3 * ..... * N_1) = log(N_1!)
By Stirling's Approximation, the logarithm of a factorial is bounded by:$$\log(N_1!) \approx N_1 \log N_1 - N_1$$

In Big-O notation, we drop the lower-order term (-N_1) and constant factors, which leaves:
O(N1*logN1)
*/

// TC :- O(N1*logN1 + n2*logN2) + O(N1+N2) ----> First two are for insertion into set from both the arrays and third one is inserting into final union_array which is a vector
// SC :- O(N1 + N2) + O(N1 + N2)   ---> One is for union_array and one is for final array