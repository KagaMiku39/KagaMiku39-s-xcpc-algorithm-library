#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

constexpr int logn = 20;
constexpr int N = 100005; 

struct PointDivideTree {
    int n_; 

    // === 状态变量 ===
    vector<vector<int>> adj;
    vector<int> val;
    vector<int> dep;
    vector<vector<int>> up;
    vector<long long> tr1[N], tr2[N]; 
    int fa[N]; 

    // === 构建辅助变量 ===
    vector<int> siz;
    vector<int> del;
    int sum, mxs, cen;

    // === 优化：预处理距离 ===
    // pdt_ancestors[x][i] = x 在点分树上的第 i 个祖先 u
    // pdt_dists_self[x][i]  = dist(x, u)
    // pdt_dists_parent[x][i]= dist(x, fa[u])
    vector<int> pdt_ancestors[N];
    vector<int> pdt_dists_self[N];
    vector<int> pdt_dists_parent[N];

    // === 内部辅助函数 (BIT) ===
    void bit_add(vector<long long> &tr, int pos, long long delta) {
        pos ++; 
        for (; pos < ssize(tr); pos += pos & -pos) {
            tr[pos] += delta;
        }
    }

    long long bit_query(const vector<long long> &tr, int pos) {
        pos ++;
        pos = min(pos, ssize(tr) - 1); 
        long long res = 0;
        for (; pos > 0; pos -= pos & -pos) {
            res += tr[pos];
        }
        return res;
    }

    // === 内部辅助函数 (LCA) ===
    void dfs_lca(int u, int p) {
        for (int i = 1; i <= logn; i ++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto v: adj[u]) {
            if (v == p) {
                continue;
            }
            up[v][0] = u;
            dep[v] = dep[u] + 1;
            dfs_lca(v, u);
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        for (int i = logn; ~i; i --) {
            if (dep[u] - (1 << i) >= dep[v]) {
                u = up[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = logn; ~i; i --) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * lca(u, v);
    }

    // === 内部辅助函数 (点分树构建) ===
    void getcen(int u, int p) {
        siz[u] = 1;
        int s = 0;
        for (auto &v : adj[u]) {
            if (v == p || del[v]) {
                continue;
            }
            getcen(v, u);
            siz[u] += siz[v];
            cmax(s, siz[v]);
        }
        cmax(s, sum - siz[u]);
        if (s < mxs) {
            mxs = s;
            cen = u;
        }
    };

    // 优化：DFS 遍历当前 'centroid' 所在连通块，预存距离
    void component_dfs(int v, int p, int centroid) {
        // v = 当前节点, p = v 在原树上的父亲
        // centroid = v 所在连通块的重心 (也是 v 在点分树上的一个祖先)
        
        // 存储 v 到 centroid 及其父亲的距离
        pdt_ancestors[v].push_back(centroid);
        pdt_dists_self[v].push_back(dist(v, centroid));
        pdt_dists_parent[v].push_back(fa[centroid] ? dist(v, fa[centroid]) : 0);

        for (auto &child : adj[v]) {
            if (child == p || del[child]) continue;
            component_dfs(child, v, centroid);
        }
    }


    void build_tree(int u, int p, int s_p) {
        sum = s_p;
        mxs = n_ + 1; 
        getcen(u, 0);
        u = cen;
        fa[u] = p;

        getcen(u, 0); 
        tr1[u].resize(siz[u] + 2, 0);
        if (p) {
            tr2[u].resize(s_p + 2, 0);
        }

        // *** 优化点 ***
        // 遍历 u 所在连通块的所有节点 v
        // 并为 v 存储 {u, dist(v, u), dist(v, fa[u])}
        component_dfs(u, 0, u); 

        del[u] = 1;
        for (auto &v : adj[u]) {
            if (del[v]) {
                continue;
            }
            int s_v = siz[v];
            if (s_v > siz[u]) { 
                s_v = s_p - siz[u];
            }
            build_tree(v, u, s_v);
        }
    };

    // === 构造函数 ===
    PointDivideTree(int n, const vector<vector<int>> &g, const vector<int> &initial_val) {
        n_ = n;
        
        adj = g;
        val = initial_val; 
        dep.resize(n_ + 1);
        up.resize(n_ + 1, vector<int>(logn + 1));
        siz.resize(n_ + 1);
        del.resize(n_ + 1);
        
        // 初始化距离向量 (虽然 N 是 100005，但用 C++ 数组特性，无需 clear)

        dep[1] = 1;
        dfs_lca(1, 0);

        // build_tree 会自动调用 component_dfs 来填充距离
        build_tree(1, 0, n_);

        // 填充初始值
        vector<int> temp_val = val;
        val.assign(n_ + 1, 0); 
        for (int i = 1; i <= n_; i ++) {
            this->update(i, temp_val[i]); // 调用 public update
        }
    }

    // === 公共接口：修改 (已优化) ===
    void update(int x, int y) {
        long long delta = (long long)y - val[x];
        val[x] = y;

        // 遍历 x 的所有点分树祖先 (已预处理)
        for (int i = 0; i < ssize(pdt_ancestors[x]); ++i) {
            int u = pdt_ancestors[x][i];
            int d_self = pdt_dists_self[x][i];   // O(1) 获取 dist(x, u)
            
            bit_add(tr1[u], d_self, delta);
            
            if (fa[u]) { // fa[u] != 0
                int d_parent = pdt_dists_parent[x][i]; // O(1) 获取 dist(x, fa[u])
                bit_add(tr2[u], d_parent, delta);
            }
        }
    }

    // === 公共接口：查询 (已优化) ===
    long long query(int x, int k) {
        long long ans = 0;
        
        // 遍历 x 的所有点分树祖先 (已预处理)
        // pdt_ancestors[x] 中, [0] 是最近的(叶)重心, [n-1] 是总根重心
        for (int i = 0; i < ssize(pdt_ancestors[x]); ++i) {
            int u = pdt_ancestors[x][i];
            int d = pdt_dists_self[x][i]; // O(1) 获取 dist(x, u)
            
            if (k >= d) {
                ans += bit_query(tr1[u], k - d);
                
                // 容斥：减去来自 x 所在子树(last) 对 u 的贡献
                // last = pdt_ancestors[x][i-1]
                // fa[last] = u
                if (i > 0) { 
                    int last = pdt_ancestors[x][i-1];
                    // 我们需要减去的距离是 dist(x, u)
                    // d = dist(x, u), 正好是 d
                    ans -= bit_query(tr2[last], k - d);
                }
            }
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> initial_val(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> initial_val[i];
    }

    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    PointDivideTree pdt(n, g, initial_val);

    long long last = 0;
    while (m --) {
        int op, x, yk;
        cin >> op >> x >> yk;
        
        x ^= last;
        yk ^= (int)last; 

        if (op == 0) {
            long long ans = pdt.query(x, yk);
            cout << ans << '\n';
            last = ans;
        } else {
            pdt.update(x, yk);
        }
    }

    return 0;
}