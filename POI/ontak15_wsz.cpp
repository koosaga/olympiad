#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int chk[200005], n, m, p;
int vis[200005];

vector<int> gph[200005];
vector<int> v;

int dp[200005][2];
void dfs(int x, int p){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(i != p) dfs(i, x);
	}
	if(chk[x]){
		for(auto &i : gph[x]){
			if(i != p) dp[x][1] += dp[i][0];
		}
		dp[x][0] = 1;
		for(auto &i : gph[x]){
			if(i != p) dp[x][0] += min(dp[i][0], dp[i][1]);
		}
	}
	else{
		int s1 = 0, s2 = 1, up = 0;
		for(auto &i : gph[x]){
			if(i != p){
				s1 += dp[i][0];
				s2 += min(dp[i][0], dp[i][1]);
			}
		}
		dp[x][0] = min(s1, s2);
		for(auto &i : gph[x]){
			if(i != p){
				dp[x][1] += dp[i][0];
				up = min(up, dp[i][1] - dp[i][0]);
			}
		}
		dp[x][1] += up;
	}
}

void trace(int x, int p, int d){
	if(chk[x]){
		if(d == 0){
			v.push_back(x);
			for(auto &i : gph[x]){
				if(i != p){
					if(dp[i][0] <= dp[i][1]) trace(i, x, 0);
					else trace(i, x, 1);
				}
			}
		}
		else{
			for(auto &i : gph[x]){
				if(i != p) trace(i, x, 0);
			}
		}
	}
	else{
		if(d == 0){
			int s1 = 0, s2 = 1;
			for(auto &i : gph[x]){
				if(i != p){
					s1 += dp[i][0];
					s2 += min(dp[i][0], dp[i][1]);
				}
			}
			if(s1 <= s2){
				for(auto &i : gph[x]){
					if(i != p) trace(i, x, 0);
				}
			}
			else{
				v.push_back(x);
				for(auto &i : gph[x]){
					if(i != p){
						if(dp[i][0] <= dp[i][1]) trace(i, x, 0);
						else trace(i, x, 1);
					}
				}
			}
		}
		else{
			int up = 0, upp = -1;
			for(auto &i : gph[x]){
				if(i != p){
					if(up >= dp[i][1] - dp[i][0]){
						up = dp[i][1] - dp[i][0];
						upp = i;
					}
				}
			}
			for(auto &i : gph[x]){
				if(i != p){
					if(upp == i) trace(i, x, 1);
					else trace(i, x, 0);
				}
			}
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&p);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(s == p) chk[e]++;
		else if(e == p) chk[s]++;
		else{
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
	}
	for(int i=1; i<=n; i++){
		if(chk[i] >= 2){
			v.push_back(i);
			gph[i].clear();
		}
		else{
			vector<int> w = gph[i];
			gph[i].clear();
			for(auto &j : w){
				if(chk[j] <= 1) gph[i].push_back(j);
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dfs(i, -1);
			if(dp[i][0] <= dp[i][1]){
				trace(i, -1, 0);
			}
			else{
				trace(i, -1, 1);
			}
		}
	}
	cout << v.size() << endl;
	sort(v.begin(), v.end());
	for(auto &i : v){
		printf("%d ", i);
	}
}
