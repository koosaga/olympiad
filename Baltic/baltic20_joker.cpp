#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 400005;

struct event{
	int *p;
	int v;
};

int n, m, q;
pi a[MAXN];

void rollback(vector<event> &E){
	reverse(all(E));
	for(auto &i : E){
		*i.p = i.v;
	}
	E.clear();
}

struct btracker{
	int pa[MAXN], rk[MAXN];
	int is_cycle;
	void init(int n){
		iota(pa, pa + n + 1, 0);
		memset(rk, 0, sizeof(rk));
		is_cycle = 0;
	}
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] > rk[q]) swap(p, q);
		pa[p] = q;
		if(rk[p] == rk[q]) rk[q]++;
		return 1;
	}
	bool uni(int p, int q, vector<event> &snap){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] > rk[q]) swap(p, q);
		snap.push_back((event){&pa[p], pa[p]});
		pa[p] = q;
		if(rk[p] == rk[q]){
			snap.push_back((event){&rk[q], rk[q]});
			rk[q]++;
		}
		return 1;
	}
	void add_edge(int x, int y){
		uni(x, y + n);
		uni(y, x + n);
		if(find(x) == find(x + n)) is_cycle = 1;
	}
	void add_edge(int x, int y, vector<event> &snap){
		uni(x, y + n, snap);
		uni(y, x + n, snap);
		if(find(x) == find(x + n)){
			snap.push_back((event){&is_cycle, is_cycle});
			is_cycle = 1;
		}
	}
}disj;

int dap[MAXN];

void solve(int s, int e, int ps, int pe){
	if(s > e) return;
	int m = (s + e) / 2;
	vector<event> snap1, snap2;
	for(int i = e; i >= m; i--){
		disj.add_edge(a[i].first, a[i].second, snap1);
	}
	for(int i = ps; i <= pe; i++){
		disj.add_edge(a[i].first, a[i].second, snap2);
		if(disj.is_cycle){
			dap[m] = i;
			break;
		}
	}
	rollback(snap2);
	solve(s, m - 1, ps, dap[m]);
	rollback(snap1);
	for(int i = ps; i <= dap[m] - 1; i++){
		disj.add_edge(a[i].first, a[i].second, snap1);
	}
	solve(m + 1, e, dap[m], pe);
	rollback(snap1);
}

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1; i<=m; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		a[i + m] = a[i];
	}
	disj.init(n+n);
	int stpos = -1;
	for(int i=m; i; i--){
		disj.add_edge(a[i].first, a[i].second);
		if(disj.is_cycle){
			stpos = i + 1;
			break;
		}
	}
	if(disj.is_cycle == 0){
		while(q--) puts("NO");
		return 0;
	}
	disj.init(n+n);
	{
		vector<event> v;
		dap[m + 1] = 2 * m + 1;
		for(int j=m + 1; j<=2*m; j++){
			disj.add_edge(a[j].first, a[j].second, v);
			if(disj.is_cycle){
				dap[m + 1] = j;
				break;
			}
		}
		rollback(v);
	}
	solve(stpos, m, m + 1, dap[m + 1]);
	while(q--){
		int x, y; scanf("%d %d",&x,&y);
		if(y + 1 < stpos) puts("YES");
		else puts(dap[y + 1] < x + m? "YES" : "NO");
	}
}
