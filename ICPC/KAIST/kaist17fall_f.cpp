#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 200005;

int n, a[MAXN];
int dpu[MAXN], dpd[MAXN];
int nafn[MAXN], ret[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	dpu[n] = dpd[n] = n;
	for(int i=n-1; i>=1; i--){
		dpu[i] = dpd[i] = i;
		if(a[i] <= a[i+1]) dpu[i] = dpu[i + 1];
		else dpd[i] = dpd[i + 1];
	}
	for(int i=2; i<=n; i++){
		int pos = 1;
		while(pos <= n){
			int maxup = max({dpu[pos], dpd[pos], pos + i - 1}) + 1;
			maxup = min(maxup, n + 1);
			nafn[i] += maxup - max(dpu[pos], dpd[pos]) - 1;
			ret[i]++;
			pos = maxup;
		}
	}
	int q; scanf("%d",&q); 
	while(q--){ 
		int x; scanf("%d",&x); 
		printf("%d %d\n", ret[x], nafn[x]); 
	}
}
