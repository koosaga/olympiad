#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
using lint = long long;

int n, deg[MAXN], lo[MAXN], hi[MAXN];
char buf[MAXN * 10];

lint binom(int x, int y){
	y = min(y, x - y);
	lint ans = 1;
	for(int i=1; i<=y; i++){
		ans *= x + 1 - i;
		ans /= i;
	}
	return ans;
}

int main(){
	scanf("%d\n",&n);
	for(int i=0; i<n; i++){
		fgets(buf, 50000, stdin);
		sscanf(buf, "%d", &deg[i]);
	}
	sort(deg, deg + n);
	int tot = accumulate(deg, deg + n, 0);
	memset(lo, 0x3f, sizeof(lo));
	for(int i=0; i<n; i++){
		lo[deg[i]] = min(lo[deg[i]], i);
		hi[deg[i]] = max(hi[deg[i]], i);
	}
	int l = 0, r = tot;
	lint ans = 0;
	for(int i=0; i<n-1; i++){
		l += deg[i];
		r -= deg[i];
		if(r - l == (n - i - 1) * (n - i - 2)){
			int totcnt = hi[deg[i]] - lo[deg[i]] + 1;
			int partcnt = i - lo[deg[i]] + 1;
			ans += binom(totcnt, partcnt);
		}
	}
	cout << ans << endl;
}
