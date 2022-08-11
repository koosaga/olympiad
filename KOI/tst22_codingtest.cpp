#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
 
vector<int> ans;
vector<lint> f, g;
 
struct query{
	int l, r, idx;
};
 
lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}
 
int S[MAXN], E[MAXN], X[MAXN];
lint Lmax[MAXN], Rmin[MAXN];
 
void solve(int s, int e, vector<query> &q){
	if(!sz(q)) return;
	if(s == e){
		for(auto &x : q){
			ans[x.idx] = g[e] - f[s - 1];
		}
      return;
	}
	int m = (s + e) / 2;
	vector<query> L, R, H;
	for(auto &y : q){
		if(y.r <= m) L.push_back(y);
		else if(y.l > m) R.push_back(y);
		else H.push_back(y);
	}
	solve(s, m, L);
	solve(m + 1, e, R);
	vector<query> H1 = H, H2 = H;
	sort(all(H1), [&](const query &a, const query &b){
		return a.l > b.l;
	});
	sort(all(H2), [&](const query &a, const query &b){
		return a.r < b.r;
	});
	// L
	{
		vector<pi> stk;
		int p = 0;
		lint cur = 1e9;
		for(int i = m; i >= s; i--){
			pi G(i, g[i]);
			while(sz(stk) >= 2 && ccw(stk[sz(stk) - 2], stk.back(), G) >= 0) stk.pop_back();
			stk.push_back(G);
			pi F(i - 1, f[i - 1]);
			int s = 0, e = sz(stk) - 1;
			while(s != e){
				int m = (s + e) / 2;
				if(ccw(F, stk[m], stk[m + 1]) <= 0) s = m + 1;
				else e = m;
			}
			cur = min(cur, (stk[s].second - F.second) / (stk[s].first - F.first)); 
			while(p < sz(H1) && H1[p].l == i){
				ans[H1[p].idx] = min(ans[H1[p].idx], (int)cur); 
				p++;
			}
		}
	}
	// R 
	{
		vector<pi> stk;
		int p = 0;
		lint cur = 1e9;
		for(int i = m + 1; i <= e; i++){
			pi F(i - 1, f[i - 1]);
			while(sz(stk) >= 2 && ccw(stk[sz(stk) - 2], stk.back(), F) >= 0) stk.pop_back();
			stk.push_back(F);
			pi G(i, g[i]);
			int s = 0, e = sz(stk) - 1;
			while(s != e){
				int m = (s + e) / 2;
				if(ccw(stk[m], stk[m + 1], G) >= 0) e = m;
				else s = m + 1;
			}
			cur = min(cur, (G.second - stk[s].second) / (G.first - stk[s].first));
			while(p < sz(H2) && H2[p].r == i){
				ans[H2[p].idx] = min(ans[H2[p].idx], (int)cur); 
				p++;
			}
		}
	}
	// M
	{
		for(auto &x : H){
			S[x.idx] = 0, E[x.idx] = 3e8, Lmax[x.idx] = -1e18, Rmin[x.idx] = 1e18;
		}
		bool doit = true;
		while(doit){
			vector<pi> stk;
			int p = 0;
			for(auto &x : H){
				if(S[x.idx] != E[x.idx]){
					X[x.idx] = (S[x.idx] + E[x.idx] + 1) / 2;
				}
			}
			for(int i = m; i >= s; i--){
				pi F(i - 1, f[i - 1]);
				while(sz(stk) >= 2 && ccw(stk[sz(stk) - 2], stk.back(), F) <= 0) stk.pop_back();
				stk.push_back(F);
				while(p < sz(H1) && H1[p].l == i){
					int s = 0, e = sz(stk) - 1;
					auto func = [&](int m){
						return stk[m].second - 1ll * X[H1[p].idx] * stk[m].first;
					};
					while(s != e){
						int m = (s + e) / 2;
						if(func(m) > func(m + 1)) e = m;
						else s = m + 1;
					}
					Lmax[H1[p].idx] = func(s);
					p++;
				}
			}
			p = 0;
			stk.clear();
			for(int i = m + 1; i <= e; i++){
				pi G(i, g[i]);
				while(sz(stk) >= 2 && ccw(stk[sz(stk) - 2], stk.back(), G) <= 0) stk.pop_back();
				stk.push_back(G);
				while(p < sz(H2) && H2[p].r == i){
					int s = 0, e = sz(stk) - 1;
					auto func = [&](int m){
						return stk[m].second - 1ll * X[H2[p].idx] * stk[m].first;
					};
					while(s != e){
						int m = (s + e) / 2;
						if(func(m) < func(m + 1)) e = m;
						else s = m + 1;
					}
					Rmin[H2[p].idx] = func(s);
					p++;
				}
			}
			doit = false;
			for(auto &x : H){
				if(S[x.idx] != E[x.idx]){
					if(Lmax[x.idx] > Rmin[x.idx]) E[x.idx] = X[x.idx] - 1;
					else S[x.idx] = X[x.idx];
					if(S[x.idx] != E[x.idx]) doit = true;
				}
			}
		}
		for(auto &x : H){
			ans[x.idx] = min(ans[x.idx], S[x.idx]);
		}
	}
}
 
std::vector<int> testset(std::vector<int> A, std::vector<int> B, std::vector<int> L, std::vector<int> U){
	int n = sz(A);
	f.resize(n + 1);
	g.resize(n + 1);
	for(int i = 1; i <= n; i++){
		g[i] += A[i - 1];
		f[i] += A[i - 1];
	}
	for(int i = 1; i < n; i++){
		g[i] += B[i - 1];
		f[i + 1] += B[i - 1];
	}
	for(int i = 1; i <= n; i++){
		g[i] += g[i - 1];
		f[i] += f[i - 1];
	}
	int Q = sz(L);
	ans.resize(Q);
	fill(all(ans), 1e9);
	vector<query> queries;
	for(int i = 0; i < Q; i++){
		L[i]++;
		U[i]++;
		queries.push_back({L[i], U[i], i});
	}
	solve(1, n, queries);
	return ans;
}