#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, w[1000005], a[1000005], b[1000005];
int nxt[1000005], vis[1000005], cst[1000005];

int main(){
	scanf("%d",&n);
	int wmin = 1e9;
	for(int i=1; i<=n; i++){
		scanf("%d",&w[i]);
		wmin = min(wmin, w[i]);
	}
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		a[x] = i;
	}
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		b[x] = i;
	}
	for(int i=1; i<=n; i++){
		nxt[a[i]] = b[i];
		cst[a[i]] = w[i];
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i] && nxt[i] != i){
			int minv = 1e9;
			lint sum = 0;
			int cnt = 0;
			for(int j=i; !vis[j]; j=nxt[j]){
				minv = min(minv, cst[j]);
				sum += cst[j];
				vis[j] = 1;
				cnt++;
			}
			lint exp1 = sum + 1ll * (cnt - 2) * minv;
			lint exp2 = sum - minv + wmin + 1ll * (cnt - 2) * wmin + 2 * (minv + wmin);
			ret += min(exp1, exp2);
		}
	}
	cout << ret;
}


