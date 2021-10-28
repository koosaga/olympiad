#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;
const ld PI = 4*atan((ld)1);

template<class T> void ckmin(T &a, T b) { a = min(a, b); }
template<class T> void ckmax(T &a, T b) { a = max(a, b); }

namespace io {
    // TYPE ID (StackOverflow)
    
    template<class T> struct like_array : is_array<T>{};
    template<class T, size_t N> struct like_array<array<T,N>> : true_type{};
    template<class T> struct like_array<vector<T>> : true_type{};
    template<class T> bool is_like_array(const T& a) { return like_array<T>::value; }

    // I/O 
    
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0);
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); }
    }
    
    // INPUT 
    
    template<class T> void re(T& x) { cin >> x; }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest);
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) { re(first); re(rest...); }
    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
    
    // OUTPUT 
    
    template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) {
        os << '{' << a.f << ", " << a.s << '}'; return os;
    }
    template<class T> ostream& printArray(ostream& os, const T& a, int SZ) {
        os << '{';
        F0R(i,SZ) {
            if (i) {
                os << ", ";
                if (is_like_array(a[i])) cout << "\n";
            }
            os << a[i];
        }
        os << '}';
        return os;
    }
    template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
        return printArray(os,a,sz(a));
    }
    template<class T, size_t SZ> ostream& operator<<(ostream& os, const array<T,SZ>& a) {
        return printArray(os,a,SZ);
    }
    
    template<class T> void pr(const T& x) { cout << x << '\n'; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) { 
        cout << first << ' '; pr(rest...); 
    }
}

using namespace io;

int N,M, dir[MX];

void finish() {
    FOR(i,1,N+1) pr(0);
    exit(0);
}

template<int SZ> struct Topo {
    int N, in[SZ], ok[SZ];
    vi res, adj[SZ];
    
    void addEdge(int x, int y) {
        adj[x].pb(y), in[y] ++;
    }
    
    void sort() {
        queue<int> todo;
        FOR(i,1,N+1) if (in[i] == 0) {
            ok[i] = 1;
            todo.push(i);
        }
        while (sz(todo)) {
            int x = todo.front(); todo.pop();
            res.pb(x);
            for (int i: adj[x]) {
                in[i] --;
                if (!in[i]) todo.push(i);
            }
        }
        if (sz(res) == N) {
            FOR(i,1,N+1) pr(ok[i]);
        } else {
            finish();
        }
    }
};

template<int SZ> struct LCA {
    const int MAXK = 32-__builtin_clz(SZ);
    
    int N, R = 1; // vertices from 1 to N, R = root
    vi adj[SZ];
    int par[32-__builtin_clz(SZ)][SZ], depth[SZ];
    
    void addEdge(int u, int v) {
        adj[u].pb(v), adj[v].pb(u);
    }
    
    void dfs(int u, int prev){
        par[0][u] = prev;
        depth[u] = depth[prev]+1;
        for (int v: adj[u]) if (v != prev) dfs(v, u);
    }
    
    void init(int _N) {
        N = _N;
        dfs(R, 0);
        FOR(k,1,MAXK) FOR(i,1,N+1)
            par[k][i] = par[k-1][par[k-1][i]];
    }
    
    int lca(int u, int v){
        if (depth[u] < depth[v]) swap(u,v);
        
        F0Rd(k,MAXK) if (depth[u] >= depth[v]+(1<<k))  u = par[k][u];
        F0Rd(k,MAXK) if (par[k][u] != par[k][v]) u = par[k][u], v = par[k][v];
        
        if(u != v) u = par[0][u], v = par[0][v];
        return u;
    }
    
    int dist(int u, int v) {
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }
    
    bool isAnc(int a, int b) {
        F0Rd(i,MAXK) if (depth[b]-depth[a] >= (1<<i)) b = par[i][b];
        return a == b;
    }
    
    int getAnc(int a, int b) {
        F0Rd(i,MAXK) if (depth[b]-depth[a]-1 >= (1<<i)) b = par[i][b];
        return b;
    }
};

LCA<MX> L;
Topo<MX> T;

void setDir(int x, int y) {
    if (dir[x] && dir[x] != y) finish();
    dir[x] = y;
}

void dfs0(int x) {
    for (int y: L.adj[x]) if (y != L.par[0][x]) {
        dfs0(y);
        if (x != 1 && dir[y] == -1) setDir(x,-1);
    }
}

void dfs1(int x) {
    int co = 0;
    if (dir[x] == 1) co ++;
    for (int y: L.adj[x]) if (y != L.par[0][x]) {
        if (dir[y] == -1) co ++;
    }
    for (int y: L.adj[x]) if (y != L.par[0][x]) {
        if (dir[y] == -1) co --;
        if (co) setDir(y,1);
        if (dir[y] == -1) co ++;
    }
    for (int y: L.adj[x]) if (y != L.par[0][x]) dfs1(y);
}

void genEdge() {
    dfs0(1);
    dfs1(1);
    FOR(i,2,N+1) {
        if (dir[i] == -1) {
            T.addEdge(i,L.par[0][i]);
        } else if (dir[i] == 1) {
            T.addEdge(L.par[0][i],i);
        }
    }
}

int main() {
    // you should actually read the stuff at the bottom
    setIO("gathering"); 
    re(N,M);
    F0R(i,N-1) {
        int a,b; re(a,b);
        L.addEdge(a,b);
    }
    L.init(N);
    F0R(i,M) {
        int a,b; re(a,b); // if you root the tree at b, then every node in the subtree corresponding to a is bad
        if (L.isAnc(a,b)) { // a is ancestor of b
            int B = L.getAnc(a,b); 
            setDir(B,-1);
        } else {
            setDir(a,1);
        }
        T.addEdge(b,a);
    }
    genEdge(); T.N = N; T.sort();
    
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?), set tle
    * do smth instead of nothing and stay organized
*/