#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
const int MAXN = 1005;

int n, m;
vector<int> gph[MAXN];
int par[MAXN], chk[MAXN], inpath[MAXN];

pi dfs(int x, int p = -1){
	pi ret(0, x);
	for(auto &y : gph[x]){
		if(y != p){
			par[y] = x;
			auto z = dfs(y, x);
			z.first++;
			ret = max(ret, z);
		}
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	if(m != n - 1){
		puts("NO");
		return 0;
	}
	if(n == 1){
		puts("YES\n1\n1");
		return 0;
	}
	if(n == 2){
		puts("YES\n2\n1 1");
		return 0;
	}
	for(int i = 0; i < n - 1; i++){
		int s, e; cin >> s >> e;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int u = dfs(1).second;
	int v = dfs(u).second;
	for(int i = v; ; i = par[i]){
		chk[i] = 1;
		inpath[i] = 1;
		for(auto &j : gph[i]){
			chk[j] = 1;
			for(auto &k : gph[j]){
				chk[k] = 1;
			}
		}
		if(i == u) break;
	}
	if(count(chk + 1, chk + n + 1, 0)){
		puts("NO");
		return 0;
	}
	vector<int> ans;
	for(int i = par[v]; i != u; i = par[i]){
		ans.push_back(i);
		for(auto &j : gph[i]){
			if(sz(gph[j]) == 1 || inpath[j]) continue;
			ans.push_back(j);
			ans.push_back(i);
		}
	}
	printf("YES\n%d\n", 2 * sz(ans));
	for(auto &i : ans) printf("%d ", i);
	reverse(all(ans));
	for(auto &i : ans) printf("%d ", i);
}
