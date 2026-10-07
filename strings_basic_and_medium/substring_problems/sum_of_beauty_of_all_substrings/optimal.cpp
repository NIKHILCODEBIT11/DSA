#include<bits./stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SUM OF BEAUTY OF ALL SUBSTRINGS):
   - Problem:
     Hume ek string 's' di gayi hai. Kisi bhi substring ki "Beauty" ka matlab 
     hota hai:
       Beauty = (Highest character frequency) - (Lowest NON-ZERO character frequency)
     Hume string ke saare possible substrings ki beauty calculate karke unka 
     total sum return karna hai.

   - Brute Force Se Better Approach (Rolling Frequency Count):
     - Agar hum saare substrings alag se banayein aur har substring ke liye 
       shuru se frequency count karein, toh O(N^3) time lag jayega jo TLE dega.
     - Better Idea:
       Jab hum starting index 'i' fix karte hain aur ending index 'j' ko aage badhate hain, 
       toh naya substring pichle substring me sirf EK character jod kar banta hai!
       Example: "aab" se agla substring "aabc" banane ke liye sirf 'c' add hua.
       Toh har baar nayi frequency array banane ke badle hum current frequency array 
       me sirf `s[j]` ka count +1 karte chalenge.

   - Finding Min and Max Efficiently:
     String me sirf lowercase English alphabets ('a' se 'z') hain, yani exactly 26 possible characters.
     Har baar jab ek character add hota hai:
     - 26-size ke array par loop chalakar max aur min frequency nikalna sirf 26 steps leta hai.
     - 26 ek constant number hai (O(26) = O(1)).
     - Min nikalte waqt bas dhyan rakhna hai ki `freq[k] > 0` hona chahiye, kyunki jo character 
       substring me aaya hi nahi uski frequency 0 ko min nahi maanna hai.

   - Note on Header:
     Code me `#include<bits./stdc++.h>` likha hai, dot '.' galti se lag gaya hai. 
     Standard header `#include<bits/stdc++.h>` hota hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - int total_beauty = 0; :
     Saare substrings ki beauties ka cumulative sum store karne ke liye.
   - for(int i = 0; i < n; i++) :
     Substring ka starting point 'i' fix kiya.
   - vector<int> freq(26, 0); :
     Har naye starting point 'i' ke liye 26 characters ki frequency 0 se reset ki.
   - for(int j = i; j < n; j++) :
     Substring ka ending point 'j' expand kiya. Substring 's[i...j]' dynamically form ho rahi hai.
   - freq[s[j] - 'a']++; :
     Naye character ki frequency directly increment ki without re-scanning the whole substring.
   - for(int k = 0; k < 26; k++) if(freq[k] > 0) ... :
     26 buckets check kiye. Jo characters present hain (`freq[k] > 0`), unme se 
     maximum aur minimum frequency find ki.
   - total_beauty += max_freq - min_freq; :
     Current substring ki beauty calculate karke answer me add kar di.
   - return total_beauty; :
     Saare substrings process hone ke baad total sum return kar diya.

======================================================================
3. DETAILED DRY RUN:

   Input: s = "aabcbaa", n = 7
   Small example slice dekhte hain jab i = 0 ('a'):

   --- i = 0, j = 0 -> Substring "a" ---
   freq['a'] = 1
   Present frequencies: {1}
   max_freq = 1, min_freq = 1
   Beauty = 1 - 1 = 0
   total_beauty = 0

   --- i = 0, j = 1 -> Substring "aa" ---
   freq['a'] = 2
   Present frequencies: {2}
   max_freq = 2, min_freq = 2
   Beauty = 2 - 2 = 0
   total_beauty = 0

   --- i = 0, j = 2 -> Substring "aab" ---
   freq['a'] = 2, freq['b'] = 1
   Present frequencies: {2, 1}
   max_freq = 2, min_freq = 1
   Beauty = 2 - 1 = 1
   total_beauty = 0 + 1 = 1

   --- i = 0, j = 3 -> Substring "aabc" ---
   freq['a'] = 2, freq['b'] = 1, freq['c'] = 1
   Present frequencies: {2, 1, 1}
   max_freq = 2, min_freq = 1
   Beauty = 2 - 1 = 1
   total_beauty = 1 + 1 = 2

   --- i = 0, j = 4 -> Substring "aabcb" ---
   freq['a'] = 2, freq['b'] = 2, freq['c'] = 1
   Present frequencies: {2, 2, 1}
   max_freq = 2, min_freq = 1
   Beauty = 2 - 1 = 1
   total_beauty = 2 + 1 = 3

   --- i = 0, j = 5 -> Substring "aabcba" ---
   freq['a'] = 3, freq['b'] = 2, freq['c'] = 1
   Present frequencies: {3, 2, 1}
   max_freq = 3, min_freq = 1
   Beauty = 3 - 1 = 2
   total_beauty = 3 + 2 = 5

   --- i = 0, j = 6 -> Substring "aabcbaa" ---
   freq['a'] = 4, freq['b'] = 2, freq['c'] = 1
   Present frequencies: {4, 2, 1}
   max_freq = 4, min_freq = 1
   Beauty = 4 - 1 = 3
   total_beauty = 5 + 3 = 8

   Isi tarah i = 1, 2, ... 6 ke saare substrings add honge.
   Final total_beauty for "aabcbaa" = 17.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Outer loop 'i' chalta hai: N times.
     * Inner loop 'j' chalta hai: average N/2 times -> total substrings = N * (N + 1) / 2 = O(N^2).
     * Har substring ke liye 26 characters ka loop chalta hai: O(26) = O(1) constant time.
     * Total Time Complexity: O(26 * N^2) = O(N^2).
     * N <= 500 ke constraints ke liye N^2 operations lagbhag 2.5 * 10^5 hote hain, jo easily 
       1-2 milliseconds me pass ho jata hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Vector 'freq' ka size fixed 26 hai chahe string ki length kitni bhi badi ho.
     * Memory allocation completely constant O(26) = O(1) hai.
