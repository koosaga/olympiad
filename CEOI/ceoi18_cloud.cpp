#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

struct ord{
	int c, f, v;
	bool operator<(const ord &o)const{
		return pi(o.f, o.c) < pi(f, c);
	}
}a[4005];

lint dp[MAXN];

int main(){
	int n, m;
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].c >> a[i].f >> a[i].v;
		a[i].v *= -1;
	}
	cin >> m;
	for(int i=n; i<n+m; i++){
		cin >> a[i].c >> a[i].f >> a[i].v;
		a[i].c *= -1;
	}
	sort(a, a+n+m);
	fill(dp + 1, dp + MAXN, -1e18);
	for(int i=0; i<n+m; i++){
		lint nxt[MAXN];
		for(int j=0; j<MAXN; j++){
			nxt[j] = dp[j];
			if(j - a[i].c >= 0 && j - a[i].c < MAXN){
				nxt[j] = max(nxt[j], dp[j - a[i].c] + a[i].v);
			}
		}
		memcpy(dp, nxt, sizeof(dp));
	}
	cout << *max_element(dp, dp + MAXN) << endl;
}
