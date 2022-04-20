#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

template<class flow_t> struct HLPP {
    struct Edge {
        int to, inv;
        flow_t rem, cap;
    };
 
    vector<basic_string<Edge>> G;
    vector<flow_t> excess;
    vector<int> hei, arc, prv, nxt, act, bot;
    queue<int> Q;
    int n, high, cut, work;
 
    // Initialize for n vertices
    HLPP(int k) : G(k) {}
 
    int addEdge(int u, int v,
                flow_t cap, flow_t rcap = 0) {
        G[u].push_back({ v, sz(G[v]), cap, cap });
        G[v].push_back({ u, sz(G[u])-1, rcap, rcap });
        return sz(G[u])-1;
    }
 
    void raise(int v, int h) {
        prv[nxt[prv[v]] = nxt[v]] = prv[v];
        hei[v] = h;
        if (excess[v] > 0) {
            bot[v] = act[h]; act[h] = v;
            high = max(high, h);
        }
        if (h < n) cut = max(cut, h+1);
        nxt[v] = nxt[prv[v] = h += n];
        prv[nxt[nxt[h] = v]] = v;
    }
 
    void global(int s, int t) {
        hei.assign(n, n*2);
        act.assign(n*2, -1);
        iota(all(prv), 0);
        iota(all(nxt), 0);
        hei[t] = high = cut = work = 0;
        hei[s] = n;
        for (int x : {t, s})
            for (Q.push(x); !Q.empty(); Q.pop()) {
                int v = Q.front();
                for(auto &e : G[v]){
                    if (hei[e.to] == n*2 &&
                        G[e.to][e.inv].rem)
                        Q.push(e.to), raise(e.to,hei[v]+1);
                }
            }
    }
 
    void push(int v, Edge& e, bool z) {
        auto f = min(excess[v], e.rem);
        if (f > 0) {
            if (z && !excess[e.to]) {
                bot[e.to] = act[hei[e.to]];
                act[hei[e.to]] = e.to;
            }
            e.rem -= f; G[e.to][e.inv].rem += f;
            excess[v] -= f; excess[e.to] += f;
        }
    }
 
    void discharge(int v) {
        int h = n*2, k = hei[v];
 
        for(int j = 0; j < sz(G[v]); j++){
            auto& e = G[v][arc[v]];
            if (e.rem) {
                if (k == hei[e.to]+1) {
                    push(v, e, 1);
                    if (excess[v] <= 0) return;
                } else h = min(h, hei[e.to]+1);
            }
            if (++arc[v] >= sz(G[v])) arc[v] = 0;
        }
 
        if (k < n && nxt[k+n] == prv[k+n]) {
            for(int j = k; j < cut; j++){
            while (nxt[j+n] < n)
                raise(nxt[j+n], n);
            }
            cut = k;
        } else raise(v, h), work++;
    }
 
    // Compute maximum flow from src to dst
    flow_t flow(int src, int dst) {
        excess.assign(n = sz(G), 0);
        arc.assign(n, 0);
        prv.assign(n*3, 0);
        nxt.assign(n*3, 0);
        bot.assign(n, 0);
        for(auto &e : G[src]){
            excess[src] = e.rem, push(src, e, 0);
        }
 
        global(src, dst);
 
        for (; high; high--)
            while (act[high] != -1) {
                int v = act[high];
                act[high] = bot[v];
                if (v != src && hei[v] == high) {
                    discharge(v);
                    if (work > 4*n) global(src, dst);
                }
            }
 
        return excess[dst];
    }
 
    // Get flow through e-th edge of vertex v
    flow_t getFlow(int v, int e) {
        return G[v][e].cap - G[v][e].rem;
    }
 
    // Get if v belongs to cut component with src
    bool cutSide(int v) { return hei[v] >= n; }
};
 
template <class T> struct Circulation {
    const T INF = numeric_limits<T>::max() / 2;
    T lowerBoundSum = 0;
    HLPP<T> mf;
 
    // Initialize for n vertices
    Circulation(int k) : mf(k + 2) {}
    void addEdge(int s, int e, T l, T r){
        mf.addEdge(s + 2, e + 2, r - l);
        if(l > 0){
            mf.addEdge(0, e + 2, l);
            mf.addEdge(s + 2, 1, l);
            lowerBoundSum += l;
        }
        else{
            mf.addEdge(0, s + 2, -l);
            mf.addEdge(e + 2, 1, -l);
            lowerBoundSum += -l;
        }
    }
    bool solve(int s, int e){
 //       mf.addEdge(e+2, s+2, INF); // to reduce as maxflow with lower bounds, in circulation problem skip this line
        return lowerBoundSum == mf.flow(0, 1);
        // to get maximum LR flow, run maxflow from s+2 to e+2 again
    }
};

