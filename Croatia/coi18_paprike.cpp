#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int MAXN = 100005;

int n, k, a[MAXN];
vector<int> gph[MAXN];
int ans;

int dfs(int x, int p){
	vector<int> v;
	for(auto &i : gph[x]){
		if(i != p) v.push_back(dfs(i, x));
	}
	sort(v.begin(), v.end());
	int ret = a[x];
	for(int i=0; i<v.size(); i++){
		if(ret + v[i] > k){
			ans += v.size() - i;
			return ret;
		}
		ret += v[i];
	}
	return ret;
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	cout << ans << endl;
}
