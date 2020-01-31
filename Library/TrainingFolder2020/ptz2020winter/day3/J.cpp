#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 998244353;

vector<int> gph[MAXN];
int n, m;
int dep[MAXN], vis[MAXN];
int ev, od;

void dfs(int x){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(!vis[i]){
			dep[i] = dep[x] + 1;
			dfs(i);
		}
		else if(dep[i] < dep[x] - 1){
			if(dep[i] % 2 != dep[x] % 2) ev++;
			else od++;
		}
	}
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	for(;p;p>>=1){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
	}
	return ret;
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		for(int i=0; i<m; i++){
			int s, e; scanf("%d %d",&s,&e);
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		int pot = 0;
		for(int i=1; i<=n; i++){
			if(!vis[i]){
				ev = od = 0;
				dfs(i);
				pot += ev + max(0, od - 1);
			}
		}
		int ans = ipow(5, pot);
		printf("%d\n", ans);
		for(int i=0; i<=n; i++){
			gph[i].clear();
			vis[i] = 0;
		}
		ev = od = 0;
	}
}
