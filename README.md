<div style="height: 100vh; display: flex; justify-content: center; align-items: center;">
  <div style="text-align: center; color: #9a8fc1;">
    <div style="font-size: 3.5rem; font-weight: 700; margin: 0 0 0.5rem 0; display: inline-block;">
      XCPC 算法模板
    </div>
    <div style="font-size: 1.2rem; color: #b6abd8; font-weight: 500; text-align: right; display: inline-block; width: 100%;">
      by KagaMiku39
    </div>
  </div>
</div>
<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #FFD1D9; margin: 0; padding: 0;">
    数据结构
  </div>
</div>
<div style="page-break-after: always;"></div>


<div style="page-break-after: always;"></div>

# P1886 滑动窗口 /【模板】单调队列

## 题目描述

有一个长为 $n$ 的序列 $a$，以及一个大小为 $k$ 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。

例如，对于序列 $[1,3,-1,-3,5,3,6,7]$ 以及 $k = 3$，有如下过程：

$$\def\arraystretch{1.2}
\begin{array}{|c|c|c|}\hline
\textsf{窗口位置} & \textsf{最小值} & \textsf{最大值} \\ \hline
\verb![1   3  -1] -3   5   3   6   7 ! & -1 & 3 \\ \hline
\verb! 1  [3  -1  -3]  5   3   6   7 ! & -3 & 3 \\ \hline
\verb! 1   3 [-1  -3   5]  3   6   7 ! & -3 & 5 \\ \hline
\verb! 1   3  -1 [-3   5   3]  6   7 ! & -3 & 5 \\ \hline
\verb! 1   3  -1  -3  [5   3   6]  7 ! & 3 & 6 \\ \hline
\verb! 1   3  -1  -3   5  [3   6   7]! & 3 & 7 \\ \hline
\end{array}
$$

## 输入格式

输入一共有两行，第一行有两个正整数 $n,k$。
第二行 $n$ 个整数，表示序列 $a$

## 输出格式

输出共两行，第一行为每次窗口滑动的最小值   
第二行为每次窗口滑动的最大值

## 输入输出样例 #1

### 输入 #1

```
8 3
1 3 -1 -3 5 3 6 7
```

### 输出 #1

```
-1 -3 -3 -3 3 3
3 3 5 5 6 7
```

## 说明/提示

【数据范围】    
对于 $50\%$ 的数据，$1 \le n \le 10^5$；  
对于 $100\%$ 的数据，$1\le k \le n \le 10^6$，$a_i \in [-2^{31},2^{31})$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    deque<int> dq[2];
    vector<vector<int>> ans(2, vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j < 2; j ++) {
            if (ssize(dq[j]) && dq[j].front() + k - 1 < i) {
                dq[j].pop_front();
            }
            int l = j ? -1 : 1;
            while (ssize(dq[j]) && a[dq[j].back()] * l >= a[i] * l) {
                dq[j].pop_back();
            }
            dq[j].emplace_back(i);
            ans[j][i] = a[dq[j].front()];
        }
    }

    for (int i = 0; i < 2; i ++) {
        for (int j = k; j <= n; j ++) {
            cout << ans[i][j] << " \n"[j == n];
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P5788 【模板】单调栈

## 题目背景

模板题，无背景。  

2019.12.12 更新数据，放宽时限，现在不再卡常了。

## 题目描述

给出项数为 $n$ 的整数数列 $a_{1 \dots n}$。

定义函数 $f(i)$ 代表数列中第 $i$ 个元素之后第一个大于 $a_i$ 的元素的**下标**，即 $f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}$。若不存在，则 $f(i)=0$。

试求出 $f(1\dots n)$。

## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数 $a_{1\dots n}$。

## 输出格式

一行 $n$ 个整数表示 $f(1), f(2), \dots, f(n)$ 的值。

## 输入输出样例 #1

### 输入 #1

```
5
1 4 2 3 5
```

### 输出 #1

```
2 5 4 5 0
```

## 说明/提示

【数据规模与约定】

对于 $30\%$ 的数据，$n\leq 100$；

对于 $60\%$ 的数据，$n\leq 5 \times 10^3$ ；

对于 $100\%$ 的数据，$1 \le n\leq 3\times 10^6$，$1\leq a_i\leq 10^9$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n + 2, INT_MAX);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    vector<int> vec, ans(n + 1);
    for (int i = 1; i <= n + 1; i ++) {
        while (ssize(vec) && a[vec.back()] < a[i]) {
            ans[vec.back()] = i % (n + 1);
            vec.pop_back();
        }
        vec.emplace_back(i);
    }

    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << " \n"[i == n];
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P1168 中位数

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A$，对于前奇数项求中位数。

## 输入格式

第一行一个正整数 $N$。

第二行 $N$ 个正整数 $A_{1\dots N}$。

## 输出格式

共 $\lfloor \frac{N + 1}2\rfloor$ 行，第 $i$ 行为 $A_{1\dots 2i - 1}$ 的中位数。

## 输入输出样例 #1

### 输入 #1

```
7
1 3 5 7 9 11 6
```

### 输出 #1

```
1
3
5
6
```

## 输入输出样例 #2

### 输入 #2

```
7
3 1 5 9 8 7 6
```

### 输出 #2

```
3
3
5
6
```

## 说明/提示

对于 $20\%$ 的数据，$N \le 100$；

对于 $40\%$ 的数据，$N \le 3000$；

