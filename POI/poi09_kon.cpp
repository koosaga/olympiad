#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, k, a[605][605];
lint dp[55][605];
int opt[55][605];

lint getsum(int s, int e){
	return a[e][e] - a[s-1][e] - a[e][s-1] + a[s-1][s-1];
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++) scanf("%d",&a[i][j]);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
		}
	}
	for(int i=1; i<n; i++){
		dp[1][i] = getsum(1, i);
	}
	for(int i=2; i<=k; i++){
		for(int j=1; j<n; j++){
			dp[i][j] = 2e9 + 100;
			for(int k=1; k<j; k++){
				if(dp[i][j] > dp[i-1][k] + getsum(k+1, j)){
					dp[i][j] = dp[i-1][k] + getsum(k+1, j);
					opt[i][j] = k;
				}
			}
		}
	}
	int ret = 2e9 + 100, pos = -1;
	for(int i=1; i<n; i++){
		if(ret > dp[k][i] + getsum(i+1, n)){
			ret = dp[k][i] + getsum(i+1, n);
			pos = i;
		}
	}
	vector<int> v;
	for(int i=1; i<=k; i++){
		v.push_back(pos);
		pos = opt[k+1-i][pos];
	}
	reverse(v.begin(), v.end());
	for(auto &i : v){
		printf("%d ", i);
	}
}
