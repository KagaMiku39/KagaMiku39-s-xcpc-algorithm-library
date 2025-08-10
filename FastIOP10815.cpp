#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

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

    int input() {
        int x;
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
            sta[tp ++] = '0' + x % 10;
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

int main() {
    int n = input();

    i64 sum = 0;
    for (int i = 1; i <= n; i ++) {
        sum += input();
    }

    write(sum);

    quit(0);
}