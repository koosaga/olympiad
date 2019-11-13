#include <bits/stdc++.h>
#define sz(v) ((int)((v).size()))
using namespace std;
const int MAXN = 300005;
using lint = long long;
using pi = pair<lint, int>;
 
int n, m, a[MAXN];
 
struct edge{
	int s, e, x;
	lint stack_s, stack_e;
}ed[MAXN];
 
struct disj{
	int pa[MAXN];
	lint sum[MAXN];
	void init(int n, int *a){
		iota(pa, pa + n + 1, 0);
		for(int i=1; i<=n; i++) sum[i] = a[i];
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	lint getsum(int x){ return sum[find(x)]; }
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sum[p] += sum[q];
		return 1;
	}
}disj;
 
priority_queue<int, vector<int>, greater<int> > pq;
priority_queue<pi, vector<pi>, greater<pi> > notify[MAXN];
 
lint cur_thres[MAXN];
 
void refresh_event(int i){
	if(disj.find(ed[i].s) == disj.find(ed[i].e)) return;
	ed[i].stack_s = disj.getsum(ed[i].s);
	ed[i].stack_e = disj.getsum(ed[i].e);
	if(ed[i].stack_s + ed[i].stack_e >= ed[i].x){
		pq.push(i);
	}
	else{
		lint threshold = (ed[i].x - ed[i].stack_s - ed[i].stack_e) + 1;
		threshold /= 2;
		cur_thres[i] = threshold;
		notify[disj.find(ed[i].s)].emplace(threshold + ed[i].stack_s, i);
		notify[disj.find(ed[i].e)].emplace(threshold + ed[i].stack_e, i);
	}
}
 
vector<int> dap;
 
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	disj.init(n, a);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&ed[i].s,&ed[i].e,&ed[i].x);
		refresh_event(i);
	}
	while(!pq.empty()){
		auto x = pq.top(); pq.pop();
		int l = disj.find(ed[x].s);
		int r = disj.find(ed[x].e);
		if(l == r) continue;
		dap.push_back(x);
		if(sz(notify[l]) < sz(notify[r])) swap(l, r);
		disj.uni(l, r);
		vector<pi> v;
		while(!notify[r].empty()){
			v.push_back(notify[r].top());
			notify[r].pop();
		}
		sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
			return pi(a.second, a.first) < pi(b.second, b.first);
		});
		for(int i=0; i<sz(v); i++){
			if(i > 0 && v[i-1].second == v[i].second) continue;
			notify[l].push(v[i]);
		}
		while(!notify[l].empty() && notify[l].top().first <= disj.sum[l]){
			refresh_event(notify[l].top().second);
			notify[l].pop();
		}
	}
	printf("%d\n", sz(dap));
	for(auto &i : dap) printf("%d ", i + 1);
}
