#include <bits/stdc++.h>

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long; 
using i128 = __int128; 

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
     
    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }
     
    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }
     
    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
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

constexpr int N = 1e5;

unordered_map<int, Z> fMu;

vector<int> minp, primes, phi, mu;
vector<i64> sphi;

void sieve(int n) {
    minp.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    sphi.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    primes.clear();
    phi[1] = 1;
    mu[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mu[i * p] = -mu[i];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        sphi[i] = sphi[i - 1] + phi[i];
        mu[i] += mu[i - 1];
    }
}

Z sumMu(int n) {
    if (n <= N) {
        return mu[n];
    }
    if (fMu.count(n)) {
        return fMu[n];
    }
    if (n == 0) {
        return 0;
    }
    Z ans = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * sumMu(n / l);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);



    return 0;
}