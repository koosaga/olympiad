#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, c;
int a[55][55];
int dp[500005];
int main(){
	cin >> n >> m >> c;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> a[i][j];
		}
	}
	for(int i=0; i<m-1; i++){
		for(int j=1; j<=500000; j++){
			dp[j] = dp[j-1] + 1;
			for(int k=0; k<n; k++){
				if(a[k][i] <= j){
					dp[j] = max(dp[j], dp[j - a[k][i]] + a[k][i+1]);
				}
			}
		}
		c = dp[c];
	}
	cout << c;
}
