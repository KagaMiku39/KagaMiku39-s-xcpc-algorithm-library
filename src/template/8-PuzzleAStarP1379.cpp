#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    
    int gx[]{-1, 0, 0, 0, 1, 2, 2, 2, 1}, gy[]{-1, 0, 1, 2, 2, 2, 1, 0, 0}, 
        off[][2]{0, 1, 1, 0, 0, -1, -1, 0};
    auto f = [&](string &str) {
        int res = 0;
        for (int i = 0; i < 9; i ++) {
            if (str[i] != '0') {
                int tmp = str[i] - '0';
                res += abs(i / 3 - gx[tmp]) + abs(i % 3 - gy[tmp]);
            }
        }
        return res;
    };
    auto AStar = [&]() {
        unordered_map<string, int> dis;
        priority_queue<tuple<int, int, string>> pq;
        dis[s] = 0;
        pq.emplace(-f(s), 0, s);
        while (ssize(pq)) {
            auto [key, val, str] = pq.top();
            pq.pop();
            if (str == "123804765") {
                return dis[str];
            }
            int k = str.find('0'), r = k / 3, c = k % 3;
            for (int i = 0; i < 4; i ++) {
                int nr = r + off[i][0], nc = c + off[i][1];
                if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) {
                    continue;
                }
                string tmp = str;
                swap(tmp[k], tmp[nr * 3 + nc]);
                if (!dis.count(tmp)) {
                    dis[tmp] = dis[str] + 1;
                    pq.emplace(-(dis[tmp] + f(tmp)), -(dis[tmp]), tmp);
                }
            }
        }
        return -1;
    };

    cout << AStar() << '\n';

    return 0;
}