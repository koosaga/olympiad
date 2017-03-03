#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct cht{
	int s, e;
	int pa[1005], pb[1005];
	void clear(){
		s = e = 0;
	}
	void add(int x, int y){
		pa[e] = x;
		pb[e] = y;
		while(e - 2 >= s &&1ll * (pb[e-1] - pb[e-2]) * (pa[e-1] - pa[e]) > 1ll * (pb[e] - pb[e-1]) * (pa[e-2] - pa[e-1])){
			pa[e-1] = pa[e];
			pb[e-1] = pb[e];
			e--;
		}
		e++;
	}
	int query(int x){
		while(s + 1 < e && pa[s] * x + pb[s] >= pa[s+1] * x + pb[s+1]) s++;
		return pa[s] * x + pb[s];
	}
}cht;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x > e.x;
	}
};

const int MAXN = 1000005;
struct disj{
	int pa[MAXN], sz[MAXN];
	void init(int n){
		for(int i=0; i<=n; i++){
			pa[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
}disj;

int n, m;
pi s, e;
int up[1005][1005], dn[1005][1005];
int dis[1005][1005];

int get(int x, int y){
	return (x - 1) * m + y - 1;
}

int main(){
	int k;
	scanf("%d %d",&n,&m);
	scanf("%d %d %d %d",&s.first,&s.second,&e.first,&e.second);
	scanf("%d",&k);
	disj.init(n*m);
	memset(up, -1, sizeof(up));
	memset(dn, -1, sizeof(dn));
	for(int i=0; i<k; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		up[x][y] = dn[x][y] = x;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(up[i][j] == -1){
				up[i][j] = up[i-1][j];
			}
			if(dn[n+1-i][j] == -1){
				dn[n+1-i][j] = dn[n+2-i][j];
			}
		}
	}
	for(int i=1; i<=n; i++){
		cht.clear();
		for(int j=1; j<=m; j++){
			int dy = 1e4;
			if(~up[i][j]) dy = min(dy, i - up[i][j]);
			if(~dn[i][j]) dy = min(dy, dn[i][j] - i);
			if(dy < 2000){
				cht.add(-2 * j, dy * dy + j * j);
			}
		}
		for(int j=1; j<=m; j++){
			dis[i][j] = cht.query(j) + j * j;
		}
	}
	if(s == e){
		printf("%d\n", dis[s.first][s.second]);
		return 0;
	}
	vector<edg> v;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(j < m) v.push_back((edg){get(i, j), get(i, j+1), min(dis[i][j], dis[i][j+1])});
			if(i < n) v.push_back((edg){get(i, j), get(i+1, j), min(dis[i][j], dis[i+1][j])});
		}
	}
	sort(v.begin(), v.end());
	for(int ii=0; ii<v.size(); ii++){
		edg i = v[ii];
		disj.uni(i.s, i.e);
		if(disj.find(get(s.first, s.second)) == disj.find(get(e.first, e.second))){
			printf("%d", i.x);
			return 0;
		}
	}
}