对于 $100\%$ 的数据，$1 \le N ≤ 100000$，$0 \le A_i \le 10^9$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int mid = 0;
    priority_queue<int> le;
    priority_queue<int, vector<int>, greater<int>> gr;
    for (int i = 1; i <= n; i ++) {
        if (i > 1) {
            if (a[i] > mid) {
                gr.emplace(a[i]);
            }else {
                le.emplace(a[i]);
            }
        }else {
            mid = a[i];
        }
        if (abs(ssize(le) - ssize(gr)) > 1) {
            if (ssize(le) > ssize(gr)) {
                gr.emplace(mid);
                mid = le.top();
                le.pop();
            }else {
                le.emplace(mid);
                mid = gr.top();
                gr.pop();
            }
        }
        if (i & 1) {
            cout << mid << '\n';
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# U104609 【模板】树的重心

## 题目背景

模板题，无背景

## 题目描述

给定一个 $n$ 个节点的**无根树**，节点按照 $1 \sim n$ 编号，并且无**自环**和**重边**。求它的重心，如果有多个重心，按照编号从小到大的顺序依次输出。

## 输入格式

第一行：一个整数 $n$，含义见题目描述。  
接下来 $n-1$ 行，每行两个整数 $u,v$，代表 $u$ 和 $v$ 之间有一条连边。

## 输出格式

仅一行，按照编号从小到大输出重心。

## 输入输出样例 #1

### 输入 #1

```
6
1 2
2 3
2 5
3 4
3 6
```

### 输出 #1

```
2 3
```

## 输入输出样例 #2

### 输入 #2

```
8
1 2
2 3
3 4
4 5
5 6
6 7
7 8
```

### 输出 #2

```
4 5
```

## 说明/提示

对于 $100\%$ 的数据，$2 \leq n \leq 5 \times 10^4$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> cen, sz(n + 1, 1);
    auto dfs = [&](auto &self, int u, int p) -> void {
        int wei = 0;
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            sz[u] += sz[v];
            cmax(wei, sz[v]);
        }
        cmax(wei, n - sz[u]);
        if (wei <= n / 2) {
            cen.emplace_back(u);
        }
    };
    dfs(dfs, 1, 0);

    sort(begin(cen), end(cen));

    for (int &i: cen) {
        cout << i << " \n"[i == cen.back()];
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P1364 医院设置

## 题目描述

设有一棵二叉树，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kawht13x.png)

其中，圈中的数字表示结点中居民的人口。圈边上数字表示结点编号，现在要求在某个结点上建立一个医院，使所有居民所走的路程之和为最小，同时约定，相邻接点之间的距离为 $1$。如上图中，若医院建在 $1$ 处，则距离和 $=4+12+2\times20+2\times40=136$；若医院建在 $3$ 处，则距离和 $=4\times2+13+20+40=81$。

## 输入格式

第一行一个整数 $n$，表示树的结点数。

接下来的 $n$ 行每行描述了一个结点的状况，包含三个整数 $w, u, v$，其中 $w$ 为居民人口数，$u$ 为左链接（为 $0$ 表示无链接），$v$ 为右链接（为 $0$ 表示无链接）。

## 输出格式

一个整数，表示最小距离和。

## 输入输出样例 #1

### 输入 #1

```
5						
13 2 3
4 0 0
12 4 5
20 0 0
40 0 0
```

### 输出 #1

```
81
```

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 100$，$0 \leq u, v \leq n$，$1 \leq w \leq 10^5$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> w(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i ++) {
        int u, v;
        cin >> w[i] >> u >> v;
        auto addedge = [&](int x) {
            if (!x) return;
            adj[i].emplace_back(x);
            adj[x].emplace_back(i); 
        };
        addedge(u);
        addedge(v);
    }

    vector<int> sz = w, dep(n + 1), dp(n + 1);
    auto dfs1 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            dep[v] = dep[u] + 1; 
            self(self, v, u);
            sz[u] += sz[v];
        }
        dp[1] += dep[u] * w[u];
    };
    dfs1(dfs1, 1, 0);
    
    int ans = INT_MAX;
    auto dfs2 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            dp[v] = dp[u] + sz[1] - 2 * sz[v];
            self(self, v, u);
        }
        cmin(ans, dp[u]);
    };
    dfs2(dfs2, 1, 0);
    
    cout << ans << '\n';

    return 0;
}
```

<div style="page-break-after: always;"></div>

# U81904 【模板】树的直径

## 题目背景

模板题，无背景

## 题目描述

给定一棵树，树中每条边都有一个权值，

树中两点之间的距离定义为连接两点的路径边权之和。

树中最远的两个节点之间的距离被称为树的直径，连接这两点的路径被称为树的最长链。

现在让你求出树的最长链的距离

## 输入格式

给定一棵无根树

第一行为一个正整数$n$,表示这颗树有$n$个节点

接下来的$n-1$行,每行三个正整数$u,v,w$，表示$u,v$（$u,v<=n$）有一条权值为$w$的边相连

数据保证没有重边或自环

## 输出格式

输入仅一行，表示树的最长链的距离

## 输入输出样例 #1

### 输入 #1

```
6
1 2 1
1 3 2
2 4 3
4 5 1
3 6 2
```

### 输出 #1

```
9
```

## 说明/提示

对于$10%$的数据 $n<=10$

对于$30%$的数据 $n<=1000$

对于$50%$的数据 $n<=10000$

对于$70%$的数据 $n<=100000$  边权均为正整数

对于$100%$的数据 $n<=500000$ 边权可能为负

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    i64 ans = 0;
    vector<i64> dp(n + 1);
    auto dfs = [&](auto &self, int u, int p) -> void {
        for (auto &[v, w]: adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            cmax(ans, dp[u] + dp[v] + w);
            cmax(dp[u], dp[v] + w);
        }
    };
    dfs(dfs, 1, 0);

    cout << ans << '\n';
    
    return 0;
}
```

