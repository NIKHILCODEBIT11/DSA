#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
  KYUN 'hashset' KO HAR BAAR LOOP KE ANDAR (i KE AAGE BADHNE PAR) RECREATE /
  CLEAR KARNA JARURI HAI?
================================================================================

  SAWAL:
  Agar 'set<int> hashset;' ko loop ke bahar sirf 1 baar banate aur har naye 'i'
  par reset na karte, to kya problem aati? Bahar wala 'st' to duplicate triplets
  waise bhi filter kar deta hai na?

  JAWAB:
  Problem duplicates ki nahi hai. Problem ye hai ki agar hashset clear nahi kiya,
  to CODE WRONG ANSWER DEGA (ek hi element ko 2 baar use kar lega, jo allowed
  nahi hai). 

--------------------------------------------------------------------------------
  CONCRETE EXAMPLE SE SAMAJHTE HAIN:
--------------------------------------------------------------------------------
  Maan lo array ye hai:
  nums = [1, 2, -1]
  Indices:
    index 0 =  1
    index 1 =  2
    index 2 = -1

  Asliyat (Correct Answer):
  Teeno ko jod kar dekho: 1 + 2 + (-1) = 2 (sum 0 nahi banta).
  Array me koi triplet possible hi nahi hai.
  Sahi Output aana chahiye: [] (Empty array)

--------------------------------------------------------------------------------
  AGAR HASHSET BAHAR HOTA (KHALI NAHI KIYA JATA) TO KYA KAAND HOTA:
--------------------------------------------------------------------------------
  Iteration 1 (Jab i = 0, nums[0] = 1):
    - j = 1 (nums[1] = 2) chalega.
      hashset abhi khali hai. 2 insert ho gaya.
      hashset = {2}

    - j = 2 (nums[2] = -1) chalega.
      third = -(1 + -1) = 0 (nahi mila).
      hashset me -1 insert ho gaya.
      hashset = {2, -1}

    Yaha tak Round 1 khatam. Lekin hashset me pichle elements {2, -1} baithe hain!

  Iteration 2 (Jab i = 1, nums[1] = 2):
    - j = 2 (nums[2] = -1) chalega.
    - Code teesra number mangega:
        third = -(nums[i] + nums[j])
        third = -(2 + (-1))
        third = -1

    - Ab code check karega: kya hashset me -1 hai?
    - BOOM! Hashset me pichle round (j = 2) ka dala hua -1 pehle se baitha hai!
    - Code sochega: "-1 mil gaya! Triplet ban gaya: {2, -1, -1}".
    - Aur ye triplet 'st' ke andar save ho jayega.

--------------------------------------------------------------------------------
  YAHA GALTI KYA HUI?
--------------------------------------------------------------------------------
  Array me -1 sirf EK HI BAAR tha (index 2 par).
  Lekin code ne:
    * nums[j] ke roop me bhi index 2 ke -1 ko le liya.
    * third ke roop me bhi pichle round se usi -1 ko wapas use kar liya.

  Yaani ek hi element ko 2 baar ghasit kar invalid answer bana diya.
  'st' (final set) is galat triplet ko filter nahi kar sakta kyunki uske
  hisaab se {2, -1, -1} ek naya mathematical combination hai.

--------------------------------------------------------------------------------
  GOLDEN RULE (JO YAAD RAKHNA HAI):
--------------------------------------------------------------------------------
  'third' element hamesha wahi hona chahiye jo CURRENT 'i' aur CURRENT 'j'
  ke BEECH me aata ho (index i se aage aur index j se pehle).

  Pichle kisi 'i' ke rounds me dekhe gaye elements ko naye round me search
  nahi kiya ja sakta.

  Isliye har baar jab 'i' aage badhta hai, hume ek ekdum KHAALI (fresh)
  'hashset' chahiye hota hai taaki purane rounds ka kachra current calculation
  ko corrupt na kare.
================================================================================
*/

