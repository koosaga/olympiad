#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[1005], aux[1005], pos[1005];
int dp[1005][1005], nxt[1005][1005];
int chk[1005];

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> aux[i];
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(aux[j] >= aux[i]) a[i]++;
		}
	}
	a[n+1] = n+1;
	n++;
	for(int i=1; i<=n; i++) pos[a[i]] = i;
	memset(dp, 0x3f, sizeof(dp));
	dp[n][n] = 0;
	for(int i=n-1; i; i--){
		int p1 = 1, p2 = 1;
		for(int j=1; j<i; j++){
			if(pos[j] < pos[i]) p1++;
		}
		for(int j=1; j<=n; j++){
			dp[i][j] = dp[i+1][j] + p1 + p2;
			nxt[i][j] = j;
			if(a[j] < i) p2++;
		}
		int cost = 0;
		for(int j=pos[i]+1; j<=n; j++){
			if(dp[i][pos[i]] > dp[i+1][j] + cost){
				dp[i][pos[i]] = dp[i+1][j] + cost;
				nxt[i][pos[i]] = j;
			}
			if(a[j] < i) cost += i - a[j];
		}
	}
	int tmp = 1e9, tra = 0;
	for(int i=1; i<=n; i++){
		if(tmp > dp[1][i]){
			tmp = dp[1][i];
			tra = i;
		}
	}
	for(int i=1; i<=n; i++){
		if(nxt[i][tra] != tra){
			chk[i] = 1;
		}
		tra = nxt[i][tra];
	}
	vector<pi> dap;
	for(int i=n-1; i; i--){
		if(!chk[i]){
			int st = -1, ed = -1;
			for(int j=1; j<=n; j++){
				if(a[j] == i) st = j;
				if(a[j] == i+1) ed = j;
			}
			if(st < ed){
				ed--;
				dap.push_back({st, ed});
				for(int j=st; j<ed; j++){
					a[j] = a[j+1];
				}
				a[ed] = i;
			}
			else{
				dap.push_back({st, ed});
				for(int j=st; j>ed; j--){
					a[j] = a[j-1];
				}
				a[ed] = i;
			}
		}
	}
	cout << dap.size() << endl;
	for(auto &i : dap) cout << i.first << " " << i.second << endl;
}
