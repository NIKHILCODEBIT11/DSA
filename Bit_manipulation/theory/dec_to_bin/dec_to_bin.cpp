#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (DECIMAL TO BINARY CONVERSION):
   - Problem Statement:
     Ek positive base-10 integer 'n' ko uske equivalent base-2 (binary) string
     representation mein convert karna hai.

   - Division by 2 & Remainder Property:
     - Kisi bhi number 'n' ka last binary bit (LSB - Least Significant Bit)
       hamesha `n % 2` (remainder) hota hai.
       - Agar odd hai toh remainder 1 (LSB = '1').
       - Agar even hai toh remainder 0 (LSB = '0').
     - Number ko 1 bit right-shift karne ke liye hum integer division `n = n / 2` karte hain.
     - Is loop se bits Least Significant (peeche se) to Most Significant (aage ki taraf)
       generate hote hain.
     - Isliye end mein string ko `reverse(res.begin(), res.end())` karna zaroori hota hai.

   - Code Insight & C++ Syntax Note:
     Tere comment mein likha tha:
     `res.push_back((n%2 == 1) ? "1" : "0");`  // ❌ Syntax Error!
     - `push_back()` single character (`char`) accept karta hai.
     - `"1"` double quotes mein string literal hai (`const char*`).
     - Sahi ternary version:
       `res.push_back((n % 2 == 1) ? '1' : '0');`
       Ya direct arithmetic:
       `res.push_back((n % 2) + '0');`

   - Bitwise Alternative (Interview Pro-Tip):
     - `n % 2` ke badle: `(n & 1)` (Bitwise AND with 1 - checks LSB in 1 CPU cycle).
     - `n / 2` ke badle: `(n >> 1)` (Right shift by 1 bit).

======================================================================
2. DETAILED DRY RUN:
   Input: n = 17

   Initial: res = ""

   - Iteration 1:
     n = 17
     17 % 2 == 1  --> push_back('1') -> res = "1"
     n = 17 / 2 = 8

   - Iteration 2:
     n = 8
     8 % 2 == 0   --> push_back('0') -> res = "10"
     n = 8 / 2 = 4

   - Iteration 3:
     n = 4
     4 % 2 == 0   --> push_back('0') -> res = "100"
     n = 4 / 2 = 2

   - Iteration 4:
     n = 2
     2 % 2 == 0   --> push_back('0') -> res = "1000"
     n = 2 / 2 = 1

   - Iteration 5:
     n = 1
     1 % 2 == 1   --> push_back('1') -> res = "10001"
     n = 1 / 2 = 0

   Loop terminates (n = 0).

   Reverse Step:
   reverse("10001") => "10001" (16 + 1 = 17)

   Result: "10001"

======================================================================
3. COMPLEXITY ANALYSIS:
   - Time Complexity: O(log2 N)
     Har iteration mein number aadha ho raha hai (`n = n / 2`), toh loop
     theek number of bits ke barabar (approx ceil(log2 N)) baar chalta hai.
     String reversal time bhi O(log2 N) hota hai.
   - Space Complexity: O(log2 N)
     Resultant binary string ki length binary representation ke bits ke barabar hoti hai.
======================================================================
*/


string convert_dec_to_bin(int n){
    if (n == 0) return "0";
    string res = "";
    while(n > 0){
        // neeche ke if-else block ke badle mein    res.push_back((n%2 == 1) ? "1" : "0");
        if(n%2 == 1){
            res.push_back('1');
        }
        else{
            res.push_back('0');
        }
        n = n/2;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main(){
    int n = 17;
    string bin = convert_dec_to_bin(n);
    cout<<bin;
    return 0;
}