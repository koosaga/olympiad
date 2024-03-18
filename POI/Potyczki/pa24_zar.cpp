#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 400005;
const int mod = 1e9 + 7;

lint ipow(lint x, lint p) {
    lint ret = 1, piv = x;
    while (p) {
        if (p & 1)
            ret = ret * piv % mod;
        piv = piv * piv % mod;
        p >>= 1;
    }
    return ret;
}

int n;
int str[MAXN];
lint fact[MAXN], invf[MAXN];
lint bino(int x, int y) { return fact[x] * (invf[y] * invf[x - y] % mod) % mod; }

bool bipartite;
int vis[MAXN], E;
vector<int> dfn;
vector<int> gph[MAXN];

void dfs(int x, int c) {
    if (vis[x]) {
        if (vis[x] != c)
            bipartite = 0;
        return;
    }
    dfn.push_back(x);
    vis[x] = c;
    E += sz(gph[x]);
    for (auto &i : gph[x])
        dfs(i, 3 - c);
}

void trans() {
    for (auto &i : dfn) {
        if (vis[i] == 2)
            str[i] ^= 1;
    }
}

int main() {
    fact[0] = invf[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % mod;
        invf[i] = ipow(fact[i], mod - 2);
    }
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &str[i]);
    for (int i = 0; i < m; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        s--, e--;
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    lint X = 1;
    for (int i = 0; i < n; i++) {
        if (vis[i])
            continue;
        dfn.clear();
        bipartite = 1;
        E = 0;
        dfs(i, 1);
        if (bipartite) {
            trans();
            int K = 0;
            for (auto &i : dfn)
                if (str[i] == 1)
                    K++;
            X = X * bino(sz(dfn), K) % mod;
            trans();
        } else {
            X = X * ipow(2, sz(dfn) - 1) % mod;
        }
    }
    printf("%lld\n", X);
}