#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 2000005;

string s;
int son[MAXN][2], type[MAXN], sz[MAXN]; // min = 0, max = 1
pi dp[MAXN];

int comma[MAXN * 5], mtch[MAXN * 5], piv;

int dfs(int l, int r){
	if(l == r){
		return ++piv;
	}
	int cur = ++piv;
	if(s[l + 2] == 'n') type[cur] = 0;
	else type[cur] = 1;
	son[cur][0] = dfs(l + 4, comma[l + 3] - 1);
	son[cur][1] = dfs(comma[l + 3] + 1, r - 1);
//	cout << "max(" << cur << ") -> " << son[cur][0] << "," << son[cur][1] << "\n";
	return cur;
}

void solve(int x){
	if(son[x][0] == 0 && son[x][1] == 0){
		dp[x] = pi(1, 1);
		sz[x] = 1;
		return;
	}
	solve(son[x][0]);
	solve(son[x][1]);
	sz[x] = sz[son[x][0]] + sz[son[x][1]];
	if(type[x] == 0){
		dp[x].first = min(dp[son[x][0]].first, dp[son[x][1]].first);
		dp[x].second = dp[son[x][0]].second + dp[son[x][1]].second - 1;
	}
	else{
		dp[x].first = dp[son[x][0]].first + dp[son[x][1]].first;
		dp[x].second = max(sz[son[x][1]] + dp[son[x][0]].second, sz[son[x][0]] + dp[son[x][1]].second);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	vector<int> v;
	for(int i = 0; i < sz(s); i++){
		if(s[i] == '('){
			v.push_back(i);
		}
		else if(s[i] == ','){
			comma[v.back()] = i;
		}
		else if(s[i] == ')'){
			mtch[v.back()] = i;
			v.pop_back();
		}
	}
	int r = dfs(0, sz(s) - 1);
	solve(r);
	cout << dp[r].second - dp[r].first + 1 << "\n";
}
