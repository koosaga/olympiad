#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 755;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct disj{
	int pa[MAXN * MAXN];
	int cnt[MAXN * MAXN];
	int sz[MAXN * MAXN];
	void init(){
		iota(pa, pa + MAXN * MAXN, 0);
		fill(sz, sz + MAXN * MAXN, 1);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		cnt[p] += cnt[q];
		sz[p] += sz[q];
		return 1;
	}
}disj;

int n, dap, a[MAXN][MAXN];
pi pos[MAXN * MAXN];
int compCnt[MAXN * MAXN];

int val(int x, int y){ return x * (n + 2) + y; }
vector<int> v;

int main(){
	freopen("valleys.in", "r", stdin);
	freopen("valleys.out", "w", stdout);
	scanf("%d",&n);
	memset(a, 0x3f, sizeof(a));
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d",&a[i][j]);
			v.push_back(a[i][j]);
		}
	}
	v.push_back(-1);
	sort(v.begin(), v.end());
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			a[i][j] = lower_bound(v.begin(), v.end(), a[i][j]) - v.begin();
			pos[a[i][j]] = pi(i, j);
		}
	}
	disj.init();
	for(int i=0; i<n+1; i++){
		disj.uni(val(0, i), val(0, i+1));
		disj.uni(val(n+1, i), val(n+1, i+1));
		disj.uni(val(i, 0), val(i+1, 0));
		disj.uni(val(i, n+1), val(i+1, n+1));
	}
	for(int i=n*n; i; i--){
		compCnt[i] = compCnt[i + 1] + 1;
		int x, y; tie(x, y) = pos[i];
		for(int j=-1; j<=1; j++){
			for(int k=-1; k<=1; k++){
				if(a[x+j][y+k] > a[x][y]){
					compCnt[i] -= disj.uni(val(x+j, y+k), val(x, y));
				}
			}
		}
	}
	disj.init();
	lint dap = 0;
	for(int i=1; i<=n*n; i++){
		int delta = compCnt[i+1] - compCnt[i];
		int x, y; tie(x, y) = pos[i];
		for(int j=0; j<4; j++){
			if(x + dx[j] >= 1 && x + dx[j] <= n && y + dy[j] >= 1 && y + dy[j] <= n && a[x+dx[j]][y+dy[j]] < a[x][y]){
				disj.uni(val(x, y), val(x + dx[j], y + dy[j]));
			}
		}
		disj.cnt[disj.find(val(x, y))] += delta;
		if(disj.cnt[disj.find(val(x, y))] == 0){
	//		cout << disj.sz[disj.find(val(x, y))] << endl;
			dap += disj.sz[disj.find(val(x, y))];
		}
	}
	cout << dap << endl;
}
