#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
typedef pair<int, int> pi;

struct disj{
	int pa[4 * MAXN *MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct tup{
	int x, y, v;
	bool operator<(const tup &t)const{
		return v < t.v;
	}
};

int n, m, a[MAXN][MAXN];
int chk[MAXN][MAXN];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && chk[x][y];
}

int get(int x, int y){ return x * m + y; }

void solve(){
	vector<tup> v;
	disj.init(n * m);
	memset(chk, 0, sizeof(chk));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			v.push_back({i, j, a[i][j]});
		}
	}
	sort(v.rbegin(), v.rend());
	int cmp = 0;
	vector<pi> ans;
	ans.push_back(pi(2e9, 0));
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i].v == v[e].v) e++;
		for(int j=i; j<e; j++){
			cmp++;
			chk[v[j].x][v[j].y] = 1;
			for(int k=0; k<4; k++){
				if(ok(v[j].x + dx[k], v[j].y + dy[k])){
					int v1 = get(v[j].x, v[j].y);
					int v2 = get(v[j].x + dx[k], v[j].y + dy[k]);
					cmp -= disj.uni(v1, v2);
				}
			}
		}
		ans.push_back(pi(v[i].v, cmp));
		i = e;
	}
	sort(ans.begin(), ans.end());
	int q;
	scanf("%d",&q);
	while(q--){
		int x;
		scanf("%d",&x);
		printf("%d ", upper_bound(ans.begin(), ans.end(), pi(x, 1e9))->second);
	}
	puts("");
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				scanf("%d",&a[i][j]);
			}
		}
		solve();
	}
}