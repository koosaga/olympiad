#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;

int n, q, a[MAXN];
lint sum[MAXN][MAXN];
int cnt[2222222];

int main(){
	freopen("threesum.in", "r", stdin);
	freopen("threesum.out", "w", stdout);
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; i++){
		int dap = 0;
		for(int j=i+1; j<=n; j++){
			int neg = -(a[i] + a[j]) + 1000000;
			if(neg <= 2000000 && neg >= 0){
				sum[i][j] = cnt[neg];
			}
			cnt[a[j] + 1000000]++;
		}
		for(int j=i+1; j<=n; j++) cnt[a[j] + 1000000] = 0;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	while(q--){
		int l, r; scanf("%d %d",&l,&r);
		printf("%lld\n", sum[r][r] - sum[l-1][r] - sum[r][l-1] + sum[l-1][l-1]);
	}
}

