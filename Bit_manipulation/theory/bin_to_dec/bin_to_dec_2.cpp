// homer's method

#include <iostream>
#include <string>

using namespace std;

int convert_bin_to_dec(string x) {
    int num = 0;
    
    for (char c : x) {
        // Purane value ko left shift / 2 se multiply karo, 
        // aur current bit ko convert karke add karo.
        num = (num * 2) + (c - '0');
    }
    
    return num;
}

int main() {
    string x = "10001";
    int dec = convert_bin_to_dec(x);
    cout << "Binary: " << x << " -> Decimal: " << dec << endl;
    return 0;
}

/*
======================================================================
              HORNER'S METHOD KA MATHEMATICAL INTUITION
======================================================================

1. Decimal Number "352" Ka Example:
-----------------------------------
Aap bachpan se "352" ko expand karna jante hain:
   352 = 3 * 10^2 + 5 * 10^1 + 2 * 10^0

Horner's rule isko bracket mein fold kar deta hai:
   352 = ((3 * 10) + 5) * 10 + 2

Left-to-Right build karne ka step-by-step logic:
   - Shuru:   num = 0
   - Digit 3: num = (0 * 10) + 3   = 3
   - Digit 5: num = (3 * 10) + 5   = 35
   - Digit 2: num = (35 * 10) + 2  = 352

Decimal ka base 10 hai, isliye har step par 10 se multiply hota hai.


2. Binary Number "10001" (Decimal = 17) Par Wahi Logic:
-------------------------------------------------------
Normal Expansion:
   10001 = 1 * 2^4 + 0 * 2^3 + 0 * 2^2 + 0 * 2^1 + 1 * 2^0

Horner's Rule (Powers calculate karne ki zaroorat nahi):
   10001 = ((((1 * 2 + 0) * 2 + 0) * 2 + 0) * 2 + 1)

Step-by-step trace:
   - Shuru:     num = 0
   - Char '1':  num = (0 * 2) + 1  = 1
   - Char '0':  num = (1 * 2) + 0  = 2
   - Char '0':  num = (2 * 2) + 0  = 4
   - Char '0':  num = (4 * 2) + 0  = 8
   - Char '1':  num = (8 * 2) + 1  = 17

Fayda: 
O(1) extra space lagti hai, na string reverse karni padti hai, 
na hi alag se power of 2 ka variable maintain karna padta hai.
======================================================================
*/