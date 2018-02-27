#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 505;
const int MAXM = 20005;

int n, m = 20000;
lint dp[MAXM], nxt[MAXM], a, d, c;

lint nc2(int x){
	return x * (x-1) / 2;
}

struct cht{
	pi v[MAXM];
	int sz;
	void clear(){ sz = 0; }
	double cross(pi a, pi b){
		return (1.0 * (b.second - a.second)) / (a.first - b.first);
	}
	void add_line(lint x, lint y){	
		pi p(x, y);
		while(sz >= 2 && cross(v[sz - 2], v[sz - 1]) >= cross(v[sz - 1], p)){
			sz--;
		}
		v[sz++] = p;
	}
	lint query(int x){
		if(sz == 0) return 1e18;
		while(sz >= 2 && v[sz - 2].first * x + v[sz - 2].second <= v[sz - 1].first * x + v[sz - 1].second){
			sz--;
		}
		return v[sz - 1].first * x + v[sz - 1].second;
	}
}cht;

void solve(int s, int e){
	if(s == e){
		return;
	}
	int m = (s+e)/2;
	solve(s, m);
	solve(m+1, e);
	int k = m;
	cht.clear();
	for(int j=e; j>m; j--){
		while(k >= s && k >= j - c){
			cht.add_line(k * d / 2, dp[k]);
			k--;
		}
		nxt[j] = min(nxt[j], cht.query(2 * j - 1) + j * a - (j * j - j) * (d / 2));
	}
}

int main(){
	int k;
	scanf("%d %d",&n,&k);
	memset(dp, 0x3f, sizeof(dp));
	memset(nxt, 0x3f, sizeof(nxt));
	dp[0] = nxt[0] = 0;
	lint sum = 0;
	for(int i=1; i<=n; i++){
		cin >> a >> d >> c;
		d <<= 1;
		a <<= 1;
		for(int i=0; i<=m; i++){
			dp[i] -= i * a + i * i * (d / 2);
		}
		solve(0, m);
		memcpy(dp, nxt, sizeof(dp));
	}
	while(k--){
		int x;
		cin >>x;
		cout << dp[x] / 2 <<endl;
	}
}
