#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct Matrix {
    static constexpr int mod = 1e9 + 7;
    
    T mat[2][2]{};
    
    Matrix() {}

    Matrix(T a, T b, T c = T{}, T d = T{}) : mat{a, b, c, d} {}
    
    Matrix operator * (const Matrix &b) const {
        Matrix res;
        for (int i = 0; i < 2; i ++)
            for (int k = 0; k < 2; k ++) {
                T tmp = mat[i][k];
                for (int j = 0; j < 2; j ++) {
                    if constexpr (is_integral_v<T>) {
                        res.mat[i][j] = (res.mat[i][j] + 1ll * tmp * b.mat[k][j]) % mod;
                    } else {
                        res.mat[i][j] += tmp * b.mat[k][j];
                    }
                }
            }
        return res;
    }

    Matrix &operator *= (const Matrix &b) {
        return *this = *this * b; 
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
    
    cout << (Matrix{1, 1, 0, 0} * Matrix<int>::binpow(Matrix{0, 1, 1, 1}, n - 2)).mat[0][1] << '\n';

    return 0;
}