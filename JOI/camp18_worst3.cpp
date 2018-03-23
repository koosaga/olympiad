#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, q, a[MAXN];
vector<pi> cnd;

int main(){
	scanf("%d %d",&n,&q);
	int prv = 1;
	a[0] = 1;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		prv = ((a[i] - 1) / prv + 1) * prv;
		a[i] = prv;
	}
	for(int i=0; i<=n; ){
		int e = i;
		while(e <= n && a[i] == a[e]) e++;
		cnd.push_back(pi(a[i], e - i));
		i = e;
	}
	while(q--){
		int l, r, t;
		scanf("%d %d %d",&t,&l,&r);
		int curp = t+1;
		int ans = 0, pos = 0;
		for(auto &i : cnd){
			curp -= (curp + pos - 1) % i.first + 1;
			ans += max(0, min(r, curp) - max(l, curp - i.second + 1) + 1);
			curp -= i.second - 1;
			pos += i.second;
		}
		printf("%d\n", ans);
	}
}
