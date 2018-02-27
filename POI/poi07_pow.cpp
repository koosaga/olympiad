#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1005;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
};

struct disj{
	int pa[MAXN * MAXN];
	bool fn[MAXN * MAXN];
	void init(int n){
		iota(pa, pa + n, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		fn[p] |= fn[q];
		return 1;
	}
	bool is_mark(int p){ return fn[find(p)]; }
	void do_mark(int p){ fn[find(p)] = 1; }
}disj;

vector<edg> ed;
int n, m, a[MAXN][MAXN];

int getnum(int x, int y){ return x * m + y; }

int main(){
	scanf("%d %d",&n,&m);
	vector<pi> v;
	disj.init(n*m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
			if(a[i][j] > 0) v.push_back(pi(a[i][j], getnum(i, j)));
			else a[i][j] = -a[i][j];
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(j + 1 < m){
				ed.push_back({getnum(i, j), getnum(i, j+1), max(a[i][j], a[i][j+1])});
			}
			if(i + 1 < n){
				ed.push_back({getnum(i, j), getnum(i+1, j), max(a[i][j], a[i+1][j])});
			}
		}
	}
	sort(v.begin(), v.end());
	sort(ed.begin(), ed.end());
	int ans = 0, ptr = 0;
	for(int i=0; i<v.size(); i++){
		while(ptr < ed.size() && ed[ptr].x <= v[i].first){
			disj.uni(ed[ptr].s, ed[ptr].e);
			ptr++;
		}
		if(!disj.is_mark(v[i].second)){
			disj.do_mark(v[i].second);
			ans++;
		}
	}
	cout << ans << endl;
}

