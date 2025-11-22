#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    string s;
    cin >> s;

    char ch[]{'L', 'I', 'T'};

    int cnt[3]{};
    for (char &c: s) {
        for (int i = 0; i < 3; i ++) {
            cnt[i] += ch[i] == c;
        }
    }

    if (count(begin(s), end(s), 'L') == ssize(s) || count(begin(s), end(s), 'I') == ssize(s) || count(begin(s), end(s), 'T') == ssize(s)) {
        cout << "-1\n";
        return;
    }
    
    vector<int> ans;
    while (cnt[0] != cnt[1] || cnt[1] != cnt[2] || cnt[0] != cnt[2]) {
        if (cnt[0] > cnt[1]) {
            swap(cnt[0], cnt[1]);
            swap(ch[0], ch[1]);
        } 
        if (cnt[0] > cnt[2]) {
            swap(cnt[0], cnt[2]);
            swap(ch[0], ch[2]);
        }
        if (cnt[1] > cnt[2]) {
            swap(cnt[1], cnt[2]);
            swap(ch[1], ch[2]);
        }
        bool tag = false;
        for (int i = 0; i < ssize(s) - 1; i ++) {
            if ((s[i] == ch[1] && s[i + 1] == ch[2]) || (s[i] == ch[2] && s[i + 1] == ch[1])) {
                cnt[0] ++;
                tag = true;
                s.insert(i + 1, 1, ch[0]);
                ans.emplace_back(i + 1);
                break;
            }
        }
        if (!tag) {
            for (int i = 0; i < ssize(s) - 1; i ++) {
                if ((s[i] == ch[0] && s[i + 1] == ch[2]) || (s[i] == ch[2] && s[i + 1] == ch[0])) {
                    cnt[1] ++;
                    s.insert(i + 1, 1, ch[1]);
                    ans.emplace_back(i + 1);
                    break;
                }
            }
        }
    }

    cout << ssize(ans) << '\n';
    for (int &i: ans) {
        cout << i << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}