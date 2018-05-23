#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, piv, a[MAXN];
int vis[MAXN], deg[MAXN];
vector<int> gph[MAXN];
vector<int> dfn;

void dfs(int x){
	if(vis[x]) return;
	dfn.push_back(x);
	vis[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
	}
}

pi dp(int x, int p){
	int mat = 0;
	int ans = 0;
	for(auto &i : gph[x]){
		if(i != p && !deg[i]){
			auto k = dp(i, x);
			ans += k.first;
			if(k.second) mat = 1;
		}
	}
	if(mat) return pi(ans + 1, 0);
	return pi(ans, 1);
}

int solve(int r){
	dfn.clear();
	dfs(r);
	queue<int> que;
	for(auto &i : dfn) if(!deg[i]) que.push(i);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[a[x]]--;
		if(deg[a[x]] == 0) que.push(a[x]);
	}
	for(auto &i : dfn){
		if(deg[i]){
			vector<int> cyc = {i};
			for(int j=a[i]; j!=i; j=a[j]) cyc.push_back(j);
			if(cyc.size() == 1){
				return dfn.size()-dp(i, -1).first;
			}
			if(cyc.size() == 2){
				int ans = 2;
				for(auto &i : cyc){
					for(auto &j : gph[i]){
						if(!deg[j]) ans += dp(j, i).first;
					}
				}
				return dfn.size()-ans;
			}
			if(cyc.size() > 2){
				vector<int> tmp;
				int ans = 0;
				for(auto &i : cyc){
					auto k = dp(i, -1);
					ans += k.first;
					tmp.push_back(!k.second);
				}
				int fuck = 0;
				for(int i=0; i<2; i++){
					int tans = 0;
					for(int i=0; i+1<tmp.size(); i++){
						if(tmp[i] + tmp[i+1] == 0){
							i++;
							tans++;
						}
					}
					rotate(tmp.begin(), tmp.begin() + 1, tmp.end());
					fuck = max(fuck, tans);
				}
				ans += fuck;
				return dfn.size() - ans;
			}
		}
	}
	assert(0);
}

map<string, int> mp;
int tok(string s){
	if(mp.find(s) == mp.end()) mp[s] = piv++;
	return mp[s];
}

int main(){
	scanf("%d",&n);
	if(n % 2 == 1){
		puts("-1");
		return 0;
	}
	for(int i=0; i<n; i++){
		string l, r;
		cin >> l >> r;
		int pl = tok(l);
		int pr = tok(r);
		a[pl] = pr;
		deg[pr]++;
		if(pl != pr){
			gph[pl].push_back(pr);
			gph[pr].push_back(pl);
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++){
		if(!vis[i]){
			ans += solve(i);
		}
	}
	cout << ans << endl;
}
