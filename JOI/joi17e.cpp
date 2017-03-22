#include <bits/stdc++.h>
typedef long long lint;
typedef long double llf;
using namespace std;
typedef pair<int, int> pi;

int n, m, a[1000005];
int ans[1000005], occ[1000005], chk[1000005];
vector<int> pnt[1000005];

void solve(int s, int e){
	if(e - s + 1 < 0) return;
	for(int i=1; i<=m; i++) pnt[i].clear();
	if(s > 1) pnt[a[s-1]].push_back(a[s-1]);
	if(e < n) pnt[a[e+1]].push_back(a[e+1]);
	for(int i=s+1; i<=e; i+=2){
		if(a[i-1] == a[i]){
			pnt[a[i]].push_back(a[i]);
			pnt[a[i]].push_back(a[i]);
		}
		else{
			int x = a[i-1], y = a[i];
			pnt[x].push_back(x);
			pnt[x].push_back(y);
			pnt[y].push_back(x);
			pnt[y].push_back(y);
		}
	}
	vector<pi> v;
	for(int i=1; i<=m; i++) v.push_back(pi(occ[i], i));
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	for(int i=1; i<=m; i++){
		int cur = -1e9;
		for(auto &j : pnt[i]) chk[j]++;
		for(auto &j : v){
			cur = max(cur, j.first - chk[j.second]);
			if(!chk[j.second]) break;
		}
		for(auto &j : pnt[i]) chk[j]--;
		ans[i] = min(ans[i], n - occ[i] - cur);
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	memset(ans, 0x3f, sizeof(ans));
	for(int i=1; i<=n; i++) occ[a[i]]++;
	if(n % 2 == 0) solve(1, n), solve(2, n-1);
	else solve(1, n-1), solve(2, n);
	for(int i=1; i<=m; i++) printf("%d\n", ans[i]);
}
