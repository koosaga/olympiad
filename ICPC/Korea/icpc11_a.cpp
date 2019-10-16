#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n, m;
struct rect{
	int sx, ex, sy, ey;
	bool operator<(const rect &r)const{
		return sx < r.sx;
	}
}a[MAXN];

int dp[MAXN];

bool Do(){
	sort(a, a + n);
	for(int i=0; i<n; i++){
		dp[i] = 0;
		for(int j=0; j<i; j++){
			if(max(a[i].sy, a[j].sy) < min(a[i].ey, a[j].ey)){
				dp[i] = max(dp[i], dp[j]);
			}
		}
		dp[i] += a[i].ex - a[i].sx;
	}
	bool ret = 0;
	for(int i=0; i<n; i++){
		int del = a[i].ex - dp[i];
		a[i].sx -= del; a[i].ex -= del;
		if(del > 0) ret = 1;
	}
	return ret;
}

int main(){
	int t; scanf("%d\n",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d %d %d %d",&a[i].sx,&a[i].sy,&a[i].ex,&a[i].ey);
		}
		while(1){
			for(int i=0; i<n; i++){
				swap(a[i].sx, a[i].sy);
				swap(a[i].ex, a[i].ey);
			}
			bool good = Do();
			for(int i=0; i<n; i++){
				swap(a[i].sx, a[i].sy);
				swap(a[i].ex, a[i].ey);
			}
			good |= Do();
			if(!good) break;
		}
		int rx = 0, ry = 0;
		for(int i=0; i<n; i++) rx = max(rx, a[i].ex), ry = max(ry, a[i].ey);
		printf("%d %d\n", rx, ry);
	}
}