vector<vector<int>> three_sum(vector <int> &nums){
    int n = nums.size();
    set<vector<int>> st;
    for(int i = 0; i < n; i++){
        set<int> hashset;
        for(int j = i+1; j < n; j++){
            int third = -(nums[i] + nums[j]);
            if(hashset.find(third) != hashset.end()){
                vector <int> temp = {nums[i], nums[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashset.insert(nums[j]);
        }
    }
    vector <vector<int>> ans(st.begin(), st.end());
    return ans;
}

int main(){
    vector <int> nums = {-2, -2, -2, 0, 0, 0, 2, 2, -1, -1, -1, 2, 2};
    cout<<"The three numbers giving sum as 0 are :-"<<endl;
    vector<vector<int>> ans = three_sum(nums);
    for(auto row : ans){
        for(int x : row){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    return 0;
}

/*
================================================================================
  3-SUM (BETTER APPROACH USING HASHING)
================================================================================

  CORE INTUITION (Dimaag me logic kaise build hua?):
  --------------------------------------------------
  1. Brute force me 3 loop lagte the O(N^3):
     nums[i] + nums[j] + nums[k] == 0.
  
  2. Math ka use karke teesra loop gayab kar sakte hain:
     Agar nums[i] aur nums[j] hum choose kar chuke hain,
     toh teesra number (third) fixed hai:
     ==> third = -(nums[i] + nums[j])
     
     Matlab hume teesra banda dhundhne ke liye pura array ghoomne ki
     zarurat nahi hai, bas ye check karna hai ki kya 'third' pehle dekha gaya hai.

  3. Hashset ka role:
     - 'i' fix rehta hai.
     - 'j' aage badhta hai.
     - 'hashset' un sabhi elements ki memory hai jo 'i' aur 'j' ke BEECH me aa chuke hain.
     - Jab bhi 'j' kisi element par aata hai, wo hashset se puchta hai:
       "Kya tere paas 'third' pada hai?"
       -> Agar HAAN: Mil gaya triplet! Use sort karke answer set 'st' me daal do.
       -> Chahe mile ya na mile: Agle aane wale 'j' ke liye current 'nums[j]'
          ko hashset me daal do taaki wo kisi aur ka 'third' ban sake.

  4. Sabse Badi Galti Jo Log Karte Hain (Why recreate hashset for every i?):
     - Agar hashset ko 'i' loop ke bahar bana diya, to purane rounds ke elements
       bhi andar baithe rahenge.
     - Isse ek hi element 2 baar use ho jayega (e.g., [1, 2, -1] me answer empty
       hona chahiye, par purana -1 match hokar [2, -1, -1] ban jayega).
     - Isliye HAR NAYE 'i' PAR FRESH HASHSET banna zaroori hai!

================================================================================
  STEP-BY-STEP COMPLETE DRY RUN
  Array: nums = [-1, 0, 1, 2, -1, -4]
  Indices:         0  1  2  3   4   5
================================================================================

  Global Storage:
  st = {} (Unique triplets store karne ke liye set<vector<int>>)

  ------------------------------------------------------------------------------
  ROUND 1: i = 0  -->  nums[i] = -1
  Fresh hashset = {}
  ------------------------------------------------------------------------------
  * j = 1  -->  nums[j] = 0
    - Needed: third = -((-1) + 0) = 1
    - Check: Kya 1 hashset me hai? NAHI (hashset khali hai)
    - Memory Update: hashset me nums[j] (0) daalo -> hashset = {0}

  * j = 2  -->  nums[j] = 1
    - Needed: third = -((-1) + 1) = 0
    - Check: Kya 0 hashset me hai? HAAN!
    - Action: Triplet mila {-1, 1, 0}
              Sort kiya -> {-1, 0, 1}
              st.insert({-1, 0, 1})
              st = { {-1, 0, 1} }
    - Memory Update: hashset me nums[j] (1) daalo -> hashset = {0, 1}

  * j = 3  -->  nums[j] = 2
    - Needed: third = -((-1) + 2) = -1
    - Check: Kya -1 hashset me hai? NAHI
    - Memory Update: hashset me nums[j] (2) daalo -> hashset = {0, 1, 2}

  * j = 4  -->  nums[j] = -1
    - Needed: third = -((-1) + (-1)) = 2
    - Check: Kya 2 hashset me hai? HAAN!
    - Action: Triplet mila {-1, -1, 2}
              Sort kiya -> {-1, -1, 2}
              st.insert({-1, -1, 2})
              st = { {-1, 0, 1}, {-1, -1, 2} }
    - Memory Update: hashset me nums[j] (-1) daalo -> hashset = {-1, 0, 1, 2}

  * j = 5  -->  nums[j] = -4
    - Needed: third = -((-1) + (-4)) = 5
    - Check: Kya 5 hashset me hai? NAHI
    - Memory Update: hashset me -4 daalo -> hashset = {-4, -1, 0, 1, 2}

  ------------------------------------------------------------------------------
  ROUND 2: i = 1  -->  nums[i] = 0
  PURANA HASHSET KHATAM (DESTROYED). Fresh hashset = {}
  ------------------------------------------------------------------------------
  * j = 2  -->  nums[j] = 1
    - Needed: third = -(0 + 1) = -1
    - Check: Kya -1 hashset me hai? NAHI (hashset abhi fresh bana hai)
    - Memory Update: hashset = {1}

  * j = 3  -->  nums[j] = 2
    - Needed: third = -(0 + 2) = -2
    - Check: Kya -2 hashset me hai? NAHI
    - Memory Update: hashset = {1, 2}

  * j = 4  -->  nums[j] = -1
    - Needed: third = -(0 + (-1)) = 1
    - Check: Kya 1 hashset me hai? HAAN!
    - Action: Triplet mila {0, -1, 1}
              Sort kiya -> {-1, 0, 1}
              st.insert({-1, 0, 1}) -> Pehle se maujood hai, DUPLICATE DISCARDED!
    - Memory Update: hashset = {-1, 1, 2}

  * j = 5  -->  nums[j] = -4
    - Needed: third = -(0 + (-4)) = 4
    - Check: Kya 4 hashset me hai? NAHI
    - Memory Update: hashset = {-4, -1, 1, 2}

  ------------------------------------------------------------------------------
  ROUNDS 3, 4, 5 (Jab i = 2, 3, 4):
  ------------------------------------------------------------------------------
  - Isi tarah loop aage badhega, har naye 'i' par hashset reset hoga.
  - Baki koi bhi combination sum 0 nahi banayega.

  FINAL RESULT:
  st ke andar sirf 2 unique triplets bache:
    1. {-1, 0, 1}
    2. {-1, -1, 2}
  Inhe vector<vector<int>> me copy karke return kar diya.

================================================================================
  COMPLEXITY:
  - Time:  O(N^2 * log(M)) jahan M set ka size hai (log factor set insertion ki wajah se)
  - Space: O(N) hashset ke liye + O(2 * unique_triplets) answer aur set ke liye
================================================================================
*/