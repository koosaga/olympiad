#include "collapse.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 100050;

struct disj{
	int pa[MAXN], rk[MAXN];
	void init(int n){ iota(pa, pa + n, 0); fill(rk, rk + n, 0); }
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		pa[q] = p;
		if(rk[p] == rk[q]) rk[p]++;
		return 1;
	}
	bool uni(int p, int q, vector<pi> &r){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		pa[q] = p;
		r.push_back(pi(1, q));
		if(rk[p] == rk[q]){
			rk[p]++;
			r.push_back(pi(2, p));
		}
		return 1;
	}
	void revert(vector<pi> &r){
		for(int i=(int)r.size()-1; i>=0; i--){
			if(r[i].first == 2) rk[r[i].second]--;
			else pa[r[i].second] = r[i].second;
		}
		r.clear();
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}E[MAXN];

struct bit{
	int tree[MAXN];
	void clear(){ memset(tree, 0, sizeof(tree)); }
	void add(int x, int v){
		x++;
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		x++;
		int ret= 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

vector<pi> query[MAXN];
int ans[MAXN];
pi qry[MAXN];
int chk[MAXN];

void solve(int s, int e, vector<int> active_edges){
	if(s == e){
		E[qry[s].first].x = qry[s].second; 
		vector<int> nxt_active_edges = active_edges;
		nxt_active_edges.push_back(qry[s].first);
		sort(nxt_active_edges.begin(), nxt_active_edges.end(), [&](const int &a, const int &b){
			return E[a].x < E[b].x;
		});
		vector<pi> tmp;
		vector<int> sex;
		for(auto &i : nxt_active_edges){
			if(disj.uni(E[i].s, E[i].e, tmp)){
				sex.push_back(E[i].x);
		//		printf("MST add %d\n", i);
				bit.add(E[i].x, 1);
			}
		}
		for(auto &i : query[s]){
			ans[i.second] += bit.query(i.first);
		}
		disj.revert(tmp);
	//	printf("state of query %d\n", s);
		for(auto &i : sex) bit.add(i, -1);
		return;
	}
	int m = (s+e)/2;
	/*** CONTRACTION 1 ***/
	{
		vector<int> nxt_active_edges = active_edges;
		for(int i=m+1; i<=e; i++){
			chk[qry[i].first]--;
			if(chk[qry[i].first] == 0) nxt_active_edges.push_back(qry[i].first);
		}
		sort(nxt_active_edges.begin(), nxt_active_edges.end(), [&](const int &a, const int &b){
			return E[a].x < E[b].x;
		});
		vector<int> maybe, must, cand;
		{
			vector<pi> tmp;
			for(auto &i : nxt_active_edges){
				if(disj.uni(E[i].s, E[i].e, tmp)) maybe.push_back(i);
			}
			disj.revert(tmp);
		}
		{
			vector<pi> tmp;
			for(int i=s; i<=m; i++) disj.uni(E[qry[i].first].s, E[qry[i].first].e, tmp);
			for(auto &i : maybe){
				if(disj.uni(E[i].s, E[i].e, tmp)) must.push_back(i);
				else cand.push_back(i);
			}
			disj.revert(tmp);
		}
		vector<pi> tmp;
		vector<int> sex;
		for(auto &i : must){
	//		printf("MST add %d\n", i);
			disj.uni(E[i].s, E[i].e, tmp);
			bit.add(E[i].x, 1);
			sex.push_back(E[i].x);
		}
		solve(s, m, cand);
		disj.revert(tmp);
		for(int i=m+1; i<=e; i++){
			chk[qry[i].first]++;
		}
		for(auto &i : sex) bit.add(i, -1);
	}
	/*** CONTRACTION 2 ***/
	{
		vector<int> nxt_active_edges = active_edges;
		for(int i=s; i<=m; i++){
			chk[qry[i].first]--;
			if(chk[qry[i].first] == 0) nxt_active_edges.push_back(qry[i].first);
		}
		sort(nxt_active_edges.begin(), nxt_active_edges.end(), [&](const int &a, const int &b){
			return E[a].x < E[b].x;
		});
		vector<int> maybe, must, cand;
		{
			vector<pi> tmp;
			for(auto &i : nxt_active_edges){
				if(disj.uni(E[i].s, E[i].e, tmp)) maybe.push_back(i);
			}
			disj.revert(tmp);
		}
		{
			vector<pi> tmp;
			for(int i=m+1; i<=e; i++) disj.uni(E[qry[i].first].s, E[qry[i].first].e, tmp);
			for(auto &i : maybe){
				if(disj.uni(E[i].s, E[i].e, tmp)) must.push_back(i);
				else cand.push_back(i);
			}
			disj.revert(tmp);
		}
		vector<pi> tmp;
		vector<int> sex;
		for(auto &i : must){
	//		printf("MST add %d\n", i);
			disj.uni(E[i].s, E[i].e, tmp);
			bit.add(E[i].x, 1);
			sex.push_back(E[i].x);
		}
		solve(m+1, e, cand);
		disj.revert(tmp);
		for(int i=s; i<=m; i++){
			chk[qry[i].first]++;
		}
		for(auto &i : sex) bit.add(i, -1);
	}
}

void solve_dmst(int Q, int VN, int EN){
	disj.init(VN);
	vector<int> v;
	memset(chk, 0, sizeof(chk));
	for(int i=0; i<Q; i++) chk[qry[i].first]++;
	for(int i=0; i<EN; i++){
		if(chk[i] == 0) v.push_back(i);
	}
	solve(0, Q-1, v);
}

std::vector<int> simulateCollapse(int N, vector<int> T, vector<int> X, vector<int> Y, vector<int> W, vector<int> P){
	int Q = W.size();
	int C = T.size();
	for(int i=0; i<Q; i++){
		query[W[i]].push_back(pi(P[i], i)); // count edges with weight leq than
	}
	int cnt = 0;
	map<pi, int> mp;
	for(int i=0; i<C; i++){
		if(T[i] == 0){
			E[cnt++] = (edg){X[i], Y[i], N + 3};
			mp[pi(X[i], Y[i])] = mp[pi(Y[i], X[i])] = cnt - 1;
			qry[i] = pi(cnt - 1, max(X[i], Y[i]));
		}
		else{
			qry[i] = pi(mp[pi(X[i], Y[i])], N + 3);
		}
	}
	solve_dmst(C, N, cnt);
	for(int i=0; i<C; i++){
		for(auto &j : query[i]){
			j.first = N - 2 - j.first;
		}
	}
	for(int i=0; i<cnt; i++) E[i].x = N + 3;
	for(int i=0; i<C; i++){
		if(T[i] == 0){
			qry[i].second = N - 1 - min(E[qry[i].first].s, E[qry[i].first].e);
		}
	}
	solve_dmst(C, N, cnt);
	vector<int> ansr(Q);
	for(int i=0; i<Q; i++) ansr[i] = N - ans[i];
	return ansr;
}
