#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

struct Matrix {
    int n, mod;

    vector<vector<int>> mat;

    Matrix(int n, int mod) : n(n), mod(mod), mat(n + 1, vector<int>(n + 1)) {}

    int determinant() {
        int res = 1, tag = 1;
        for (int i = 1; i <= n; i ++) {
            for (int j = i + 1; j <= n; j ++) {
                while (mat[i][i]) {
                    int tmp = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n; k ++) {
                        mat[j][k] = (mat[j][k] - 1ll * tmp * mat[i][k] % mod + mod) % mod;
                    }
                    swap(mat[i], mat[j]);
                    tag = -tag;
                }
                swap(mat[i], mat[j]);
                tag = -tag;
            }
        }
        for (int i = 1; i <= n; i ++) {
            res = 1ll * res * mat[i][i] % mod;
        }
        res = 1ll * res * tag % mod;
        if (res < 0) {
            res += mod;
        }
        return res;
    }

    friend istream& operator>>(istream& is, Matrix& mat) {
        for (int i = 1; i <= mat.n; i ++) {
            for (int j = 1; j <= mat.n; j ++) {
                is >> mat.mat[i][j];
                mat.mat[i][j] %= mat.mod;
                if (mat.mat[i][j] < 0) {
                    mat.mat[i][j] += mat.mod;
                }
            }
        }
        return is;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, mod;
    cin >> n >> mod;

    Matrix mat(n, mod);
    cin >> mat;

    cout << mat.determinant() << "\n";

    return 0;
}