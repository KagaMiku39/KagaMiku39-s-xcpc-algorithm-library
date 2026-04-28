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

constexpr int maxa = 1e7 + 1;

int lpf[maxa];

bitset<maxa> ispri;

vector<int> pri;

template<typename T>
constexpr T power(T a, u64 b) {
    T res {1};
    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}
 
template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}
 
template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}
 
template<typename U, U P>
requires std::unsigned_integral<U>
struct ModIntBase {
public:
    constexpr ModIntBase() : x {0} {}
     
    constexpr ModIntBase(bool x_) : x {x_ ? 1U : 0U} {}
    
    template<typename T>
    requires std::integral<T>
    constexpr ModIntBase(T x_) : x {norm(x_ % T {P})} {}
     
    constexpr static U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
     
    constexpr U val() const {
        return x;
    }
     
    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm(P - x);
        return res;
    }
     
    constexpr ModIntBase inv() const {
        return power(*this, P - 2);
    }
     
    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rhs.val());
        return *this;
    }
     
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
     
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
     
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }
     
    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
     
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
     
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
     
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }
     
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }

    friend std::istream &operator>>(std::istream &is, ModIntBase &a) {
        using T = std::conditional_t<std::is_same_v<U, u32>, i64, u64>;
        T v;
        is >> v;
        a = ModIntBase(v);
        return is;
    }
     
    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }
     
    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }
     
    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }

    friend constexpr bool operator>(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() > rhs.val();
    }

    friend constexpr bool operator<=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() <= rhs.val();
    }

    friend constexpr bool operator>=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() >= rhs.val();
    }

    constexpr operator int() const {
        return val();
    }

    constexpr operator bool() const { 
        return bool(val());
    }
    
    template <typename T>
    constexpr T operator%(T m) const {
        return val() % m;
    }

private:
    U x;
};
 
template<u32 P>
using ModInt = ModIntBase<u32, P>;
 
template<u64 P>
using ModInt64 = ModIntBase<u64, P>;
 
constexpr u32 P = 998244353;
using Z = ModInt<P>;

void solve() {   
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    map<int, int> mx1, mx2;
    map<pair<int, int>, int> cnt;
    for (int i = 1; i <= n; i ++) {
        int tmp = a[i];
        while (tmp > 1) {
            int l = lpf[tmp];
            while (tmp % l == 0) {
                cnt[{i, l}] ++;
                tmp /= l;
            }
            if (mx1[l] <= cnt[{i, l}]) {
                mx2[l] = mx1[l];
                cmax(mx1[l], cnt[{i, l}]);
            } else {
                cmax(mx2[l], cnt[{i, l}]);
            }
        }
    }

    Z ans{1};
    for (auto &[a, b]: mx1) {
        ans *= power(a, b);
    }

    for (int i = 1; i <= n; i ++) {
        int tmp = a[i];
        Z res = ans;
        while (tmp > 1) {
            int l = lpf[tmp];
            if (cnt[{i, l}] == mx1[l]) {
                res /= power(l, mx1[l]);
                res *= power(l, mx2[l]);
            }
            tmp /= power(l, cnt[{i, l}]);
        }
        cout << res << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ispri.set();
    ispri[0] = ispri[1] = false;
    for (int i = 2; i < maxa; i ++) {
        if (ispri[i]) {
            lpf[i] = i;
            pri.emplace_back(i);
        }
        for (int &j: pri) {
            if (1ll * i * j > maxa) {
                break;
            }
            ispri[i * j] = false;
            lpf[i * j] = j;
            if (i % j == 0) {
                break;
            }
        }
    }
    
    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}