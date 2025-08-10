#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct Matrix {
    static constexpr int mod = 1e9 + 7;
    
    int mat[2][2]{};
    
    Matrix operator * (Matrix mat) const {
        Matrix res;
        for (int i = 0; i < 2; i ++)
            for (int k = 0; k < 2; k ++) {
                int tmp = this -> mat[i][k];
                for (int j = 0; j < 2; j ++) {
                    res.mat[i][j] = (res.mat[i][j] + 1ll * tmp * mat.mat[k][j]) % mod;
                }
            }
        return res;
    }

    Matrix &operator *= (Matrix mat) {
        return *this = *this * mat; 
    }

    static Matrix binpow(Matrix a, i64 b) {
        Matrix res{1, 0, 0, 1};
        while (b) {
            if (b & 1) {
                res *= a;
            }
            a *= a;
            b /= 2;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    i64 n;
    cin >> n;
    
    if (n < 3) {
        cout << "1\n";
        return 0;
    }
    
    cout << (Matrix{1, 1, 0, 0} * Matrix::binpow(Matrix{0, 1, 1, 1}, n - 2)).mat[0][1] << '\n';

    return 0;
}