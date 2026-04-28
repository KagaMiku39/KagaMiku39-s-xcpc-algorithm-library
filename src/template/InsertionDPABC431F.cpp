#include <bits/stdc++.h>

using namespace std;

using u32 = unsigned;
using u64 = unsigned long long; 

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

constexpr int maxn = 4e5 + 1, mod = 998244353;

int fac[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    fac[0] = 1;
    for (int i = 1; i < maxn; i ++) {
        fac[i] = (1ll * fac[i - 1] * i % mod);
    }
    
    auto comb = [&](int m, int n) -> Z {
        auto binpow = [&](int a, int b) {
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
        };
        auto inv = [&](int x) {
            return binpow(x, mod - 2);
        };
        if (n < 0 || n > m) {
            return 0;
        }
        return 1ll * fac[m] * inv(fac[n]) % mod * inv(fac[m - n]) % mod;
    };
    
    int n, d;
    cin >> n >> d;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    sort(next(begin(a)), end(a));

    vector<pair<int, int>> vec{{}};
    for (int i = 1; i <= n; i ++) {
        auto &[val, cnt] = vec.back();
        if (val == a[i]) {
            cnt ++;
        } else {
            vec.emplace_back(a[i], 1);
        }
    }

    Z sum = 0;
    vector<Z> dp(ssize(vec));
    dp[0] = 1;
    for (int i = 1, j = 1; i < ssize(vec); i ++) {
        auto &[val, cnt] = vec[i];
        while (j < i && vec[j].first + d < val) {
            sum -= vec[j].second;
            j ++;
        }
        dp[i] = comb(cnt + int(sum), int(sum)) * dp[i - 1];
        sum += cnt;
    }

    cout << dp.back() << '\n';

    return 0;
}