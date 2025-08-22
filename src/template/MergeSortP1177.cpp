#include <bits/stdc++.h>

using namespace std;

#define ssize(x) int(x.size())

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    vector<int> b(n + 1);
    
    auto mergesort = [&](auto &self, int lo, int ro) -> void {
        if (lo >= ro) {
            return;
        }
        int mid = (lo + ro) / 2;
        self(self, lo, mid);
        self(self, mid + 1, ro);
        int i = lo, j = mid + 1, k = lo;
        while (i <= mid && j <= ro) {
            if (a[i] <= a[j]) {
                b[k ++] = a[i ++];
            } else {
                b[k ++] = a[j ++];
            }
        }
        while (i <= mid) {
            b[k ++] = a[i ++];
        }
        while (j <= ro) {
            b[k ++] = a[j ++];
        }
        for (int p = lo; p <= ro; p ++) {
            a[p] = b[p];
        }
    };

    if (n > 0) {
        mergesort(mergesort, 1, n);
    }
    
    for (int i = 1; i <= n; i ++) {
        cout << a[i] << " \n"[i == n];
    }

    return 0;
}