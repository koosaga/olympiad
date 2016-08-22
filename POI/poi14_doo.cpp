#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[1000005];
int nxt[1000005], bef[1000005], dpnxt[1000005], ret[1000005];

int query(int x){
	int sum = 0, pnt = 1;
	for(int i=1; i<=n; i++){
		while(sum + a[pnt] <= x){
			sum += a[pnt];
			pnt++;
			if(pnt > n) pnt = 1; 
		}
		nxt[i] = pnt;
		sum -= a[i];
	}
	sum = 0, pnt = n;
	for(int i=n; i>=1; i--){
		while(sum + a[pnt-1] <= x){
			sum += a[pnt-1];
			pnt--;
			if(pnt == 0) pnt = n;
		}
		bef[i] = pnt;
		sum -= a[i-1];
	}
	for(int i=1; i<=n; i++){
		if(bef[i] >= i){
			ret[i] = 0;
		}
		else{
			ret[i] = ret[bef[i]] + 1;
		}
	}
	for(int i=n; i; i--){
		if(nxt[i] <= i){
			dpnxt[i] = 0;
		}
		else{
			dpnxt[i] = dpnxt[nxt[i]] + 1;
		}
		ret[i] += dpnxt[i];
	}
	for(int i=1; i<=n; i++){
		if(bef[i] >= i) bef[i] = i;
		else bef[i] = bef[bef[i]];
	}
	for(int i=n; i; i--){
		if(nxt[i] <= i) dpnxt[i] = i;
		else dpnxt[i] = dpnxt[nxt[i]];
	}
	int dap = 1e9;
	for(int i=1; i<=n; i++){
		int s = i, e = i;
		s = dpnxt[s];
		e = bef[e];
		s = nxt[s]; 	
		ret[i]++;
		while(s < e) s = nxt[s], ret[i]++;
		dap = min(dap, ret[i]);
	}
	return dap;
}

int main(){
	int s, maxv = 0, sum = 0;
	scanf("%d %d",&n,&s);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		sum += a[i];
		maxv = max(maxv, a[i]);
	}
	a[0] = a[n];
	while(s--){
		int x;
		scanf("%d",&x);
		if(x >= sum){
			puts("1");
			continue;
		}
		if(x < maxv){
			puts("NIE");
			continue;
		}
		printf("%d\n", query(x));
	}
}
