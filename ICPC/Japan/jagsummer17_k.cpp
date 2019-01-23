#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int MAXT = 270000;

int n, q, a[MAXN];
int low[MAXN];
multiset<int> ycnt[MAXN];

struct edg{ int p, q, s, e; };

lint ipow(int x, int p){
    lint ret = 1, piv  = x;
    while(p){
        if(p & 1) ret = ret * piv % mod;
        piv = piv * piv % mod;
        p >>= 1;
    }
    return ret;
}

struct seg{
    lint tree[MAXT];
    int lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree, tree + MAXT, 1);
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = tree[2*x] * tree[2*x+1] % mod;
        }
    }
}seg;

void upload(int x){
    while(x > 1){
        int c = low[x];
        int v = 0;
        while(x % c == 0){
            x /= c;
            v++;
        }
        ycnt[c].insert(v);
        seg.upd(c, ipow(c, *ycnt[c].rbegin()));
    }
}

void download(int x){
    while(x > 1){
        int c = low[x];
        int v = 0;
        while(x % c == 0){
            x /= c;
            v++;
        }
        ycnt[c].erase(ycnt[c].find(v));
        int nxt = (ycnt[c].empty() ? 0 : *ycnt[c].rbegin());
        seg.upd(c, ipow(c, nxt));
    }
}

struct disj{
    int pa[MAXN], rk[MAXN], sz[MAXN];
    void init(int n){
        fill(sz, sz + n + 1, 1);
        iota(pa, pa + n + 1, 0);
    }
    int find(int x){
        return pa[x] == x ? x : find(pa[x]);
    }
    bool uni(int p, int q, vector<pi> &rb){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        if(rk[p] < rk[q]) swap(p, q);
        download(sz[p]);
        download(sz[q]);
        sz[p] += sz[q];
        rb.emplace_back(p, q);
        upload(sz[p]);
        pa[q] = p;
        rb.emplace_back(q, -1);
        if(rk[p] == rk[q]){
            rk[p]++;
            rb.emplace_back(p, -2);
        }
        return 1;
    }
    void rollback(vector<pi> &rb){
        reverse(rb.begin(), rb.end());
        for(auto &i : rb){
            if(i.second == -1) pa[i.first] = i.first;
            else if(i.second == -2) rk[i.first]--;
            else{
                download(sz[i.first]);
                sz[i.first] -= sz[i.second];
                upload(sz[i.first]);
                upload(sz[i.second]);
            }
        }
    }
}disj;

int wtf[MAXN];

void dnc(int s, int e, vector<edg> el){
    vector<pi> rb;
    for(auto &i : el){
        if(i.s <= s && e <= i.e){
            disj.uni(i.p, i.q, rb);
        }
    }
    if(s == e){
        printf("%lld\n", seg.tree[1]);
    }
    else{
        int m = (s+e)/2;
        vector<edg> l, r;
        for(auto &i : el){
            if(i.s <= s && e <= i.e) continue;
            if(i.s <= m) l.push_back(i);
            if(m < i.e) r.push_back(i);
        }
        dnc(s, m, l);
        dnc(m+1, e, r);
    }
    disj.rollback(rb);
}

map<pi, int> back;
set<pi> fuck;
vector<edg> edge;
int curT;

void Cut(int x, int y){
    if(x == y) return;
    if(x > y) swap(x, y);
    if(fuck.find(pi(x, y)) != fuck.end()){
        fuck.erase(pi(x, y));
        return;
    }
    if(back[pi(x, y)] <= curT){
        edge.push_back({x, y, back[pi(x, y)], curT});
    }
    back.erase(pi(x, y));
}

void addEdge(int x, int y){
    if(x == y) return;
    if(x > y) swap(x, y);
    if(back.find(pi(x, y)) != back.end()){
        fuck.insert(pi(x, y));
        return;
    }
    back[pi(x, y)] = curT + 1;
}

int main(){
    scanf("%d %d",&n,&q);
    iota(a, a + n + 1, 0);
    for(int i=2; i<=n; i++){
        for(int j=i; j<=n; j+=i){
            if(!low[j]) low[j] = i;
        }
    }
    seg.init(n);
    disj.init(n);
    int cnt = 0;
    for(int i=1; i<=q; i++){
        int x, y; scanf("%d %d",&x,&y);
        Cut(x, a[x]);
        Cut(y, a[y]);
        swap(a[x], a[y]);
        addEdge(x, a[x]);
        addEdge(y, a[y]);
        curT++;
    }
    for(auto &i : back){
        if(i.second <= q) edge.push_back({i.first.first, i.first.second, i.second, q});
    }
    dnc(1, q, edge);
}
