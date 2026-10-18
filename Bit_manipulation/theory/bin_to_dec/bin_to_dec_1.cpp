#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BINARY TO DECIMAL CONVERSION):
   - Problem Statement:
     Ek binary string di gayi hai (jaise "10001"), use uske base-10 decimal
     integer value (17) mein convert karna hai.

   - Positional Weight Logic (Powers of 2):
     Binary system base-2 positional numeral system hota hai:
     String:   x[0]   x[1]   x[2]   ...   x[n-1]
     Weights:  2^(n-1) ...   2^2    2^1   2^0 (LSB)

     - Traversal Right to Left (`i = len - 1` down to `0`):
       - Sabse aakhri character ka weight $2^0 = 1$ hota hai (`p2 = 1`).
       - Har step left aane par weight 2x multiply hota jata hai (`p2 *= 2`).
       - Agar bit `'1'` hai, toh us position ka weight `num` mein add kar do (`num += p2`).
       - Agar bit `'0'` hai, toh kuch add nahi karna.

   - ⚠️ TERE COMMENT MEIN EK CRITICAL CORRECTION:
     Tune comment mein likha:
     `// p2 <<= 2 bhi likh sakta hu jiska matlab hai p2 <<= k ---> p2 * 2^k`
     
     👉 Caution:
     - `p2 <<= 1` ka matlab hota hai $p2 \times 2^1 = p2 \times 2$ (Yeh sahi hai).
     - Agar tune `p2 <<= 2` likha, toh uska matlab hoga $p2 \times 2^2 = p2 \times 4$ (Yeh galat ho jayega!).
     - So: `p2 *= 2` ko replace karna ho toh **`p2 <<= 1`** likhna, na ki `p2 <<= 2`.

   - Alternative Horner's Method (Left to Right Scan):
     `p2` variable rakhe bina bhi kar sakte ho:
     ```cpp
     int num = 0;
     for (char ch : x) {
         num = (num << 1) + (ch - '0'); // num = num * 2 + bit
     }
     ```

======================================================================
2. DETAILED DRY RUN:
   Input: x = "10001"
   len = 5
   num = 0, p2 = 1

   - Iteration 1 (i = 4, x[4] = '1'):
     x[4] == '1' -> num += 1 => num = 1
     p2 *= 2 => p2 = 2

   - Iteration 2 (i = 3, x[3] = '0'):
     x[3] == '0' -> no addition
     p2 *= 2 => p2 = 4

   - Iteration 3 (i = 2, x[2] = '0'):
     x[2] == '0' -> no addition
     p2 *= 2 => p2 = 8

   - Iteration 4 (i = 1, x[1] = '0'):
     x[1] == '0' -> no addition
     p2 *= 2 => p2 = 16

   - Iteration 5 (i = 0, x[0] = '1'):
     x[0] == '1' -> num += 16 => num = 1 + 16 = 17
     p2 *= 2 => p2 = 32

   Loop terminates!
   Output: 17

======================================================================
3. COMPLEXITY ANALYSIS:
   - Time Complexity: O(len) = O(N)
     String ke har character ko exactly ek baar right-to-left scan kiya gaya.
   - Space Complexity: O(1) Auxiliary Space
     Sirf do integer variables (`num`, `p2`) use hue.
======================================================================
*/


int convert_bin_to_dec(string x){

    // calculate length of string:
    int len = x.length();
    int num = 0;
    int p2 = 1;

    for(int i = len - 1; i >= 0 ;i--){
        if(x[i] == '1'){
            num += p2;
        }
        p2 *= 2;   // yaha pe   p2 <<= 2 bhi likh sakta hu jiska matlab hai p2 <<= k ---> p2 * 2^k
    }
    return num;
}

int main(){
    string x = "10001";
    int dec = convert_bin_to_dec(x);
    cout<<dec;
    return 0;
}