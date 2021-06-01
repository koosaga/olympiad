#include "escape_route.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

struct edg{
    int pos;
    lint L, C;
};

struct node{
    int i, j; lint max_time;
    bool operator<(const node &n)const{
        return max_time < n.max_time;
    }
};

lint daybreak[96][96];
lint dayfinish[96][96];
lint adj[96][96], dp[96][96];
vector<edg> gph[96];

vector<pi> prec[96][96];
vector<pi> qq[96][96];

lint S;
lint ret[3000005];
lint D1[8100][96], D2[8100][96];

void Do(int n){
	int idx = 0;
    for(int u = 0; u < n; u++){
        for(auto &e : gph[u]){
            int v = e.pos;
            vector<lint> dist1(n, -3e18), dist2(n, 3e18);
            // backward shortest path
            {
                dist1[u] = e.C - e.L;
                vector<int> vis(n);
                for(int it = 0; it < n; it++){
                    pi ret(-5e18, 5e18);
                    for(int i = 0; i < n; i++){
                        if(!vis[i]) ret = max(ret, pi(dist1[i], i));
                    }
                    if(ret.first < 0) break;
                    int x = ret.second;
                    vis[x] = 1;
                    for(auto &e : gph[x]){
                        if(dist1[e.pos] < dist1[x] - e.L && dist1[x] < e.C){
                            dist1[e.pos] = dist1[x] - e.L;
                        }
                    }
                }
            }
            // forward shortest path
            {
                dist2[v] = e.C;
                vector<int> vis(n);
                for(int it = 0; it < n; it++){
                    pi ret(5e18, 5e18);
                    for(int i = 0; i < n; i++){
                        if(!vis[i]) ret = min(ret, pi(dist2[i], i));
                    }
                    int x = ret.second;
                    if(ret.first > S) break;
                    vis[x] = 1;
                    for(auto &e : gph[x]){
                        if(dist2[e.pos] > dist2[x] + e.L && dist2[x] + e.L <= e.C){
                            dist2[e.pos] = dist2[x] + e.L;
                        }
                    }
                }
            }
            for(int i = 0; i < n; i++){
            	if(dist1[i] < 0) dist1[i] = -1e18;
            	if(dist2[i] > S) dist2[i] = 1e18;
            	D1[idx][i] = dist1[i];
            	D2[idx][i] = dist2[i];
			}
			idx++;
        }
    }
    for(int i = 0; i < n; i++){
    	vector<tuple<lint, lint, lint>> shit;
    	for(int j = 0; j < n; j++){
    		for(auto &k : qq[i][j]) shit.emplace_back(k.first, k.second, j);
		}
    	vector<int> fuck(idx);
    	iota(all(fuck), 0);
    	sort(all(fuck), [&](int x, int y){
    		return D1[x][i] < D1[y][i];
		});
		sort(all(shit));
		reverse(all(shit));
		vector<lint> ds(n, 1e18);
		for(auto &[T, idx, V] : shit){
			while(sz(fuck) && D1[fuck.back()][i] >= T){
				for(int j = 0; j < n; j++){
					ds[j] = min(ds[j], D2[fuck.back()][j] - D1[fuck.back()][i]);
				}
				fuck.pop_back();
			}
			ret[idx] = min(ret[idx], ds[V]);
		}
	}
}

// wtf just use namespace std and pairs
std::vector<long long> calculate_necessary_time(
        int N, int M, long long Sfuck, int Q, std::vector<int> A, std::vector<int> B,
        std::vector<long long> L, std::vector<long long> C, std::vector<int> U,
        std::vector<int> V, std::vector<long long> T) {
    S = Sfuck;
    for(int i = 0; i < M; i++){
        gph[A[i]].push_back({B[i], L[i], C[i]});
        gph[B[i]].push_back({A[i], L[i], C[i]});
    }
    {
        priority_queue<node> pq;
        memset(daybreak, 0x3f, sizeof(daybreak));
        auto enq = [&](int s, int e, lint x){
            if(daybreak[s][e] > x){
                daybreak[s][e] = x;
                pq.push({s, e, -x});
            }
        };
        for(int i = 0; i < N; i++){
            enq(i, i, 0);
        }
        while(sz(pq)){
            auto x = pq.top(); pq.pop();
            x.max_time = -x.max_time;
            if(daybreak[x.i][x.j] != x.max_time) continue;
            for(auto &e : gph[x.j]){
                if(x.max_time + e.L <= e.C){
                    enq(x.i, e.pos, x.max_time + e.L);
                }
            }
        }
    }
    {
        priority_queue<node> pq;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                dayfinish[i][j] = -1e18;
            }
        }
        auto enq = [&](int s, int e, lint x){
            if(dayfinish[s][e] < x){
                dayfinish[s][e] = x;
                pq.push({s, e, x});
            }
        };
        for(int i = 0; i < N; i++){
            enq(i, i, S);
        }
        while(sz(pq)){
            auto x = pq.top(); pq.pop();
            if(dayfinish[x.i][x.j] != x.max_time) continue;
            for(auto &e : gph[x.i]){
                lint val = min(x.max_time, e.C) - e.L;
                if(val >= 0) enq(e.pos, x.j, val);
            }
        }
    }
    {
        memset(adj, 0x3f, sizeof(adj));
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(dayfinish[i][j] >= 0) adj[i][j] = 1;
                if(i == j) adj[i][j] = 0;
            }
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++){
                    adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
                }
            }
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                assert(adj[i][j] <= N);
                dp[i][j] = 1e18;
                for(int k = 0; k < N; k++){
                    dp[i][j] = min(adj[i][k] * S + daybreak[k][j], dp[i][j]);
                }
            }
        }
	}
	fill(ret, ret + Q, 1e18);
	for(int i = 0; i < Q; i++){
		qq[U[i]][V[i]].emplace_back(T[i], i);
	}
	for(int i = 0; i < Q; i++){
		for(int j = 0; j < N; j++){
			if(dayfinish[U[i]][j] >= T[i]){
				ret[i] = min(ret[i], S - T[i] + dp[j][V[i]]);
			}
		}
	}
	Do(N);
	vector<lint> ans(ret, ret + Q);
	return ans;
}
