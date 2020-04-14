#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int n, m;
int cnt[405][405];
int dp[205][205][205];

int main(){
	scanf("%d",&n);
	const lint r[2] = {9705276, 12805858};
	vector<pi> v;
	for(int i=0; i<n; i++){
		double x; cin >> x;
		lint y = (lint)round(1e5 * x);
		for(int i=0; i<=400; i++){
			if(y - r[0] * i >= 0 && (y - r[0] * i) % r[1] == 0){
				int x = i;
				int yy = (y - r[0] * i) / r[1];
				v.emplace_back(x, yy);
				break;
			}
		}
	}
	sort(all(v), [&](const pi &a, const pi &b){
		return a.first * r[0] + a.second * r[1] < 
		b.first * r[0] + b.second * r[1];
	});
	n = v.back().first;
	m = v.back().second;
	for(auto &i : v){
		int x = i.first, y = i.second;
		if(2 * (x + y) > n + m){
			x = n - x, y = m - y;
		}
		if(x >= 0 && x <= n && y >= 0 && y <= m){
			cnt[x][y]++;
		}
	}
	for(int i=0; i<205; i++){
		for(int j=0; j<205; j++){
			for(int k=0; k<205; k++){
				dp[i][j][k] = -1e9;
			}
		}
	}
	dp[0][0][0] = cnt[0][0];
	for(int i=1; i<=(n+m)/2; i++){
		for(int j=0; j<=i; j++){
			for(int k=0; k<=i; k++){
				dp[i][j][k] = dp[i-1][j][k];
				if(j) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k]);
				if(k) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1]);
				if(j&&k) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k-1]);
				if(j == k) dp[i][j][k] += cnt[j][i-j];
				else dp[i][j][k] += cnt[j][i-j] + cnt[k][i-k];
			}
		}
	}
	string L, R;
	auto trace = [&](pi p){
		int j = p.first, k = p.second;
		for(int i = (n+m)/2; i>0; i--){
			if(j == k) dp[i][j][k] -= cnt[j][i-j];
			else dp[i][j][k] -= cnt[j][i-j] + cnt[k][i-k];
			if(dp[i][j][k] == dp[i-1][j][k]){
				L.push_back('Q');
				R.push_back('Q');
			}
			else if(j && dp[i][j][k] == dp[i-1][j-1][k]){
				j--;
				L.push_back('P');
				R.push_back('Q');
			}
			else if(k && dp[i][j][k] == dp[i-1][j][k-1]){
				k--;
				L.push_back('Q');
				R.push_back('P');
			}
			else if(j && k && dp[i][j][k] == dp[i-1][j-1][k-1]){
				j--; k--;
				L.push_back('P');
				R.push_back('P');
			}
		}
		reverse(all(L));
	};
	if((n + m) % 2 == 0){
		int dap = -1;
		pi dpos(-1, -1);
		for(int i=0; i<=(n+m)/2; i++){
			int x1 = i;
			int y1 = (n+m)/2 - i;
			int x2 = n - x1;
			int y2 = m - y1;
			if(x1 <= n && y1 <= m){
				if(dap < dp[(n+m)/2][x1][x2]){
					dap = max(dap, dp[(n+m)/2][x1][x2]);
					dpos = pi(x1, x2);
				}
			}
		}
		trace(dpos);
		cout << L << R << endl;
	}
	else{
		int dap = -1;
		pi dpos(-1, -1);
		int foo = -1;
		for(int i=0; i<=(n+m)/2; i++){
			int x1 = i;
			int y1 = (n+m)/2 - i;
			int x2 = n - x1;
			int y2 = m - y1;
			if(x1 <= n && y1 <= m && y2 > 0){
				if(dap < dp[(n+m)/2][x1][x2]){
					dap = max(dap, dp[(n+m)/2][x1][x2]);
					dpos = pi(x1, x2);
					foo = 0;
				}
			}
			if(x1 <= n && y1 <= m && x2 > 0){
				if(dap < dp[(n+m)/2][x1][x2-1]){
					dap = max(dap, dp[(n+m)/2][x1][x2-1]);
					dpos = pi(x1, x2-1);
					foo = 1;
				}
			}
		}
		trace(dpos);
		cout << L;
		if(!foo) putchar('Q');
		else putchar('P');
		cout << R << endl;
	}
}
