#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

int n, a[MAXN], chk[MAXN];

int main(){
	freopen("hell.in", "r", stdin);
	freopen("hell.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	lint sum = accumulate(a + 1, a + n + 1, 0ll);
	if(sum % 2 == 1){
		puts("No");
		return 0;
	}
	puts("Yes");
	sum /= 2;
	for(int i=n; i; i--){
		if(sum >= a[i]){
			sum -= a[i];
			chk[i] = 1;
		}
		else chk[i] = -1;
	}
	for(int i=1; i<=n; i++) printf("%d ", chk[i]);
}