<div style="page-break-after: always;"></div>

# P3379 【模板】最近公共祖先（LCA）

## 题目描述

如题，给定一棵有根多叉树，请求出指定两个点直接最近的公共祖先。

## 输入格式

第一行包含三个正整数 $N,M,S$，分别表示树的结点个数、询问的个数和树根结点的序号。

接下来 $N-1$ 行每行包含两个正整数 $x, y$，表示 $x$ 结点和 $y$ 结点之间有一条直接连接的边（数据保证可以构成树）。

接下来 $M$ 行每行包含两个正整数 $a, b$，表示询问 $a$ 结点和 $b$ 结点的最近公共祖先。

## 输出格式

输出包含 $M$ 行，每行包含一个正整数，依次为每一个询问的结果。

## 输入输出样例 #1

### 输入 #1

```
5 5 4
3 1
2 4
5 1
1 4
2 4
3 2
3 5
1 2
4 5
```

### 输出 #1

```
4
4
1
4
4
```

## 说明/提示

对于 $30\%$ 的数据，$N\leq 10$，$M\leq 10$。

对于 $70\%$ 的数据，$N\leq 10000$，$M\leq 10000$。

对于 $100\%$ 的数据，$1 \leq N,M\leq 5\times10^5$，$1 \leq x, y,a ,b \leq N$，**不保证** $a \neq b$。


样例说明：

该树结构如下：

 ![](https://cdn.luogu.com.cn/upload/pic/2282.png) 

第一次询问：$2, 4$ 的最近公共祖先，故为 $4$。

第二次询问：$3, 2$ 的最近公共祖先，故为 $4$。

第三次询问：$3, 5$ 的最近公共祖先，故为 $1$。

第四次询问：$1, 2$ 的最近公共祖先，故为 $4$。

第五次询问：$4, 5$ 的最近公共祖先，故为 $4$。

故输出依次为 $4, 4, 1, 4, 4$。

2021/10/4 数据更新 @fstqwq：应要求加了两组数据卡掉了暴力跳。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    
    vector<int> p(n + 1), sz(n + 1, 1), dep(n + 1), ch(n + 1);
    sz[0] = 0, dep[s] = 1;
    auto dfs1 = [&](auto &self, int u, int pa) -> void {
        p[u] = pa;
        for (int &v: adj[u]) {
            if (v == pa) {
                continue;
            }
            dep[v] = dep[u] + 1;
            self(self, v, u);
            sz[u] += sz[v];
            if (sz[ch[u]] < sz[v]) {
                ch[u] = v;
            }
        }
    };
    dfs1(dfs1, s, 0);

    vector<int> tp(n + 1);
    auto dfs2 = [&](auto &self, int u, int top) -> void {
        tp[u] = top;
        if (!ch[u]) {
            return;
        }
        self(self, ch[u], top);
        for (int &v: adj[u]) {
            if (v == p[u] || v == ch[u]) {
                continue;
            }
            self(self, v, v);
        }
    };
    dfs2(dfs2, s, s);

    auto lca = [&](int a, int b) {
        while (tp[a] != tp[b]) {
            if (dep[tp[a]] < dep[tp[b]]) {
                swap(a, b);
            }
            a = p[tp[a]];
        }
        return dep[a] < dep[b] ? a : b;
    };
    for (int i = 1; i <= m; i ++) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P1364 医院设置

## 题目描述

设有一棵二叉树，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kawht13x.png)

其中，圈中的数字表示结点中居民的人口。圈边上数字表示结点编号，现在要求在某个结点上建立一个医院，使所有居民所走的路程之和为最小，同时约定，相邻接点之间的距离为 $1$。如上图中，若医院建在 $1$ 处，则距离和 $=4+12+2\times20+2\times40=136$；若医院建在 $3$ 处，则距离和 $=4\times2+13+20+40=81$。

## 输入格式

第一行一个整数 $n$，表示树的结点数。

接下来的 $n$ 行每行描述了一个结点的状况，包含三个整数 $w, u, v$，其中 $w$ 为居民人口数，$u$ 为左链接（为 $0$ 表示无链接），$v$ 为右链接（为 $0$ 表示无链接）。

## 输出格式

一个整数，表示最小距离和。

## 输入输出样例 #1

### 输入 #1

```
5						
13 2 3
4 0 0
12 4 5
20 0 0
40 0 0
```

### 输出 #1

