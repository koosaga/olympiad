#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;
using lint = long long;

int n, m;

vector<vector<int>> arr;
vector<vector<int>> dp;
vector<vector<int>> foo;

void dfs(int x, int y, int t){
	if(foo[x][y]) return;
	foo[x][y] = 1;
	if(x > 0 && dp[x-1][y] >= t) dfs(x-1, y, t);
	if(x < n-1 && dp[x+1][y] >= t) dfs(x+1, y, t);
	if(y > 0 && dp[x][y-1] >= t) dfs(x, y-1, t);
	if(y < m-1 && dp[x][y+1] >= t) dfs(x, y+1, t);
}

bool trial(int x){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(dp[i][j] >= x){
				dfs(i, j, x);
				bool ans = 1;
				vector<pi> v;
				for(int k = n-1; k >= 0; k--){
					for(int l = m-1; l >= 0; l--){
						if(foo[k][l]){
							v.emplace_back(k, l);
							foo[k][l] = 0;
						}
					}
				}
				for(auto &[k, l] : v){
					foo[max(k-x+1, 0)][max(l-x+1, 0)] += 1;
					if(l + 1 < m) foo[max(k-x+1, 0)][l+1] -= 1;
					if(k + 1 < n) foo[k+1][max(l-x+1, 0)] -= 1;
					if(k + 1 < n && l + 1 < m) foo[k+1][l+1] += 1;
				}
				for(int k = 0; k < n; k++){
					for(int l = 0; l < m; l++){
						if(k) foo[k][l] += foo[k-1][l];
						if(l) foo[k][l] += foo[k][l-1];
						if(k&&l) foo[k][l] -= foo[k-1][l-1];
						if(foo[k][l] == 0 && !arr[k][l]){
							ans = 0;
						}
					}
				}
				for(int k = 0; k < n; k++){
					for(int l = 0; l < m; l++){
						foo[k][l] = 0;
					}
				}
				return ans;
			}
		}
	}
	return 0;
}

int main(){
	int k;
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 0; i < n; i++){
		vector<int> v(m);
		arr.push_back(v);
		dp.push_back(v);
		foo.push_back(v);
	}
	while(k--){
		int i, j; scanf("%d %d",&i,&j);
		arr[i-1][j-1] = 1;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(arr[i][j] == 1) dp[i][j] = 0;
			else{
				if(i == 0 || j == 0) dp[i][j] = 1;
				else dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
			}
		}
	}
	int s = 0, e = min(n, m);
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	if(s == 0) s = -1;
	cout << s << endl;
}
