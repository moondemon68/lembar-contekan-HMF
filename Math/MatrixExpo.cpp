/*
    This is an implementation of Matrix Exponentiation made in C++.
    In this case, the base cases are f(0) = 0, f(1) = 1, f(2) = 2.
    The reccurence relation is f(n) = f(n-1) + 2f(n-2) + 3f(n-3).
    This code calculates f(n) % 1000000007.
*/

#include <bits/stdc++.h>
#define LL long long
#define MOD 1000000007

using namespace std;

const LL sz = 3; // size of matrix

// A utility function to multiply two matrices, result of multiplication stored in a.
void multiply(LL a[sz][sz], LL b[sz][sz]) {
    LL mul[sz][sz];
    for (LL i = 0; i < sz; i++) {
        for (LL j = 0; j < sz; j++) {
            mul[i][j] = 0;
            for (LL k = 0; k < sz; k++) {
                mul[i][j] += (a[i][k]%MOD)*(b[k][j]%MOD);
                mul[i][j] %= MOD;
            }
        }
    }
    for (LL i=0; i<sz; i++) {
        for (LL j=0; j<sz; j++) {
            a[i][j] = mul[i][j];
        }
    }
}

// Function to compute F raise to power of n.
void power(LL F[sz][sz], LL n) {
    LL res[sz][sz] = {{1,0,0},{0,1,0},{0,0,1}};
    while (n) {
        if (n & 1) {
            multiply(res,F);
        }
        n = n >> 1;
        multiply(F, F);
    }
    for (int i=0;i<sz;i++) {
        for (int j=0;j<sz;j++) {
            F[i][j] = res[i][j];
        }
    }
}

// Driver code
int main() {
    LL n;
    cin >> n;
    LL base[sz] = {0,1,2};
    for (int i=0;i<=n;i++) {    // print f(i) up to n
        LL mat[sz][sz] = {{0,1,0},{0,0,1},{3,2,1}};
        power(mat, i);
        LL ans = 0;
        for (int j=0;j<sz;j++) ans += ((mat[0][j]%MOD) * (base[j]%MOD)) % MOD;
        cout << ans << endl;
    }
    return 0;
} 