```
81
```

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 100$，$0 \leq u, v \leq n$，$1 \leq w \leq 10^5$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> w(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i ++) {
        int u, v;
        cin >> w[i] >> u >> v;
        auto addedge = [&](int x) {
            if (!x) return;
            adj[i].emplace_back(x);
            adj[x].emplace_back(i); 
        };
        addedge(u);
        addedge(v);
    }

    vector<int> sz = w, dep(n + 1), dp(n + 1);
    auto dfs1 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            dep[v] = dep[u] + 1; 
            self(self, v, u);
            sz[u] += sz[v];
        }
        dp[1] += dep[u] * w[u];
    };
    dfs1(dfs1, 1, 0);
    
    int ans = INT_MAX;
    auto dfs2 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            dp[v] = dp[u] + sz[1] - 2 * sz[v];
            self(self, v, u);
        }
        cmin(ans, dp[u]);
    };
    dfs2(dfs2, 1, 0);
    
    cout << ans << '\n';

    return 0;
}
```



<div style="page-break-after: always;"></div>

# P3372 【模板】线段树 1

## 题目描述

如题，已知一个数列 $\{a_i\}$，你需要进行下面两种操作：

1. 将某区间每一个数加上 $k$。
2. 求出某区间每一个数的和。

## 输入格式

第一行包含两个整数 $n, m$，分别表示该数列数字的个数和操作的总个数。

第二行包含 $n$ 个用空格分隔的整数 $a_i$，其中第 $i$ 个数字表示数列第 $i$ 项的初始值。

接下来 $m$ 行每行包含 $3$ 或 $4$ 个整数，表示一个操作，具体如下：

1. `1 x y k`：将区间 $[x, y]$ 内每个数加上 $k$。
2. `2 x y`：输出区间 $[x, y]$ 内每个数的和。

## 输出格式

输出包含若干行整数，即为所有操作 2 的结果。

## 输入输出样例 #1

### 输入 #1

```
5 5
1 5 4 2 3
2 2 4
1 2 3 2
2 3 4
1 1 5 1
2 1 4
```

### 输出 #1

```
11
8
20
```

## 说明/提示

对于 $15\%$ 的数据：$n \le 8$，$m \le 10$。  
对于 $35\%$ 的数据：$n \le {10}^3$，$m \le {10}^4$。    
对于 $100\%$ 的数据：$1 \le n, m \le {10}^5$，$a_i,k$ 为正数，且任意时刻数列的和不超过 $2\times 10^{18}$。

**【样例解释】**

![](https://cdn.luogu.com.cn/upload/pic/2251.png)

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define lc 2 * cur
#define rc 2 * cur + 1

template<typename T>
struct SegmentTree{
    vector<T> vec; 

    struct Node{
        T val, tag;
    };
    vector<Node> st;

    SegmentTree(int n, vector<T> vec) : vec(vec), st(4 * (n + 1)) {
        build(1, 1, n);
    }

    void pushup(int cur) {
        st[cur].val = st[lc].val + st[rc].val; 
    }

    void build(int cur, int s, int t) {
        if (s == t) {
            st[cur].val = vec[s];
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }

    void pushdown(int cur, int s, int t, int mid) {
        if (!st[cur].tag) {
            return; 
        }
        st[lc].val += (mid - s + 1) * st[cur].tag;
        st[rc].val += (t - mid) * st[cur].tag;
        st[lc].tag += st[cur].tag;
        st[rc].tag += st[cur].tag;
        st[cur].tag = 0;
    }

    void add(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            st[cur].val += (t - s + 1) * val;
            st[cur].tag += val;
            return; 
        }
        int mid = (s + t) / 2; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            add(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            add(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
    }

    T query(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return st[cur].val;
        }
        int mid = (s + t) / 2;
        T sum = 0; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            sum += query(lc, s, mid, lo, ro);
        }
        if (ro > mid) {
            sum += query(rc, mid + 1, t, lo, ro);
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<i64> a(n + 1);
    
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    SegmentTree st(n, a);
    
    while (m --) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            i64 k;
            cin >> k;
            st.add(1, 1, n, x, y, k);
        }else {
            cout << st.query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>

# P3373 【模板】线段树 2

## 题目描述

如题，已知一个数列，你需要进行下面三种操作：

- 将某区间每一个数乘上 $x$；
- 将某区间每一个数加上 $x$；
- 求出某区间每一个数的和。

## 输入格式

第一行包含三个整数 $n,q,m$，分别表示该数列数字的个数、操作的总个数和模数。

第二行包含 $n$ 个用空格分隔的整数，其中第 $i$ 个数字表示数列第 $i$ 项的初始值。

接下来 $q$ 行每行包含若干个整数，表示一个操作，具体如下：

操作 $1$： 格式：`1 x y k`  含义：将区间 $[x,y]$ 内每个数乘上 $k$。

操作 $2$： 格式：`2 x y k`  含义：将区间 $[x,y]$ 内每个数加上 $k$。

操作 $3$： 格式：`3 x y`  含义：输出区间 $[x,y]$ 内每个数的和对 $m$ 取模所得的结果。

## 输出格式

输出包含若干行整数，即为所有操作 $3$ 的结果。

## 输入输出样例 #1

### 输入 #1

```
5 5 38
1 5 4 2 3
2 1 4 1
3 2 5
1 2 4 2
2 3 5 5
3 1 4
```

### 输出 #1

```
17
2
```

## 说明/提示

【数据范围】

对于 $30\%$ 的数据：$n \le 8$，$q \le 10$。  
对于 $70\%$ 的数据：$n \le 10^3 $，$q \le 10^4$。  
对于 $100\%$ 的数据：$1 \le n \le 10^5$，$1 \le q \le 10^5,1\le k\le 10^4$。

除样例外，$m = 571373$。

（数据已经过加强 ^\_^）

样例说明：

 ![](https://cdn.luogu.com.cn/upload/pic/2255.png) 

故输出应为 $17$、$2$（$40 \bmod 38 = 2$）。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

#define lc 2 * cur
#define rc 2 * cur + 1

template<typename T>
struct SegmentTree{
    vector<T> vec; 
    
    struct Node{
        T val;
        
        array<T, 2> tag;
        
        Node() : tag{0, 1} {}
    };
    vector<Node> st;
    
    int mod;
    
    SegmentTree(int n, vector<T> &vec, int mod) : vec(vec), st(4 * (n + 1)), mod(mod) {
        build(1, 1, n);
    }

    void pushup(int cur) {
        st[cur].val = (1ll * st[lc].val + st[rc].val) % mod;
    }

    void build(int cur, int s, int t) {
        if (s == t) {
            st[cur].val = vec[s];
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }

    void pushdown(int cur, int s, int t, int mid) {
        if (!st[cur].tag[0] && st[cur].tag[1] == 1) {
            return; 
        }
        st[lc].val = (1ll * st[lc].val * st[cur].tag[1] + 1ll * (mid - s + 1) * st[cur].tag[0]) % mod;
        st[rc].val = (1ll * st[rc].val * st[cur].tag[1] + 1ll * (t - mid) * st[cur].tag[0]) % mod;
        st[lc].tag[0] = (1ll * st[lc].tag[0] * st[cur].tag[1] + st[cur].tag[0]) % mod;
        st[lc].tag[1] = 1ll * st[lc].tag[1] * st[cur].tag[1] % mod;
        st[rc].tag[0] = (1ll * st[rc].tag[0] * st[cur].tag[1] + st[cur].tag[0]) % mod;
        st[rc].tag[1] = 1ll * st[rc].tag[1] * st[cur].tag[1] % mod;
        st[cur].tag = {0, 1};
    }

    void add(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            st[cur].val = (st[cur].val + 1ll * (t - s + 1) * val) % mod;
            st[cur].tag[0] = (1ll * st[cur].tag[0] + val) % mod;
            return; 
        }
        int mid = (s + t) / 2; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            add(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            add(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
    }

    void mul(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            st[cur].val = 1ll * st[cur].val * val % mod;
            st[cur].tag[0] = 1ll * st[cur].tag[0] * val % mod;
            st[cur].tag[1] = 1ll * st[cur].tag[1] * val % mod;
            return; 
        }
        int mid = (s + t) / 2; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            mul(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            mul(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
    }

    T query(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return st[cur].val;
        }
        int mid = (s + t) / 2;
        T sum = 0; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            sum = (sum + query(lc, s, mid, lo, ro)) % mod;
        }
        if (ro > mid) {
            sum = (sum + query(rc, mid + 1, t, lo, ro)) % mod;
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, m;
    cin >> n >> q >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    SegmentTree<int> st(n, vec, m);

    while (q --) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            int k;
            cin >> k;
            st.mul(1, 1, n, x, y, k);
        }
        if (opt == 2) {
            int k;
            cin >> k;
            st.add(1, 1, n, x, y, k);
        }
        if (opt == 3) {
            cout << st.query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>

# P3834 【模板】可持久化线段树 2

## 题目背景

这是个非常经典的可持久化权值线段树入门题——静态区间第 $k$ 小。

**数据已经过加强，请使用可持久化权值线段树。同时请注意常数优化**。

## 题目描述

如题，给定 $n$ 个整数构成的序列 $a$，将对于指定的闭区间 $[l, r]$ 查询其区间内的第 $k$ 小值。

## 输入格式

第一行包含两个整数，分别表示序列的长度 $n$ 和查询的个数 $m$。  
第二行包含 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个元素 $a_i$。   
接下来 $m$ 行每行包含三个整数 $ l, r, k$ , 表示查询区间 $[l, r]$ 内的第 $k$ 小值。

## 输出格式

对于每次询问，输出一行一个整数表示答案。

## 输入输出样例 #1

### 输入 #1

```
5 5
25957 6405 15770 26287 26465 
2 2 1
3 4 1
4 5 1
1 2 2
4 4 1
```

### 输出 #1

```
6405
15770
26287
25957
26287
```

## 说明/提示

### 样例 1 解释

$n=5$，数列长度为 $5$，数列从第一项开始依次为$\{25957, 6405, 15770, 26287, 26465\}$。

- 第一次查询为 $[2, 2]$ 区间内的第一小值，即为 $6405$。
- 第二次查询为 $[3, 4]$ 区间内的第一小值，即为 $15770$。
- 第三次查询为 $[4, 5]$ 区间内的第一小值，即为 $26287$。
- 第四次查询为 $[1, 2]$ 区间内的第二小值，即为 $25957$。
- 第五次查询为 $[4, 4]$ 区间内的第一小值，即为 $26287$。


### 数据规模与约定

- 对于 $20\%$ 的数据，满足 $1 \leq n,m \leq 10$。
- 对于 $50\%$ 的数据，满足 $1 \leq n,m \leq 10^3$。
- 对于 $80\%$ 的数据，满足 $1 \leq n,m \leq 10^5$。
- 对于 $100\%$ 的数据，满足 $1 \leq n,m \leq 2\times 10^5$，$0\le a_i \leq 10^9$，$1 \leq l \leq r \leq n$，$1 \leq k \leq r - l + 1$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define lc(x) hjt[x].ch[0]
#define rc(x) hjt[x].ch[1]

struct PersistentSegmentTree{
    int idx{};
    
    vector<int> rt;
    
    struct Node{
        int cnt;
        
        array<int, 2> ch;
    };
    vector<Node> hjt;
    
    PersistentSegmentTree() {
        rt.emplace_back();
        hjt.emplace_back();
    }
    
    void append(int val) {
        rt.emplace_back(insert(rt.back(), 0, 1e9, val));
    }

    void pushup(int cur) {
        hjt[cur].cnt = hjt[lc(cur)].cnt + hjt[rc(cur)].cnt; 
    }
    
    int insert(int last, int s, int t, int val) {
        int now = ++ idx;
        hjt.emplace_back(hjt[last]);
        if (s == t) {
            hjt[now].cnt ++;
            return now; 
        }
        int mid = s + (t - s) / 2;
        if (val > mid) {
            rc(now) = insert(rc(last), mid + 1, t, val); 
        }else {
            lc(now) = insert(lc(last), s, mid, val);
        }
        pushup(now);
        return now;
    }

    int query(int ro, int lo, int rk) {
        return query(rt[ro], rt[lo], 0, 1e9, rk);
    }

    int query(int ro, int lo, int s, int t, int rk) {
        if (s == t) {
            return s;
        }
        int mid = s + (t - s) / 2, cnt = hjt[lc(ro)].cnt - hjt[lc(lo)].cnt;
        if (rk > cnt) {
            return query(rc(ro), rc(lo), mid + 1, t, rk - cnt);
        }else {
            return query(lc(ro), lc(lo), s, mid, rk);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    PersistentSegmentTree hjt;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        hjt.append(a[i]);
    }   
     
    while (m --) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << hjt.query(r, l - 1, k) << '\n';
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P3374 【模板】树状数组 1

## 题目描述

如题，已知一个数列，你需要进行下面两种操作：

- 将某一个数加上 $x$

- 求出某区间每一个数的和

## 输入格式

第一行包含两个正整数 $n,m$，分别表示该数列数字的个数和操作的总个数。   

第二行包含 $n$ 个用空格分隔的整数，其中第 $i$ 个数字表示数列第 $i$ 项的初始值。

接下来 $m$ 行每行包含 $3$ 个整数，表示一个操作，具体如下：

- `1 x k`  含义：将第 $x$ 个数加上 $k$

- `2 x y`  含义：输出区间 $[x,y]$ 内每个数的和

## 输出格式

输出包含若干行整数，即为所有操作 $2$ 的结果。

## 输入输出样例 #1

### 输入 #1

```
5 5
1 5 4 2 3
1 1 3
2 2 5
1 3 -1
1 4 2
2 1 4
```

### 输出 #1

```
14
16
```

## 说明/提示

【数据范围】

对于 $30\%$ 的数据，$1 \le n \le 8$，$1\le m \le 10$；   
对于 $70\%$ 的数据，$1\le n,m \le 10^4$；   
对于 $100\%$ 的数据，$1\le n,m \le 5\times 10^5$。

数据保证对于任意时刻，$a$ 的任意子区间（包括长度为 $1$ 和 $n$ 的子区间）和均在 $[-2^{31}, 2^{31})$ 范围内。


样例说明：

 ![](https://cdn.luogu.com.cn/upload/pic/2256.png) 

故输出结果14、16

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

struct FenwickTree{
    int n;

    vector<int> bit;

    FenwickTree(int n, vector<int> &vec) : n(n), bit(n + 1) {
        for (int i = 1; i <= n; i ++) {
            add(i, vec[i]);
        }
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, int val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += lowbit(pos);
        }
    }
    
    int query(int pos, int res = 0) {
        while (pos) {
            res += bit[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    FenwickTree bit(n, vec);
    
    while (m --) {
        int opt, x;
        cin >> opt >> x;
        if (opt - 1) {
            int y;
            cin >> y;
            cout << bit.query(y) - bit.query(x - 1) << '\n';
        }else {
            int k;
            cin >> k;
            bit.add(x, k);
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P3368 【模板】树状数组 2

## 题目描述

如题，已知一个数列，你需要进行下面两种操作：

1. 将某区间每一个数加上 $x$；

2. 求出某一个数的值。

## 输入格式

第一行包含两个整数 $N$、$M$，分别表示该数列数字的个数和操作的总个数。

第二行包含 $N$ 个用空格分隔的整数，其中第 $i$ 个数字表示数列第 $i $ 项的初始值。

接下来 $M$ 行每行包含 $2$ 或 $4$个整数，表示一个操作，具体如下：

操作 $1$： 格式：`1 x y k` 含义：将区间 $[x,y]$ 内每个数加上 $k$；

操作 $2$： 格式：`2 x` 含义：输出第 $x$ 个数的值。

## 输出格式

输出包含若干行整数，即为所有操作 $2$ 的结果。

## 输入输出样例 #1

### 输入 #1

```
5 5
1 5 4 2 3
1 2 4 2
2 3
1 1 5 -1
1 3 5 7
2 4
```

### 输出 #1

```
6
10
```

## 说明/提示

#### 样例 1 解释：

 ![](https://cdn.luogu.com.cn/upload/pic/2258.png) 

故输出结果为 6、10。

---

#### 数据规模与约定

对于 $30\%$ 的数据：$N\le8$，$M\le10$；

对于 $70\%$ 的数据：$N\le 10000$，$M\le10000$；

对于 $100\%$ 的数据：$1 \leq N, M\le 500000$，$1 \leq x, y \leq n$，保证任意时刻序列中任意元素的绝对值都不大于 $2^{30}$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

struct FenwickTree{
    int n;

    vector<int> bit;

    FenwickTree(int n, vector<int> &vec) : n(n), bit(n + 1) {
        for (int i = 1; i <= n; i ++) {
            add(i, vec[i]), add(i + 1, -vec[i]);
        }
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, int val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += lowbit(pos);
        }
    }
    
    int query(int pos, int res = 0) {
        while (pos) {
            res += bit[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }
    
    FenwickTree bit(n, vec);
    
    while (m --) {
        int opt, x;
        cin >> opt >> x;
        if (opt - 1) {
            cout << bit.query(x) << '\n';
        }else {
            int y, k;
            cin >> y >> k;
            bit.add(x, k), bit.add(y + 1, -k);
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P3367 【模板】并查集

## 题目背景

**本题数据范围已经更新到 $1\le N\le 2\times 10^5$，$1\le M\le 10^6$。**

## 题目描述

如题，现在有一个并查集，你需要完成合并和查询操作。

## 输入格式

第一行包含两个整数 $N,M$ ,表示共有 $N$ 个元素和 $M$ 个操作。

接下来 $M$ 行，每行包含三个整数 $Z_i,X_i,Y_i$ 。

当 $Z_i=1$ 时，将 $X_i$ 与 $Y_i$ 所在的集合合并。

当 $Z_i=2$ 时，输出 $X_i$ 与 $Y_i$ 是否在同一集合内，是的输出 
 `Y` ；否则输出 `N` 。

## 输出格式

对于每一个 $Z_i=2$ 的操作，都有一行输出，每行包含一个大写字母，为 `Y` 或者 `N` 。

## 输入输出样例 #1

### 输入 #1

```
4 7
2 1 2
1 1 2
2 1 2
1 3 4
2 1 4
1 2 3
2 1 4
```

### 输出 #1

```
N
Y
N
Y
```

## 说明/提示

对于 $15\%$ 的数据，$N \le 10$，$M \le 20$。

对于 $35\%$ 的数据，$N \le 100$，$M \le 10^3$。

对于 $50\%$ 的数据，$1\le N \le 10^4$，$1\le M \le 2\times 10^5$。

对于 $100\%$ 的数据，$1\le N\le 2\times 10^5$，$1\le M\le 10^6$，$1 \le X_i, Y_i \le N$，$Z_i \in \{ 1, 2 \}$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

struct DisjointSetUnion{
    vector<int> p, rk;

    DisjointSetUnion(int n) : p(n + 1), rk(n + 1) {
        iota(begin(p), end(p), 0);
    }

    int find(int x) {
        while (x != p[x]) {
            x = p[x] = p[p[x]];
        }
        return x;
    }

    void merge(int a, int b) {
        int pa[2]{find(a), find(b)};
        if (pa[0] == pa[1]) {
            return;
        }        
        if (rk[pa[0]] > rk[pa[1]]) {
            swap(pa[0], pa[1]);
        }
        p[pa[0]] = pa[1];
        rk[pa[1]] += rk[pa[0]] == rk[pa[1]];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DisjointSetUnion dsu(n);
    
    while (m --) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z - 1) {
            cout << (dsu.find(x) == dsu.find(y) ? "Y\n" : "N\n");
        }else {
            dsu.merge(x, y);
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P1494 [国家集训队] 小 Z 的袜子

## 题目描述

upd on 2020.6.10 ：更新了时限。

作为一个生活散漫的人，小 Z 每天早上都要耗费很久从一堆五颜六色的袜子中找出一双来穿。终于有一天，小 Z 再也无法忍受这恼人的找袜子过程，于是他决定听天由命……

具体来说，小 Z 把这 $N$ 只袜子从 $1$ 到 $N$ 编号，然后从编号 $L$ 到 $R$ 的袜子中随机选出两只来穿。尽管小 Z 并不在意两只袜子是不是完整的一双，他却很在意袜子的颜色，毕竟穿两只不同色的袜子会很尴尬。

你的任务便是告诉小 Z，他有多大的概率抽到两只颜色相同的袜子。当然，小 Z 希望这个概率尽量高，所以他可能会询问多个 $(L,R)$ 以方便自己选择。

**然而数据中有 $L=R$ 的情况，请特判这种情况，输出`0/1`。**

## 输入格式

输入文件第一行包含两个正整数 $N$ 和 $M$。$N$ 为袜子的数量，$M$ 为小 Z 所提的询问的数量。接下来一行包含 $N$ 个正整数 $C_i$，其中 $C_i$ 表示第 $i$ 只袜子的颜色，相同的颜色用相同的数字表示。再接下来 $M$ 行，每行两个正整数 $L, R$ 表示一个询问。

## 输出格式

包含 $M$ 行，对于每个询问在一行中输出分数 $A/B$ 表示从该询问的区间 $[L,R]$ 中随机抽出两只袜子颜色相同的概率。若该概率为 $0$ 则输出 `0/1`，否则输出的 $A/B$ 必须为最简分数。（详见样例）

## 输入输出样例 #1

### 输入 #1

```
6 4
1 2 3 3 3 2
2 6
1 3
3 5
1 6
```

### 输出 #1

```
2/5
0/1
1/1
4/15
```

## 说明/提示

$30\%$ 的数据中，$N,M\leq 5000$；

$60\%$ 的数据中，$N,M \leq 25000$；

$100\%$ 的数据中，$N,M \leq 50000$，$1 \leq L \leq R \leq N$，$C_i \leq N$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }

    int sq = sqrt(m), sz = 1.5 * (n + sq - 1) / sq;
    vector<tuple<int, int, int, int>> queries;
    for (int i = 1; i <= m; i ++) {
        int l, r;
        cin >> l >> r;
        queries.emplace_back(1 + l / sz, r, l, i);
    }

    sort(begin(queries), end(queries), [&](const auto &a, const auto &b) {
        return get<0>(a) & 1 
            ? tie(get<0>(a), get<1>(a)) < tie(get<0>(b), get<1>(b)) 
            : tie(get<0>(a), get<1>(b)) < tie(get<0>(b), get<1>(a));
    });

    int lo = 1, ro = 0;
    i64 res = 0;
    vector<int> cnt(n + 1);
    vector<string> ans(n + 1);
    auto add = [&](int pos) {
        res += 2 * cnt[c[pos]];
        cnt[c[pos]] ++;
    };
    auto del = [&](int pos) {
        cnt[c[pos]] --;
        res -= 2 * cnt[c[pos]];
    };
    for (auto &[_, r, l, id]: queries) {
        while (lo > l) {
            lo --;
            add(lo);
        }
        while (ro < r) {
            ro ++;
            add(ro);
        }
        while (lo < l) {
            del(lo);
            lo ++;
        }
        while (ro > r) {
            del(ro);
            ro --;
        }
        i64 g = gcd(res, 1ll * (ro - lo + 1) * (ro - lo));
        ans[id] = lo != ro ? to_string(res / g) + '/' + to_string(1ll * (ro - lo + 1) * (ro - lo) / g) : "0/1";
    }

    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

# P3865 【模板】ST 表 && RMQ 问题

## 题目背景

这是一道 ST 表经典题——静态区间最大值

**请注意最大数据时限只有 0.8s，数据强度不低，请务必保证你的每次查询复杂度为 $O(1)$。若使用更高时间复杂度算法不保证能通过。**

如果您认为您的代码时间复杂度正确但是 TLE，可以尝试使用快速读入：

```cpp
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
```

函数返回值为读入的第一个整数。

**快速读入作用仅为加快读入，并非强制使用。**

## 题目描述

给定一个长度为 $N$ 的数列，和 $ M $ 次询问，求出每一次询问的区间内数字的最大值。

## 输入格式

第一行包含两个整数 $N,M$，分别表示数列的长度和询问的个数。

第二行包含 $N$ 个整数（记为 $a_i$），依次表示数列的第 $i$ 项。

接下来 $M$ 行，每行包含两个整数 $l_i,r_i$，表示查询的区间为 $[l_i,r_i]$。

## 输出格式

输出包含 $M$ 行，每行一个整数，依次表示每一次询问的结果。

## 输入输出样例 #1

### 输入 #1

```
8 8
9 3 1 7 5 6 0 8
1 6
1 5
2 7
2 6
1 8
4 8
3 7
1 8
```

### 输出 #1

```
9
9
7
7
9
8
7
9
```

## 说明/提示

对于 $30\%$ 的数据，满足 $1\le N,M\le 10$。

对于 $70\%$ 的数据，满足 $1\le N,M\le {10}^5$。

对于 $100\%$ 的数据，满足 $1\le N\le {10}^5$，$1\le M\le 2\times{10}^6$，$a_i\in[0,{10}^9]$，$1\le l_i\le r_i\le N$。

<div style="page-break-after: always;"></div>

```c++
#include <bits/stdc++.h>

