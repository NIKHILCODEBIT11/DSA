#include <iostream>
#include <set>

using namespace std;

void erase(set<int>& a);

void output(set<int>& a) {
    for (auto it : a) {
        cout << it << " ";
    }
    cout << endl;
}

void erase(set<int>& a) {
    int range[2];
    cout << "Enter the range of elements to remove: " << endl;
    cin >> range[0] >> range[1];

    // Regular iterators
    auto it_start = a.lower_bound(range[0]);  // Points to the first element >= range[0]
    auto it_end = a.upper_bound(range[1]);    // Points to the first element > range[1]

    // Check if the range exists
    if (it_start == a.end() || it_end == a.end()) {
        cout << "One or both of the values are not present in the set." << endl;
        return;
    }

    // Erase the range [it_start, it_end)
    a.erase(it_start, it_end);
    cout << "Updated Set: ";
    output(a);  // Display the set after erasure
}

void input(int a) {
    cout << "Inputting elements into the set:" << endl;
    set<int> s;
    for (int i = 0; i < a; i++) {
        int a2;
        cout << "Enter element " << i + 1 << ": ";
        cin >> a2;
        s.insert(a2);
    }
    cout << "Original Set: ";
    output(s);  // Display the original set

    // Perform the erase operation
    erase(s);
}

int main() {
    input(5);  // Input 5 elements into the set
    return 0;
}
