#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        for(int i = x; i < MAXN; i+=i&-i) tree[i] += v;
    }
    int query(int x){
        int ret = 0;
        for(int i = x; i; i -= i&-i) ret += tree[i];
        return ret;
    }
}bit;

struct node{
    int s, e, idx, dx;
};

vector<node> qr[MAXN];

struct graph{
    vector<int> gph[MAXN];
    int din[MAXN], dout[MAXN];
    int piv;
    void add_edge(int s, int e){
        gph[s].push_back(e);
    }
    void dfs(int x = 1){
        din[x] = ++piv;
        for(auto &y : gph[x]) dfs(y);
        dout[x] = piv;
    }
}g[2];

int ans[MAXN], ret[MAXN];

int main(){
    int n; scanf("%d",&n);
    for(int i = 0; i < 2; i++){
        for(int j = 2; j <= n; j++){
            int x; scanf("%d",&x);
            g[i].add_edge(x, j);
        }
        g[i].dfs();
    }
    for(int i = 1; i <= n; i++){
        ans[g[0].din[i]] = g[1].din[i];
        qr[g[0].dout[i]].push_back({g[1].din[i], g[1].dout[i], i, +1});
        qr[g[0].din[i] - 1].push_back({g[1].din[i], g[1].dout[i], i, -1});
    }
    for(int i = 1; i <= n; i++){
        bit.add(ans[i], 1);
        for(auto &j : qr[i]){
            ret[j.idx] += j.dx * (bit.query(j.e) - bit.query(j.s - 1));
        }
    }
    for(int i = 1; i <= n; i++) printf("%d ", ret[i]-1);
}
