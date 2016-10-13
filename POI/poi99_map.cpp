#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
lint cost[3005][3005];
lint dp[11][3005];
int a[3005];

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++) cin >> a[i];
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++){
		priority_queue<int> pql;
		priority_queue<int, vector<int>, greater<int> > pqh;
		lint sumhi = 0, sumlo = 0;
		for(int j=i; j; j--){
			if(!pql.empty() && pql.top() >= a[j]){
				pql.push(a[j]);
				sumlo += a[j];
			}
			else{
				pqh.push(a[j]);
				sumhi += a[j];
			}
			if((int)pqh.size() - (int)pql.size() > 1){
				int x = pqh.top();
				pqh.pop();
				sumhi -= x;
				sumlo += x;
				pql.push(x);
			}
			if((int)pql.size() - (int)pqh.size() > 1){
				int x = pql.top();
				pql.pop();
				sumhi += x;
				sumlo -= x;
				pqh.push(x);
			}
			int med = a[(i+j)/2];
			cost[j][i] = sumhi - 1ll * med * pqh.size() + (1ll * med * pql.size() - sumlo);
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n; j++){
			for(int k=0; k<j; k++){
				dp[i][j] = min(dp[i][j], dp[i-1][k] + cost[k+1][j]);
			}
		}
	}
	cout << dp[m][n];
}

