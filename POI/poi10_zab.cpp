#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k;
lint m, a[1000005];
int nxt[1000005], tmp[1000005], ans[1000005];

int main(){
	scanf("%d %d %lld",&n,&k,&m);
	for(int i=0; i<n; i++){
		scanf("%lld",&a[i]);
		ans[i] = i;
	}
	int s = 0, e = k;
	for(int i=0; i<n; i++){
		while(e+1 < n && a[e+1] - a[i] < a[i] - a[s]){
			e++;
			s++;
		}
		if(a[e] - a[i] > a[i] - a[s]) nxt[i] = e;
		else nxt[i] = s;
	}
	while(m){
		if(m & 1) for(int j=0; j<n; j++) ans[j] = nxt[ans[j]];
		m >>= 1;
		for(int j=0; j<n; j++) tmp[j] = nxt[nxt[j]]; 
		memcpy(nxt, tmp, sizeof(tmp));
	}
	for(int i=0; i<n; i++) printf("%d ", ans[i] + 1);
}
