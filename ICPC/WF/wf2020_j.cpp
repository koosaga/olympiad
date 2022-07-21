#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, par[MAXN], pae[MAXN], dep[MAXN];
int rdep[MAXN];
vector<pi> gph[MAXN];
vector<int> dfn;

pi far[MAXN], ufar[MAXN];

void dfs(int x, int p) {
    dfn.push_back(x);
    far[x] = pi(0, x);
    for(auto &i : gph[x]) {
        if(i.second == p) continue;
        par[i.second] = x;
        pae[i.second] = i.first;
        dep[i.second] = dep[x] + 1;
        rdep[i.second] = rdep[x] + i.first;
        dfs(i.second, x);
        far[x] = max(far[x], pi(far[i.second].first + i.first, far[i.second].second));
    }
}

struct tuple1 {
    int first, second, third;
    bool operator<(const tuple1 &t)const {
        if(first != t.first) return first < t.first;
        if(second != t.second) return second < t.second;
        return third < t.third;
    }
};

struct diam {
    int st, ed; int len;
    bool operator<(const diam &d)const {
        return len < d.len;
    }
}dp[MAXN], pp[MAXN];

vector<tuple1> flist[MAXN];
vector<pair<diam, int>> dlist[MAXN];

diam make_diam(pi a, pi b) {
    diam Fuck;
    Fuck.st = a.second;
    Fuck.ed = b.second;
    Fuck.len = a.first + b.first;
    return Fuck;
}

int main() {
    scanf("%d", &n);
    int sum = 0, tmp = 0;
    for(int i = 0; i<n - 1; i++) {
        int s, e, x;
        scanf("%d %d %d", &s, &e, &x);
        sum += 2 * x;
        gph[s].push_back(pi(x, e));
        gph[e].push_back(pi(x, s));
    }
    dfs(1, -1);
    for(int i = 1; i <= n; i++) {
        for(auto &j : gph[i]) {
            if(j.second == par[i]) continue;
            tuple1 Fuck;
            Fuck.first = far[j.second].first + j.first;
            Fuck.second = far[j.second].second;
            Fuck.third = j.second;

            flist[i].push_back(Fuck);
        }
        flist[i].push_back({ 0, i, -1 });
        flist[i].push_back({ 0, i, -1 });
        sort(flist[i].rbegin(), flist[i].rend());
        int cur = 0;
        for(int j = 0; j < flist[i].size() && j < 4; j++){
            cur += flist[i][j].first;
        }
        tmp = max(tmp, cur);
        if(flist[i].size() > 3) flist[i].resize(3);
    }
    for(int i = 1; i<dfn.size(); i++) {
        int x = dfn[i];
        ufar[x] = pi(0, par[x]);
        for(auto &j : flist[par[x]]) {
            if(j.third == x) continue;
            pi t = pi(j.first, j.second);
            ufar[x] = max(ufar[x], t);
        }
        if(par[x] != 1) {
            pi t = pi(ufar[par[x]].first + pae[par[x]], ufar[par[x]].second);
            ufar[x] = max(ufar[x], t);
        }
        int cur = ufar[x].first + pae[x];
        for(int j = 0; j < flist[x].size() && j < 3; j++){
            cur += flist[x][j].first;
        }
        tmp = max(tmp, cur);
    }
    for(int i = dfn.size() - 1; i >= 0; i--) {
        int x = dfn[i];
        pi v1(flist[x][0].first, flist[x][0].second);
        pi v2(flist[x][1].first, flist[x][1].second);
        dp[x] = make_diam(v1, v2);
        for(auto &j : gph[x]) {
            if(j.second == par[x]) continue;
            dp[x] = max(dp[x], dp[j.second]);
            dlist[x].push_back(make_pair(dp[j.second], j.second));
        }
        sort(dlist[x].rbegin(), dlist[x].rend());
        if(dlist[x].size() > 2) dlist[x].resize(2);
    }
    for(int i = 1; i<dfn.size(); i++) {
        int x = dfn[i];
        vector<pi> diam_cand;
        for(auto &j : flist[par[x]]) {
            if(j.third == x) continue;
            diam_cand.push_back(pi(j.first, j.second));
        }
        if(par[x] != 1) {
            pi t = pi(ufar[par[x]].first + pae[par[x]], ufar[par[x]].second);
            diam_cand.push_back(t);
        }
        diam_cand.push_back(pi(0, par[x]));
        diam_cand.push_back(pi(0, par[x]));
        sort(diam_cand.rbegin(), diam_cand.rend());
        pp[x] = make_diam(diam_cand[0], diam_cand[1]);
        if(par[x] != 1) pp[x] = max(pp[x], pp[par[x]]);
        for(auto &j : dlist[par[x]]) if(j.second != x) pp[x] = max(pp[x], j.first);
    }
    for(int i = 2; i <= n; i++) {
        auto up = pp[i], dn = dp[i];
        tmp = max(tmp, up.len + dn.len);
    }
    cout << sum -tmp << endl;
}
