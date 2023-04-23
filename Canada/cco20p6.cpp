#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

namespace Epp98{
    struct node{
        node *son[2];
        pi val;
        node(){
            son[0] = son[1] = NULL;
            val = pi(-1e18, -1e18);
        }
        node(pi p){
            son[0] = son[1] = NULL;
            val = p;
        }
    };

    node* copy(node *x){
        if(x == NULL) return NULL;
        node *nd = new node();
        nd->son[0] = x->son[0];
        nd->son[1] = x->son[1];
        nd->val = x->val;
        return nd;
    }

    // precondition: x, y both points to new entity
    node* merge(node *x, node *y){
        if(!x) return y;
        if(!y) return x;
        if(x->val > y->val) swap(x, y);
        int rd = randint(0, 1);
        if(x->son[rd]) x->son[rd] = copy(x->son[rd]);
        x->son[rd] = merge(x->son[rd], y);
        return x;
    }

    struct edg{
        int pos;
        lint weight;
        int idx;
    };
    vector<vector<edg>> gph, rev;
    int idx;
    void init(int n){
        gph.clear();
        rev.clear();
        gph.resize(n);
        rev.resize(n);
        idx = 0;
    }
    void add_edge(int s, int e, lint x){
        gph[s].push_back((edg){e, x, idx});
        rev[e].push_back((edg){s, x, idx});
        idx++;
    }
    vector<int> par, pae;
    vector<lint> dist;
    vector<node*> heap;
    void dijkstra(int snk){
        // replace this to SPFA if edge weight is negative
        int n = sz(gph);
        par.resize(n);
        pae.resize(n);
        dist.resize(n);
        heap.resize(n);
        fill(all(par), -1);
        fill(all(pae), -1);
        fill(all(dist), 2e18);
        fill(all(heap), (node*) NULL);
        priority_queue<pi, vector<pi>, greater<pi> > pq;
        auto enq = [&](int x, lint v, int pa, int pe){
            if(dist[x] > v){
                dist[x] = v;
                par[x] = pa;
                pae[x] = pe;
                pq.emplace(v, x);
            }
        };
        enq(snk, 0, -1, -1);
        vector<int> ord;
        while(sz(pq)){
            auto [w, v] = pq.top(); pq.pop();
            if(dist[v] != w) continue;
            ord.push_back(v);
            for(auto &e : rev[v]) enq(e.pos, e.weight + w, v, e.idx);
        }
        for(auto &v : ord){
            if(par[v] != -1){
                heap[v] = copy(heap[par[v]]);
            }
            for(auto &i : gph[v]){
                if(i.idx == pae[v]) continue;
                lint delay = dist[i.pos] + i.weight - dist[v];
                if(delay < 1e18){
                    heap[v] = merge(heap[v], new node(pi(delay, i.pos)));
                }
            }
        }
    }
    vector<lint> ksp(int s, int e, int k){
        dijkstra(e);
        using state = pair<lint, node*>;
        priority_queue<state, vector<state>, greater<state>> pq;
        vector<lint> ans;
        if(dist[s] > 1e18){
            ans.resize(k);
            fill(all(ans), -1);
            return ans;
        }
        ans.push_back(dist[s]);
        if(heap[s]) pq.emplace(dist[s] + heap[s]->val.first, heap[s]);
        while(sz(pq) && sz(ans) < k){
            auto [cst, ptr] = pq.top();
            pq.pop();
            ans.push_back(cst);
            for(int j = 0; j < 2; j++){
                if(ptr->son[j]){
                    pq.emplace(cst - ptr->val.first + ptr->son[j]->val.first, ptr->son[j]);
                }
            }
            int v = ptr->val.second;
            if(heap[v]) pq.emplace(cst + heap[v]->val.first, heap[v]);
        }
        while(sz(ans) < k) ans.push_back(-1);
        return ans;
    }
}

int n, m, k;
vector<int> pos[MAXN];
vector<lint> vect[MAXN];
pi a[MAXN];

struct node{
    int pos;
    int cnt;
    lint value;
    int limit;
    int curins;
    bool operator<(const node &n)const{
        return value > n.value;
    }
};

int main(){
    scanf("%d %d %d",&m,&n,&k);
    for(int i = 0; i < m; i++){
        int a, c; scanf("%d %d",&a,&c);
        pos[a].push_back(c);
    }
    for(int i = 1; i <= n; i++) scanf("%lld %lld",&a[i].first,&a[i].second);
    lint curSum = 0;
    priority_queue<node> pq;
    for(int i = 1; i <= n; i++){
        sort(all(pos[i]));
        if(sz(pos[i]) < a[i].first){
            for(int j = 0; j < k; j++) puts("-1");
            return 0;
        }
        a[i].second = min(a[i].second, 1ll * sz(pos[i]));
        for(int j = 0; j < a[i].first; j++) curSum += pos[i][j];
        pq.push({i, 0, 0, sz(pos[i]), sz(pos[i])});
    }
    for(int i = 0; i < k + n; i++){
        if(!sz(pq)) break;
        auto x = pq.top(); pq.pop();
        vect[x.pos].push_back(x.value);
        if(x.cnt < a[x.pos].second){
            int to_remove = a[x.pos].first - x.cnt - 1;
            if(max(0, to_remove + 1) < x.curins){
                pq.push({x.pos, x.cnt + 1, 
                x.value + pos[x.pos][max(0,to_remove + 1)] - (to_remove >= 0 ? pos[x.pos][to_remove] : 0), 
                        x.curins, max(0, to_remove + 1)});
            }
            /*
            for(int j = x.limit - 1; j >= 0 && j >= to_remove + 1; j--){
                pq.push({x.pos, x.cnt + 1, x.value + pos[x.pos][j] - (to_remove >= 0 ? pos[x.pos][to_remove] : 0), j});
            }*/
        }
        if(x.curins + 1 < x.limit){
            pq.push({x.pos, x.cnt, x.value + pos[x.pos][x.curins + 1] - pos[x.pos][x.curins], x.limit, x.curins + 1});
        }
    }
    Epp98::init(n+1);
    for(int i = 1; i <= n; i++){
        if(sz(vect[i]) == 0) vect[i].push_back(0);
        for(int j = 0; j < sz(vect[i]); j++) Epp98::add_edge(i - 1, i, vect[i][j]);
    }
    auto ans = Epp98::ksp(0, n, k);
    for(int i = 0; i < k; i++){
        if(ans[i] < 0) puts("-1");
        else printf("%lld\n", ans[i] + curSum);
    }
}
