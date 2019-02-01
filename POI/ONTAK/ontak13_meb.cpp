#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 505;
const int MAXM = 20005;

int n, m = 20000;
lint dp[MAXM], nxt[MAXM], a, d;
int c;
struct cht2{
	pi v[MAXM];
	int sz;
	void clear(){ sz = 0; }
	long double cross(pi a, pi b){
		return ((long double)(b.second - a.second)) / (a.first - b.first);
	}
	void add_line(lint x, lint y){	
		pi p(x, y);
		while(sz >= 2 && cross(v[sz - 2], v[sz - 1]) <= cross(v[sz - 1], p)){
			sz--;
		}
		v[sz++] = p;
	}
	lint query(lint x){
		if(sz == 0) return 1e18;
		while(sz >= 2 && v[sz - 2].first * x + v[sz - 2].second <= v[sz - 1].first * x + v[sz - 1].second){
			sz--;
		}
		return v[sz - 1].first * x + v[sz - 1].second;
	}
}cht2;
struct cht{
	pi v[MAXM];
	int sz;
	void clear(){ sz = 0; }
	long double cross(pi a, pi b){
		return ((long double)(b.second - a.second)) / (a.first - b.first);
	}
	void add_line(lint x, lint y){	
		pi p(x, y);
		while(sz >= 2 && cross(v[sz - 2], v[sz - 1]) >= cross(v[sz - 1], p)){
			sz--;
		}
		v[sz++] = p;
	}
	lint query(lint x){
		if(sz == 0) return 1e18;
		while(sz >= 2 && v[sz - 2].first * x + v[sz - 2].second <= v[sz - 1].first * x + v[sz - 1].second){
			sz--;
		}
		return v[sz - 1].first * x + v[sz - 1].second;
	}
}cht;

int main(){
	int k;
	scanf("%d %d",&n,&k);
	memset(dp, 0x3f, sizeof(dp));
	memset(nxt, 0x3f, sizeof(nxt));
	nxt[0] = 0;
	dp[0] = 0;
	for(int i=1; i<=n; i++){
		cin >> a >> d >> c;
		a <<= 1;
		for(int j=0; j<=m; j++) dp[j] -= j * a + j * j * d;
		for(int j=0; j<=m; j+=c+1){
			cht2.clear();
			for(int k=j; k<=min(j+c, m); k++){
				cht2.add_line(k, dp[k]);
				nxt[k] = min(nxt[k], cht2.query(d * (2*k-1)) + a * k - (k * k - k) * d);
			}
		}
		for(int j=c+1; j<=m; j+=c+1){
			cht.clear();
			int ptr = j - 1;
			for(int k=min(j+c, m); k>=j; k--){
				while(ptr >= k - c){
					cht.add_line(ptr, dp[ptr]);
					ptr--;
				}
				nxt[k] = min(nxt[k], cht.query(d * (2*k-1)) + a * k - (k * k - k) * d);
			}
		}
		memcpy(dp, nxt, sizeof(dp));
	}
	while(k--){
		int x;
		cin >>x;
		cout << dp[x] / 2 <<endl;
	}
}
