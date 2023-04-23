#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 1600005;

int n, q, par[MAXN], dist[MAXN], c[MAXN];
vector<int> gph[MAXN];
vector<pi> edg;

void dfs(int x, int p){
    for(auto &y : gph[x]){
        if(y != p){
            par[y] = x;
            dfs(y, x);
        }
    }
}

void dfs2(int x){
    for(auto &y : gph[x]){
        if(y == par[x]) continue;
        edg.emplace_back(max(dist[x], dist[y]), y);
        dfs2(y);
        edg.emplace_back(max(dist[x], dist[y]), x);
    }
}

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        for(int i = x + 2; i < MAXN; i += i & -i) tree[i] += v;
    }
    int kth(int x){
        int pos = 0;
        for(int i = 20; i >= 0; i--){
            if(pos + (1<<i) < MAXN && tree[pos + (1<<i)] < x){
                pos += (1<<i);
                x -= tree[pos];
            }
        }
        return (pos + 1) - 2;
    }
}bit;

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        int k; cin >> k;
        gph[i].resize(k);
        for(auto &j : gph[i]) cin >> j;
    }
    dfs(1, -1);
    for(int i = 1; i <= n; i++){
        int nxt = gph[i][1 % sz(gph[i])];
        if(i > 1){
            rotate(gph[i].begin(), find(all(gph[i]), par[i]), gph[i].end());
            rotate(gph[i].begin(), gph[i].begin() + 1, gph[i].end());
        }
        c[i] = find(all(gph[i]), nxt) - gph[i].begin();
    }
    memset(dist, 0x3f, sizeof(dist));
    queue<int> que; que.push(1); dist[1] = 0;
    while(sz(que)){
        int x = que.front(); que.pop();
        for(int i = c[x]; i < sz(gph[x]); i++){
            if(dist[gph[x][i]] > dist[x]){
                dist[gph[x][i]] = dist[x];
                que.push(gph[x][i]);
            }
        }
        for(int i = 0; i < c[x]; i++){
            if(dist[gph[x][i]] > dist[x] + 1){
                dist[gph[x][i]] = dist[x] + 1;
                que.push(gph[x][i]);
            }
        }
    }
    dfs2(1);
    vector<int> ans(q);
    vector<pi> qry(q);
    for(int i = 0; i < q; i++){
        cin >> qry[i].first;
        qry[i].second = i;
    }
    sort(all(qry));
    vector<int> pos(sz(edg));
    iota(all(pos), 0);
    sort(all(pos), [&](int p, int q){
        return pi(edg[p].first, p) < pi(edg[q].first, q);
    });
    lint cur = 0;
    int ptr = 0, j = 0;
    for(int i = 0; i <= n; i++){
        while(ptr < sz(pos) && edg[pos[ptr]].first == i){
            bit.add(pos[ptr], +1);
            ptr++;
        }
        while(j < sz(qry) && qry[j].first <= cur + ptr){
            ans[qry[j].second] = edg[bit.kth(qry[j].first - cur)].second;
            j++;
        }
        cur += ptr;
    }
    while(j < sz(qry)){
        lint V = (qry[j].first - cur - 1) % sz(edg);
        ans[qry[j].second] = edg[V].second;
        j++;
    }
    for(auto &x : ans)cout << x << "\n";
}
