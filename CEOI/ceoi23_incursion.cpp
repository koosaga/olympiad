#include "incursion.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 50000;

vector<int> gph[MAXN];
int dist[MAXN], par[MAXN];
vector<int> dfn;
int sz[MAXN], msz[MAXN];

void gd(int x, int p = -1) {
    for (auto &y : gph[x]) {
        if (y == p)
            continue;
        par[y] = x;
        dist[y] = dist[x] + 1;
        gd(y, x);
    }
}

void kindahld(int x) {
    sz[x] = 1;
    for (auto &y : gph[x]) {
        gph[y].erase(find(all(gph[y]), x));
        kindahld(y);
        sz[x] += sz[y];
    }
    sort(all(gph[x]), [&](int p, int q) { return sz[p] > sz[q]; });
}

void dfs(int x, int p = -1) {
    dfn.push_back(x);
    sz[x] = 1, msz[x] = 0;
    for (auto &y : gph[x]) {
        if (y != p) {
            dfs(y, x);
            sz[x] += sz[y];
            msz[x] = max(msz[x], sz[y]);
        }
    }
}

vector<int> cents;

int get_center(int x) {
    dfn.clear();
    cents.clear();
    dfs(x);
    pi ret{int(1e9), -1};
    for (auto &x : dfn) {
        int w = max(sz(dfn) - sz[x], msz[x]);
        if (w * 2 <= sz(dfn)) {
            cents.push_back(x);
        }
    }
    sort(all(cents), [&](int a, int b) { return dist[a] < dist[b]; });
    return cents[0];
}

vector<int> mark(vector<pair<int, int>> F, int safe) {
    int n = sz(F) + 1;
    for (auto &[u, v] : F) {
        gph[u].push_back(v);
        gph[v].push_back(u);
    }
    gd(safe);
    int r = get_center(1);
    gd(r);
    vector<int> ans(n);
    for (int i = safe; i != r; i = par[i])
        ans[i - 1] = 1;
    ans[r - 1] = 1;
    return ans;
}

void locate(vector<pair<int, int>> F, int curr, int t) {
    int n = sz(F) + 1;
    for (int i = 0; i <= n; i++)
        gph[i].clear();
    for (auto &[u, v] : F) {
        gph[u].push_back(v);
        gph[v].push_back(u);
    }
    gd(curr);
    int r = get_center(1);
    // cout << "root " << r << endl;
    gd(r);
    kindahld(r);
    while (t == 0 && curr != r) {
        t = visit(par[curr]);
        curr = par[curr];
    }
    if (t == 0 && curr == r) {
        t = visit(cents[1]);
        curr = cents[1];
    }
    assert(t);
    while (sz(gph[curr])) {
        bool good = 0;
        for (int i = 0; i < sz(gph[curr]); i++) {
            t = visit(gph[curr][i]);
            if (t) {
                curr = gph[curr][i];
                good = 1;
                break;
            }
            t = visit(curr);
        }
        if (!good)
            break;
    }
}