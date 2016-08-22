#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const lint inf = 1e9 + 5;

int n, m, k, a[1000005];
int st[1000005], ed[1000005];
vector<int> gph[1000005];

void dfs(int x, int p, lint s, lint e){
	st[x] = s, ed[x] = e;
	s *= gph[x].size() - 1;
	e *= gph[x].size() - 1;
	s = min(s, inf);
	e = min(e, inf);
	for(auto &i : gph[x]){
		if(i != p) dfs(i, x, s, e);
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<m; i++) scanf("%d",&a[i]);
	sort(a, a+m);
	int r1 = -1, r2 = -1;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(i == 0) tie(r1, r2) = pi(s, e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(r1, r2, k, k+1);
	dfs(r2, r1, k, k+1);
	lint ret = 0;
	for(int i=1; i<=n; i++){
		if(gph[i].size() == 1){
			ret += lower_bound(a, a+m, ed[i]) - lower_bound(a, a+m, st[i]);
		}
	}
	cout << ret * k;
}
