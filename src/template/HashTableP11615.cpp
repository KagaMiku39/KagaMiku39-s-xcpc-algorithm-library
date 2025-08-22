#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

namespace FastIO {
    constexpr int maxsz = 1 << 21;

    char rbuf[maxsz], wbuf[maxsz], sta[20], *p1 = rbuf, *p2 = rbuf;

    int ps = 0, pw = 0;
    
    constexpr char sep = '\n';

    char getch() {
        return p1 == p2 && (p2 = (p1 = rbuf) + fread(rbuf, 1, maxsz, stdin), p1 == p2) ? EOF : *p1 ++;
    }

    template<typename T>
    void read(T &x) {
        int s = 1;
        char ch = getch();
        x = 0;
        while (!isdigit(ch)) {
            if (ch == '-') {
                s = -1;
            }
            ch = getch();
        }
        while (isdigit(ch)) {
            x = x * 10 + (ch - '0');
            ch = getch();
        }
        x *= s;
    }

    template<typename T, typename... Ts>
    void read(T &x, Ts &...oth) {
        read(x);
        if constexpr (sizeof...(oth)) {
            read(oth...);
        }
    }

    template<typename T>
    T input() {
        T x;
        read(x);
        return x;
    }

    void flush() {
        fwrite(wbuf, 1, pw, stdout);
        pw = 0;
    }

    template<typename T, typename... Ts>
    void write(T x, Ts... oth) {
        if (pw > maxsz - 20) flush();
        if (x < 0) {
            wbuf[pw ++] = '-';
            x = -x;
        }
        int tp = 0;
        do {
            sta[tp ++] = char('0' + x % 10);
            x /= 10;
        } while (x);
        while (tp --) {
            wbuf[pw ++] = sta[tp];
        }
        wbuf[pw ++] = sep;
        if constexpr (sizeof...(oth)) {
            write(oth...);
        }
    }

    void quit(int x) {
        flush();
        fflush(stdout);
        exit(x);
    }
}

using namespace FastIO;

// struct Hash {
//     static u64 rnd;

//     size_t operator () (const u64 &x) const{
//         return x ^ rnd;
//     }
// };

// u64 Hash::rnd{mt19937_64(chrono::steady_clock::now().time_since_epoch().count())()};

#include<ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

struct Hash {
    static u64 splitmix64(u64 x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    
    size_t operator()(u64 x) const {
        static const i64 rnd{chrono::steady_clock::now().time_since_epoch().count()};
        return splitmix64(x + rnd);
    }
};

int main() {
    int n = input<int>();

    u64 ans = 0;
    // unordered_map<u64, u64, Hash> ump;
    gp_hash_table<u64, u64, Hash> ump;
    for (int i = 1; i <= n; i ++) {
        u64 x = input<u64>(), y = input<u64>();
        ans += i * ump[x];
        ump[x] = y;        
    }

    write(ans);

    quit(0);
}