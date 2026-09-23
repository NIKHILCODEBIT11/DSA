#include <iostream>
using namespace std;

void pascals_triangle_row(int row, int total_rows) {
    // 1. Center-align karne ke liye leading spaces print karo
    for (int s = 0; s < total_rows - row; s++) {
        cout << " ";
    }

    // 2. Row ke elements calculate aur print karo
    int n = row - 1;
    long long ans = 1;
    cout << ans << " ";
    
    for (int i = 0; i < n; i++) {
        ans = ans * (n - i);
        ans = ans / (i + 1);
        cout << ans << " ";
    }
    cout << "\n";
}

void pascals_triangle(int total_rows) {
    for (int i = 1; i <= total_rows; i++) {
        pascals_triangle_row(i, total_rows);
    }
}

int main() {
    int rows = 5;
    cout << "Pascal's Triangle (" << rows << " rows):\n\n";
    pascals_triangle(rows);
    return 0;
}