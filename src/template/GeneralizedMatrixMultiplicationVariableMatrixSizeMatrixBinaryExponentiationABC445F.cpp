#include <bits/stdc++.h>

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long; 

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

template<typename T>
struct Matrix {
    int n;
    
    vector<vector<T>> mat;

    Matrix(int n, T val) : n(n), mat(n, vector<T>(n, val)) {}
    
    Matrix operator * (const Matrix &b) const {
        Matrix res(n, numeric_limits<T>::max());
        for (int i = 0; i < n; i ++) {
            for (int k = 0; k < n; k ++) {
                    T tmp = mat[i][k];
                    if (tmp == numeric_limits<T>::max()) {
                        continue;
                    }
                    for (int j = 0; j < n; j ++) {
                        cmin(res.mat[i][j], tmp + b.mat[k][j]);
                    }
            }
        }
        return res;
    }
        
    Matrix &operator *= (const Matrix &b) {
        return *this = *this * b; 
    }
    
    static Matrix iden(int n) {
        Matrix res(n, numeric_limits<T>::max());
        for (int i = 0; i < n; i ++) {
            res.mat[i][i] = 0;
        }
        return res;
    }

    static Matrix binpow(Matrix a, i64 b) {
        Matrix res{iden(a.n)};
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
    
    int n, k;
    cin >> n >> k;

    Matrix<i64> c(n, 0);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            cin >> c.mat[i][j];
        }
    }

    Matrix mat{Matrix<i64>::binpow(c, k)};

    for (int i = 0; i < n; i ++) {
        cout << mat.mat[i][i] << '\n';
    }

    return 0;
}