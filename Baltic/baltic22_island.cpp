#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

set<pi> s;
struct disj{
	int pa[MAXN];
	lint sz[MAXN];
	vector<int> memb[MAXN];
	void init(int n, vector<lint> &a){
		for(int i = 0; i < n; i++){
			pa[i] = i;
			sz[i] = a[i];
			memb[i].push_back(i);
		}
	}
	void activate(int x){
		assert(pa[x] == x);
		s.emplace(sz[x], x);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(sz(memb[p]) < sz(memb[q])) swap(p, q);
		if(s.count(pi(sz[p], p))) s.erase(pi(sz[p], p));
		if(s.count(pi(sz[q], q))) s.erase(pi(sz[q], q));
		pa[q] = p;
		sz[p] += sz[q];
		for(auto &x : memb[q]) memb[p].push_back(x);
		s.insert(pi(sz[p], p));
		return 1;
	}
}disj;

vector<int> gph[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<lint> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++){
		int s, e; cin >> s >> e;
		s--; e--;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	vector<int> idx(n);
	iota(all(idx), 0);
	sort(all(idx), [&](const int &p, const int &q){
		return a[p] < a[q];
	});
	disj.init(n, a);
	vector<int> ans(n, 1);
	for(int i = 0; i < n; ){
		int j = i;
		while(j < n && a[idx[j]] == a[idx[i]]) j++;
		if(j == n) break;
		for(int k = i; k < j; k++){
			disj.activate(idx[k]);
		}
		for(int k = i; k < j; k++){
			for(auto &x : gph[idx[k]]){
				if(a[x] <= a[idx[k]]) disj.uni(x, idx[k]);
			}
		}
		while(sz(s) && s.begin()->first < a[idx[j]]){
			int pos = s.begin()->second;
			s.erase(s.begin());
			for(auto &j : disj.memb[pos]){
				ans[j] = 0;
			}
			disj.memb[pos].clear();
		}
		i = j;
	}
	for(auto &i : ans) cout << i;
}
