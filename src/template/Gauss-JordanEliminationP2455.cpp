#include <bits/stdc++.h>

using namespace std;

struct Matrix {
	static constexpr double eps = 1e-4;

	int r, c;

	vector<vector<double>> mat;

	Matrix(int r, int c) : r(r), c(c), mat(r + 1, vector<double>(c + 1)) {}

	int gauss() {
		for (int i = 1; i <= r; i ++) {
			int id = i;
			for (int j = 1; j <= r; j ++) {
				if (j < i && abs(mat[j][j]) >= eps) {
					continue;
				}
				if (abs(mat[id][i]) < abs(mat[j][i])) {
					id = j;
				}
			}
			swap(mat[i], mat[id]);
			double val = mat[i][i];
			if (abs(val) < eps) {
				continue;
			}
			for (int j = c; j >= i; j --) {
				mat[i][j] /= val;
			}
			for (int j = 1; j <= r; j ++) {
				if (j != i) {
					for (int k = c; k >= i; k --) {
						mat[j][k] -= mat[i][k] * mat[j][i];
					}
				}
			}
		}

		int tag = 1;
		for (int i = 1; i <= r; i ++) {
			if (abs(mat[i][i]) < eps && abs(mat[i][c]) > eps) {
				return -1;
			}
			if (abs(mat[i][i]) < eps) {
				tag = 0;
			}
		}
		return tag;
	}

	friend istream &operator >> (istream &is, Matrix &mat) {
		for (int i = 1; i <= mat.r; i ++) {
			for (int j = 1; j <= mat.c; j ++) {
				is >> mat.mat[i][j];
			}
		}
		return is;
	}

	friend ostream &operator << (ostream &os, const Matrix &mat) {
		for (int i = 1; i <= mat.r; i ++) {
			os << 'x' << i << '=' << mat.mat[i][mat.c] << '\n';
		}
		return os;
	}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Matrix mat(n, n + 1);
    cin >> mat;

    int res = mat.gauss();

    if (!~res) {
        cout << "-1\n";
    } else if (!res) {
        cout << "0\n";
    } else {
        cout << fixed << setprecision(2) << mat;
    }

    return 0;
}