using namespace std;

template<typename T, typename F>
struct SparseTable{
    int lay;
    vector<vector<T>> st;
    F op;

    SparseTable(int n, vector<T> vec, F op) : lay(bceil(n)), st(lay + 1), op(op) {
        st[0] = move(vec);
        for (int i = 1, j = 1; i <= lay; i ++, j <<= 1) {
            st[i] = st[i - 1];
            for (int k = 1; k + 2 * j - 1 <= n; k ++) {
                st[i][k] = op(st[i - 1][k], st[i - 1][k + j]);
            }
        }
    }
    
    int highbit(int x) {
        for (const int &i: {1, 2, 4, 8, 16}) {
            x |= x >> i;
        }
        return x >> 1 ^ x;
    }

    int bceil(int x) {
        int h = highbit(x); 
        return bitset<32>((h << (x != h)) - 1ul).count();
    }

    int query(int lo, int ro) {
        int len = ro - lo + 1, h = highbit(len);
        return op(st[bceil(h)][lo], st[bceil(h)][ro - h + 1]);
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    SparseTable st(n, a, [&](int a, int b) {
        return max(a, b);
    });

    while (m --) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #8FE0DA; margin: 0; padding: 0;">
    数学
  </div>
</div>
<div style="page-break-after: always;"></div>


<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #E2D0E0; margin: 0; padding: 0;">
    字符串
  </div>
</div>
<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #a3d8c6; margin: 0; padding: 0;">
    图论
  </div>
</div>
<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #a8d8ea; margin: 0; padding: 0;">
    计算几何
  </div>
</div>
<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #FAE3C6; margin: 0; padding: 0;">
    其他算法
  </div>
</div>
<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>

<div style="display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; text-align: center;">
  <div style="font-size: 4rem; font-weight: 900; color: #B3E6FF; margin: 0; padding: 0;">
    杂项
  </div>
</div>
<div style="page-break-after: always;"></div>

<div style="page-break-after: always;"></div>