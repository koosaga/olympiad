#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef __int128 lint;
typedef pair<lint, lint> pi;
const int MAXN = 105;
const int mod = 1e9 + 7;

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};

struct mcmf{
    struct edg{ int pos, cap, rev; lint cost; };
    vector<edg> gph[MAXN];
    void clear(){
        for(int i=0; i<MAXN; i++) gph[i].clear();
    }
    void add_edge(int s, int e, int x, lint c){
        gph[s].push_back({e, x, (int)gph[e].size(), c});
        gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
    }
    lint dist[MAXN];
    int pa[MAXN], pe[MAXN];
    bool inque[MAXN];
    bool spfa(int src, int sink, int n){
        memset(dist, 0x3f, sizeof(dist[0]) * n);
        memset(inque, 0, sizeof(inque[0]) * n);
        queue<int> que;
        dist[src] = 0;
        inque[src] = 1;
        que.push(src);
        bool ok = 0;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            if(x == sink) ok = 1;
            inque[x] = 0;
            for(int i=0; i<gph[x].size(); i++){
                edg e = gph[x][i];
                if(e.cap > 0 && dist[e.pos] > dist[x] + e.cost){
                    dist[e.pos] = dist[x] + e.cost;
                    pa[e.pos] = x;
                    pe[e.pos] = i;
                    if(!inque[e.pos]){
                        inque[e.pos] = 1;
                        que.push(e.pos);
                    }
                }
            }
        }
        return ok;
    }
    lint new_dist[MAXN];
    pair<bool, lint> dijkstra(int src, int sink, int n){
        priority_queue<pi, vector<pi>, greater<pi> > pq;
        memset(new_dist, 0x3f, sizeof(new_dist[0]) * n);
        new_dist[src] = 0;
        pq.emplace(0, src);
        bool isSink = 0;
        while(sz(pq)){
            auto tp = pq.top(); pq.pop();
            if(new_dist[tp.second] != tp.first) continue;
            int v = tp.second;
            if(v == sink) isSink = 1;
            for(int i = 0; i < gph[v].size(); i++){
                edg e = gph[v][i];
                lint new_weight = e.cost + dist[v] - dist[e.pos];
                if(e.cap > 0 && new_dist[e.pos] > new_dist[v] + new_weight){
                    new_dist[e.pos] = new_dist[v] + new_weight;
                    pa[e.pos] = v;
                    pe[e.pos] = i;
                    pq.emplace(new_dist[e.pos], e.pos);
                }
            }
        }
        return make_pair(isSink, new_dist[sink]);
    }

    vector<lint> match(int src, int sink, int n){
        spfa(src, sink, n);
        pair<bool, lint> path;
        vector<lint> ret;
        while((path = dijkstra(src, sink, n)).first){
            for(int i = 0; i < n; i++) dist[i] += min(lint(2e15), new_dist[i]);
            lint cap = 1e18;
            for(int pos = sink; pos != src; pos = pa[pos]){
                cap = min(cap, (lint)gph[pa[pos]][pe[pos]].cap);
            }
            for(int i = 0; i < cap; i++) ret.push_back(dist[sink] - dist[src]);
            for(int pos = sink; pos != src; pos = pa[pos]){
                int rev = gph[pa[pos]][pe[pos]].rev;
                gph[pa[pos]][pe[pos]].cap -= cap;
                gph[pos][rev].cap += cap;
            }
        }
        return ret;
    }
}mcmf;

bool cmp(pi a, pi b){
    return (__int128) a.first * b.second < (__int128) a.second * b.first;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; i++){
        int a, b, u, c;
        cin >> a >> b >> u >> c;
        mcmf.add_edge(a, b, u, c);
    }
    auto sln = mcmf.match(s, t, n+1);
    int M = sz(sln);
    vector<lint> ans(M + 1);
    pi dap(M * M, 1);
    for(int i = 1; i <= M; i++){
        ans[i] = ans[i-1] + sln[i-1];
    }
    reverse(all(ans));
    for(int i = 0; i <= M; i++){
    //  cout << ans[i] << "\n";
        dap = min(dap, pi(i * i + ans[i] * ans[i], 1), cmp);
    }
    for(int i = 0; i < M; i++){
        lint A = ans[i + 1] - ans[i];
        lint B = ans[i] - A * i;
        pi x(-A * B, A * A + 1);
        if(x.second * i <= x.first && x.first <= x.second * (i + 1)){
            pi ret((A * A + 1) * x.first * x.first 
            + 2 * A * B * x.first * x.second
            + B * B * x.second * x.second, x.second * x.second);
            dap = min(dap, ret, cmp);
        }
    }
    lint g = gcd(dap.first, dap.second);
    cout << (long long)(dap.first / g) << "/" << (long long)(dap.second / g) << "\n";
}
