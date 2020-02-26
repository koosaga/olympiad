#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
 
vector<pi> gph[MAXN];
int n, cnt[MAXN], mcnt[MAXN];
int din[MAXN], dout[MAXN], par[MAXN], pae[MAXN], piv;
lint dx[MAXN];
vector<lint> dis;
 
lint solve_small(){
	if(cnt[1] % 2 == 0){
		lint ans = 0;
		for(int i=2; i<=n; i++){
			if(cnt[i] % 2 == 1) ans += pae[i];
		}
		return ans;
	}
	lint ans = 0;
	for(int i=2; i<=n; i++){
		if(cnt[i] % 2 == 0){
			dx[din[i]] += pae[i];
			dx[dout[i] + 1] -= pae[i];
		}
		else{
			ans += pae[i];
			dx[din[i]] -= pae[i];
			dx[dout[i] + 1] += pae[i];
		}
	}
	for(int i=1; i<=n; i++){
		dx[i] += dx[i-1];
	}
	lint up = 1e18;
	for(int i=1; i<=n; i++){
		if(gph[i].size() == 1) up = min(up, dx[din[i]]);
	}
	return ans + up;
}
 
void dfsl(int x, int p, lint d){
	if(gph[x].size() == 1) dis.push_back(d);
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dfsl(i.second, x, d + i.first);
	}
}
 
void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dfs(i.second, x);
		par[i.second] = x;
		pae[i.second] = i.first;
		cnt[x] += cnt[i.second];
		mcnt[x] = max(mcnt[x], cnt[i.second]);
	}
	dout[x] = piv;
}
 
int main(){
	scanf("%d",&n);
	if(n == 2){
		int x, y, z;
		cin >> x >> y >> z;
		cout << z << " " << z;
		return 0;
	}
	for(int i=1; i<n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e, &x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	for(int i=1; i<=n; i++) cnt[i] = (gph[i].size() == 1);
	dfs(1, 0);
	pi ans(1e9, 1e9);
	for(int i=1; i<=n; i++){
		int mx = max(mcnt[i], cnt[1] - cnt[i]);
		ans = min(ans, pi(mx, i));
	}
	cout << solve_small() << endl;
	dfsl(ans.second, 0, 0);
	lint ans2 = accumulate(dis.begin(), dis.end(), 0ll);
	if(dis.size() % 2) ans2 -= *min_element(dis.begin(), dis.end());
	cout << ans2;
}