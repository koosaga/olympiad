#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
int n, a[1000005];
lint b[1000005];
 
pi l[1000005], r[1000005];
int sl, sr;
int query(int h){
	sl = sr = 0;
	for(int i=0; i<=n; i++){
		if(sl == 0 || l[sl-1].first > b[i] - 1ll * i * h){
			l[sl] = {b[i] - 1ll * i * h, i};
			sl++;
		}
	}
	for(int i=n; i>=0; i--){
		if(sr == 0 || r[sr-1].first < b[i] - 1ll * i * h){
			r[sr] = {b[i] - 1ll * i * h, i};
			sr++;
		}
	}
	int pt = 0;
	int ret = 0;
	for(int i=sr-1; i>=0; i--){
		while(pt < sl && l[pt].first > r[i].first){
			pt++;
		}
		if(pt < sl) ret = max(1ll * ret, r[i].second - l[pt].second);
	}
	return ret;
}
 
int main(){
	int q;
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		b[i] = b[i-1] + a[i];
	}
	while(q--){
		int x;
		scanf("%d",&x);
		printf("%d ", query(x));
	}
}