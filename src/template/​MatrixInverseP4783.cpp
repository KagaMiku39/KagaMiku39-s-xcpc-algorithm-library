#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct Matrix {
    static constexpr i64 mod = 1e9 + 7;
    
    int r, c;

    vector<vector<i64>> mat;

    Matrix(int r, int c) : r(r), c(c), mat(r + 1, vector<i64>(c + 1)) {}

    int binpow(int a, int b) {
        int res = 1 % mod;
        a %= mod;
        while (b) {
            if (b & 1) {
                res = 1ll * res * a % mod;
            }
            a = 1ll * a * a % mod;
            b /= 2;
        }
        return res;
    }

    int inv(int a) {
        return binpow(a, mod - 2);
    }

    bool guess() {
        for (int i = 1; i <= r; i ++) {
            int id = i;
            for (int j = i + 1; j <= r; j ++) {
                if (!mat[id][i]) {
                    id = j;
                }
            }
            if (!mat[id][i]) {
                return false;
            }
            swap(mat[i], mat[id]);
            int val = mat[i][i], vinv = inv(val);
            for (int j = c; j >= i; j --) {
                mat[i][j] = (1ll * mat[i][j] * vinv) % mod;
            }
            for (int j = 1; j <= r; j ++) {
                if (j != i) {
                    int fac = mat[j][i];
                    for (int k = c; k >= i; k --) {
                        mat[j][k] = (mat[j][k] - 1ll * mat[i][k] * fac % mod + mod) % mod;
                    }
                }
            }
        }
        return true;
    }

    friend istream &operator >> (istream &is, Matrix &mat) {
        for (int i = 1; i <= mat.r; i ++) {
            for (int j = 1; j <= mat.r; j ++) {
                is >> mat.mat[i][j];
            }
        }
        return is;
    }
    
    friend ostream &operator << (ostream &os, const Matrix &mat) {
        for (int i = 1; i <= mat.r; i ++) {
            for (int j = mat.r + 1; j <= mat.c; j ++) {
                os << mat.mat[i][j] << (j == mat.c ? "" : " ");
            }
            os << '\n';
        }
        return os;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Matrix mat(n, 2 * n); 
    cin >> mat;

    for (int i = 1; i <= n; i ++) {
        mat.mat[i][n + i] = 1; 
    }

    if (mat.guess()) {
        cout << mat;
    } else {
        cout << "No Solution\n";
    }

    return 0;
}