======================================================================
*/

int beautySum(string s) {
        int n = s.size();
        int total_beauty = 0;
        for(int i = 0; i < n; i++){
            vector <int> freq(26, 0);

            for(int j = i; j < n; j++){
                freq[s[j] - 'a']++;

                int max_freq = INT_MIN;
                int min_freq = INT_MAX;

                for(int k = 0; k < 26; k++){
                    if(freq[k] > 0){
                        max_freq = max(max_freq, freq[k]);
                        min_freq = min(min_freq, freq[k]);
                    } 
                }
                total_beauty += max_freq - min_freq;
            }
        }
        return total_beauty;
}

int main(){
    string s = "aabcbaa";
    cout<<"The beauty sum is "<<beautySum(s);
    return 0;
}

/*
================================================================================
DOUBT 1: Substring alag se string banakar ek saath kyun nahi padh rahe?
         ("abb" ko ek saath read karke frequency kyun nahi banayi?)
================================================================================

QUESTION:
Code mein hum `s.substr()` karke alag se string kyun nahi kaat rahe?
Hum ek-ek character `freq[s[j] - 'a']++` karke substring kaise cover kar le rahe hain?

ANSWER:
Kyunki har bar naya string cut karna (s.substr) extra time aur memory khata hai.
Substrings continuous hoti hain, iska fayda uthate hain:

Maan lo i = 0 hai:
- j = 0 par char mila 'a' -> freq array mein gaya 'a': 1
  -> Yeh ban gaya substring "a" ka data.
- j = 1 par naya char mila 'b' -> freq array mein jud gaya 'b': 1
  -> Purane 'a' ke saath naya 'b' milkar ban gaya "ab" ka data (a:1, b:1).
- j = 2 par fir mila 'b' -> 'b' ka count 1 se badh kar ho gaya 2
  -> Ab array mein hai (a:1, b:2). Yeh automatically ban gaya "abb" ka data!

Humein poora "abb" ek saath scan karne ki koi zaroorat hi nahi padi!
Har step par purane data mein bas naya letter "+1" hota gaya aur
naya substring khud-ba-khud taiyaar hota gaya.


================================================================================
DOUBT 2: max_freq aur min_freq har character (j loop) par reset kyun hote hain?
================================================================================

QUESTION:
`int max_freq = INT_MIN;` aur `int min_freq = INT_MAX;` ko humne `j` loop ke
andar kyun rakha? Yeh toh har ek character aane par reset ho ja rahe hain!

ANSWER:
Haan, aur inko reset hona hi chahiye!
Kyunki `max_freq` aur `min_freq` poori string ke nahi hain, balki SIRF US EK
SUBSTRING ke hain jo us waqt bani hai.

Example se samjho:
Maan lo tukda bana "aa" (a: 2).
- Yahan Max = 2, Min = 2.
Agla letter 'b' jud gaya, naya tukda bana "aab" (a: 2, b: 1).
- Ab is NAYE tukde ke liye hume taaza Max aur Min dhoondhna padega na?
- Naye tukde ka Max = 2, Min = 1.

Agar tumne min_freq ko reset nahi kiya:
Socho pehle kisi tukde ka min_freq 1 tha. Aage chal kar ek aisa tukda aaya
jisme letters the "aaaa" (a: 4).
Is tukde ka actual min hona chahiye tha 4.
Lekin agar puraana min_freq reset nahi hua, toh usme puraana 1 hi bacha
reh jayega, aur answer galat ho jayega!
Isliye har NAYI substring ke liye scanner ko taaza (reset) karna padta hai.


================================================================================
DOUBT 3: if (freq[k] > 0) kyun lagaya? Direct min/max kyun nahi nikala?
================================================================================

QUESTION:
Agar hum yeh `if (freq[k] > 0)` hata dein aur seedha:
`min_freq = min(min_freq, freq[k]);` likh dein toh kya problem aayegi?

ANSWER:
Yeh is question ka sabse bada trap hai!
Hamara freq array 26 size ka hai ('a' se lekar 'z' tak).

Maan lo hamara tukda hai "aa".
Iske andar sirf 'a' aaya hai. Baaki saare 25 letters ('b' se lekar 'z') ka
count array mein kya pada hai? ZERO (0)!

Agar tum bina `if` ke loop chalaoge:
1. k = 0 ('a'): freq[0] = 2 -> min_freq = 2 ban gaya.
2. k = 1 ('b'): freq[1] = 0 -> min_freq = min(2, 0) = 0 ho gaya!
3. k = 2 ('c'): freq[2] = 0 -> min_freq = 0 hi raha.

Aakhiri mein:
Max = 2 ('a')
Min = 0 (wo letters jo string mein the hi nahi!)
Beauty = Max - Min = 2 - 0 = 2 (GALAT! "aa" ki beauty 0 honi chahiye).

Question ne bola hai: "least frequent character jo us substring mein MAUJOOD ho."
Jo letter aaya hi nahi (jiska count 0 hai), usko minimum nahi maan sakte!
Isliye `if (freq[k] > 0)` guard lagata hai taaki computer sirf unhi letters
ko compare kare jo sach mein string ke andar maujood hain.


================================================================================
DOUBT 4: freq array ko 'i' loop ke andar kyun banaya, bahar kyun nahi?
================================================================================

QUESTION:
`vector<int> freq(26, 0);` ko sabse upar function ke shuru mein kyun nahi rakha?
Bahar rakhne se kya dikkat aati?

ANSWER:
Outer loop `i` ka matlab hai: "Substring shuru kahan se ho rahi hai."
- Jab i = 0 tha, humne index 0 se shuru hone wale saare tukde check kar liye.
- Ab jab i = 1 hua, hum index 1 se NAYI shuruat kar rahe hain!

Agar freq array ko bahar rakhte, toh index 0 wale letters ka count usme
pehle se jama rehta.
Nayi shuruat ke liye dabba bilkul khali hona chahiye.
Isliye har naye `i` ke shuru hote hi naya `freq(26, 0)` banta hai jisme
saari ginti wapas 0 hoti hai.


================================================================================
DOUBT 5: freq[s[j] - 'a']++ ka kya matlab hota hai?
================================================================================

QUESTION:
Yeh `s[j] - 'a'` karke index nikaalne ka math kya hai?

ANSWER:
Computer mein har character ka ek ASCII number hota hai:
'a' = 97, 'b' = 98, 'c' = 99 ... 'z' = 122.
Lekin hamara array 0 se 25 tak ke index ka hota hai.

Toh hum base character ('a') ko minus karke 0-based index banate hain:
- Agar char 'a' hai: 'a' - 'a' = 97 - 97 = 0 -> freq[0] badhega ('a' ke liye)
- Agar char 'b' hai: 'b' - 'a' = 98 - 97 = 1 -> freq[1] badhega ('b' ke liye)
- Agar char 'c' hai: 'c' - 'a' = 99 - 97 = 2 -> freq[2] badhega ('c' ke liye)

Isse bina kisi hashmap ke, fixed 26 size ke array mein direct O(1) mapping
ho jati hai.


================================================================================
DOUBT 6: Loop complexity O(n^2 * 26) placement ke hisaab se pass kyun hogi?
================================================================================

QUESTION:
Yahan 3 loops dikh rahe hain (i loop, j loop, k loop).
Kya yeh O(n^3) ho kar Time Limit Exceed (TLE) nahi karega?

ANSWER:
Nahi! Kyunki teesra loop 'k' string ki length par depend nahi karta.
Teesra loop hamesha exactly 26 baar hi chalta hai (constant time O(26)).

Calculation:
- n <= 500 diya hai.
- Total substrings = n * (n + 1) / 2 = (500 * 501) / 2 = 125,250.
- Har substring ke liye 26 steps: 125,250 * 26 ≈ 3.25 * 10^6 operations.

C++ 1 second mein lagbhag 10^8 (10 crore) operations kar leta hai.
Hamara code sirf 32 lakh operations kar raha hai, jo 0.02 second mein execute
ho jayega. Isliye yeh solution 100% optimal aur accepted hai.
================================================================================
*/