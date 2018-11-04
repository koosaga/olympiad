#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n, m;
struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}a[MAXN * MAXN / 2];

struct disj{
	int pa[MAXN], sz[MAXN], ed[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
		fill(ed, ed + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q){
			ed[p]++;
			return 0;
		}
		else{
			pa[q] = p;
			sz[p] += sz[q];
			ed[p] += ed[q] + 1;
			return 1;
		}
	}
	bool isgood(int v){
		v = find(v);
		if(sz[v] * (sz[v] - 1) == 2 * ed[v]) return 1;
		return 0;
	}
}disj;

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		int p = 0;
		for(int i=0; i<n; i++){
			for(int j=i+1; j<n; j++){
				scanf("%d",&a[p].x);
				a[p].s = i, a[p].e = j;
				p++;
			}
		}
		sort(a, a + p);
		disj.init(n);
		int ans = 0;
		for(int i=0; i<p; ){
			int e = i;
			while(e < p && a[e].x == a[i].x) e++;
			vector<int> v;
			for(int j=i; j<e; j++){
				disj.uni(a[j].s, a[j].e);
				if(disj.isgood(a[j].s)){
					v.push_back(a[j].s);
				}
			}
			for(auto &i : v){
				i = disj.find(i);
			}
			sort(v.begin(), v.end());
			v.resize(unique(v.begin(), v.end()) - v.begin());
			for(auto &i : v){
				if(disj.isgood(i)) ans++;
			}
			i = e;
		}
		printf("%d\n", ans - 1);
	}
}