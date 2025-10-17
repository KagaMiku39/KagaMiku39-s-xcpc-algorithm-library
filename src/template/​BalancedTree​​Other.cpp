#include <bits/stdc++.h>

using namespace std;

// #include <bits/extc++.h>

// #include <ext/rope>

// using namespace __gnu_cxx;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // vector<int> vec;

    // rope<int> rop;

    tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> rbt;
    
    int tim = 0;
    
    while (n --) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            // vec.insert(lower_bound(begin(vec), end(vec), x), x);
            // rop.insert(lower_bound(begin(rop), end(rop), x) - begin(rop), x);
            rbt.insert({x, tim ++});
        }
        if (opt == 2) {
            // vec.erase(lower_bound(begin(vec), end(vec), x));
            // rop.erase(lower_bound(begin(rop), end(rop), x) - begin(rop), 1);
            auto it = rbt.lower_bound({x, 0});
            if (it != end(rbt) && it -> first == x) {
                rbt.erase(it);
            }
        }
        if (opt == 3) {
            // auto it = lower_bound(begin(vec), end(vec), x);
            // cout << distance(begin(vec), it) + 1 << '\n';
            // cout << lower_bound(begin(rop), end(rop), x) - begin(rop) + 1 << '\n';
            cout << rbt.order_of_key({x, 0}) + 1 << '\n';
        }
        if (opt == 4) {
            // cout << *next(begin(vec), x - 1) << '\n';
            // cout << rop[x - 1] << '\n';
            auto it = rbt.find_by_order(x - 1);
            cout << it -> first << '\n';
        }
        if (opt == 5) {
            // auto it = lower_bound(begin(vec), end(vec), x);
            // cout << *prev(it) << '\n';
            // cout << rop[lower_bound(begin(rop), end(rop), x) - begin(rop) - 1] << '\n';
            auto it = rbt.lower_bound({x, 0});
            cout << (-- it) -> first << '\n';
        }
        if (opt == 6) {
            // auto it = upper_bound(begin(vec), end(vec), x);
            // cout << *it << '\n';
            // cout << rop[upper_bound(begin(rop), end(rop), x) - begin(rop)] << '\n';
            auto it = rbt.upper_bound({x, tim});
            cout << it -> first << '\n';
        }
    }

    return 0;
}