template <class T> struct MinCostCirculation {
    const int SCALE = 3; // scale by 1/(1 << SCALE)
    const T INF = numeric_limits<T>::max() / 2;
    struct EdgeStack {
        int s, e;
        T l, r, cost;
    };
    struct Edge {
        int pos, rev;
        T rem, cap, cost;
    };
    int n;
    vector<EdgeStack> estk;
    Circulation<T> circ;
    vector<vector<Edge>> gph;
    vector<T> p;
    MinCostCirculation(int k) : circ(k), gph(k), p(k) { n = k; }
    void addEdge(int s, int e, T l, T r, T cost){
        estk.push_back({s, e, l, r, cost});
    }
    pair<bool, T> solve(){
        for(auto &i : estk){
            if(i.s != i.e) circ.addEdge(i.s, i.e, i.l, i.r);
        }
        if(!circ.solve(-1, -1)){
            return make_pair(false, T(0));
        }
        vector<int> ptr(n);
        T eps = 0;
        for(auto &i : estk){
            T curFlow;
            if(i.s != i.e) curFlow = i.r - circ.mf.G[i.s + 2][ptr[i.s]].rem;
            else curFlow = i.r;
            int srev = sz(gph[i.e]);
            int erev = sz(gph[i.s]);
            if(i.s == i.e) srev++;
            gph[i.s].push_back({i.e, srev, i.r - curFlow, i.r, i.cost * (n + 1)});
            gph[i.e].push_back({i.s, erev, -i.l + curFlow, -i.l, -i.cost * (n + 1)});
            eps = max(eps, abs(i.cost) * (n + 1));
            if(i.s != i.e){
                ptr[i.s] += 2;
                ptr[i.e] += 2;
            }
        }
        while(true){
            auto cost = [&](Edge &e, int s, int t){
                return e.cost + p[s] - p[t];
            };
            eps = 0;
            for(int i = 0; i < n; i++){
            	for(auto &e : gph[i]){
            		if(e.rem > 0) eps = max(eps, -cost(e, i, e.pos));
				}
			}
			if(eps <= T(1)) break;
            eps = max(T(1), eps >> SCALE);
            bool upd = 1;
            for(int it = 0; it < 5 && upd; it++){
            	upd = false;
            	for(int i = 0; i < n; i++){
            		for(auto &e : gph[i]){
            			if(e.rem > 0 && p[e.pos] > p[i] + e.cost + eps){
            				p[e.pos] = p[i] + e.cost + eps;
            				upd = true;
						}
					}
				}
				if(!upd) break;
			}
			if(!upd) continue;
            vector<T> excess(n);
            queue<int> que;
            auto push = [&](Edge &e, int src, T flow){
                e.rem -= flow;
                gph[e.pos][e.rev].rem += flow;
                excess[src] -= flow;
                excess[e.pos] += flow;
                if(excess[e.pos] <= flow && excess[e.pos] > 0){
                    que.push(e.pos);
                }
            };
            vector<int> ptr(n);
            auto relabel = [&](int v){
            	ptr[v] = 0;
                p[v] = -INF;
                for(auto &e : gph[v]){
                    if(e.rem > 0){
                        p[v] = max(p[v], p[e.pos] - e.cost - eps);
                    }
                }
            };
            for(int i = 0; i < n; i++){
                for(auto &j : gph[i]){
                    if(j.rem > 0 && cost(j, i, j.pos) < 0){
                        push(j, i, j.rem);
                    }
                }
            }
            while(sz(que)){
                int x = que.front();
                que.pop();
                while(excess[x] > 0){
                	for(; ptr[x] < sz(gph[x]); ptr[x]++){
                		Edge &e = gph[x][ptr[x]];
                        if(e.rem > 0 && cost(e, x, e.pos) < 0){
                            push(e, x, min(e.rem, excess[x]));
                            if(excess[x] == 0) break;
                        }
                    }
                    if(excess[x] == 0) break;
                    relabel(x);
                }
            }
        }
        T ans = 0;
        for(int i = 0; i < n; i++){
            for(auto &j : gph[i]){
                j.cost /= (n + 1);
                ans += (__int128)j.cost * (j.cap - j.rem);
            }
        }
        return make_pair(true, ans / 2);
    }
    void bellmanFord(){
        fill(all(p), T(0));
        bool upd = 1;
        while(upd){
            upd = 0;
            for(int i = 0; i < n; i++){
                for(auto &j : gph[i]){
                    if(j.rem > 0 && p[j.pos] > p[i] + j.cost){
                        p[j.pos] = p[i] + j.cost;
                        upd = 1;
                    }
                }
            }
        }
    }
};

struct edg{
	int s, e, x;
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	MinCostCirculation<lint> mcc(2*n+2);
	vector<int> omega(2*n, 1e9);
	vector<edg> v;
	for(int i = 0; i < m; i++){
		int s, e, x; cin >> s >> e >> x;
		s--; e--;
		e += n;
		omega[s] = min(omega[s], x);
		omega[e] = min(omega[e], x);
		v.push_back({s, e, x});
	}
	for(auto &i : v){
		mcc.addEdge(i.s + 1, i.e + 1, 0, 1, - (omega[i.s] + omega[i.e] - i.x));
	}
	for(int i = 1; i <= n; i++){
		mcc.addEdge(0, i, 0, 1, 0);
		mcc.addEdge(i+n, 2*n+1, 0, 1, 0);
	}
	mcc.addEdge(2*n+1, 0, 0, 1e9, 0);
	if(*max_element(all(omega)) > 1e8){
		cout << "NIE\n";
		return 0;
	}
	cout << accumulate(all(omega), 0) + mcc.solve().second << "\n";
}
