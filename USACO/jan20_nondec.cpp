#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 50005;
const int MAXQ = 200005;
const int mod = 1e9 + 7;

int n, q, a[MAXN], l[MAXQ], r[MAXQ];
lint ret[MAXQ];

int dl[MAXN][20][20];
int dr[MAXN][20][20];

void solve(int s, int e, vector<int> x){
	if(s == e){
		for(auto &i : x) ret[i] = 2;
		return;
	}
	int m = (s+e)/2;
	vector<int> lx, rx, qr;
	for(auto &i : x){
		if(r[i] <= m) lx.push_back(i);
		else if(l[i] > m) rx.push_back(i);
		else qr.push_back(i);
	}
	solve(s, m, lx);
	solve(m+1, e, rx);
	memset(dl[m + 1], 0, sizeof(dl[m + 1]));
	for(int i=m; i>=s; i--){
		memcpy(dl[i], dl[i + 1], sizeof(dl[i]));
		for(int x=a[i]; x<20; x++){
			for(int y=x; y<20; y++){
				dl[i][a[i]][y] += dl[i + 1][x][y];
				if(dl[i][a[i]][y] >= mod) dl[i][a[i]][y] -= mod;
			}
		}
		dl[i][a[i]][a[i]]++;
	}
	memset(dr[m], 0, sizeof(dr[m]));
	for(int i=m+1; i<=e; i++){
		memcpy(dr[i], dr[i - 1], sizeof(dr[i]));
		for(int x=0; x<=a[i]; x++){
			for(int y=x; y<=a[i]; y++){
				dr[i][x][a[i]] += dr[i - 1][x][y];
				if(dr[i][x][a[i]] >= mod) dr[i][x][a[i]] -= mod;
			}
		}
		dr[i][a[i]][a[i]]++;
	}
	for(auto &i : qr){
		lint lend[20] = {};
		lint rend[20] = {};
		lend[0] = rend[19] = 1;
		for(int j=0; j<20; j++){
			for(int k=j; k<20; k++){
				lend[k] += dl[l[i]][j][k];
				rend[j] += dr[r[i]][j][k];
			}
		}
		for(int x=0; x<20; x++){
			lend[x] %= mod;
			rend[x] %= mod;
		}
		for(int x=0; x<20; x++){
			for(int y=x; y<20; y++){
				ret[i] += 1ll * lend[x] * rend[y] % mod;
			}
		}
		ret[i] %= mod;
	}
}

int main(){
	freopen("nondec.in", "r", stdin);
	freopen("nondec.out", "w", stdout);
	scanf("%d %*d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i]--;
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++) scanf("%d %d",&l[i],&r[i]);
	vector<int> idx(q); iota(all(idx), 0);
	solve(1, n, idx);
	for(int i=0; i<q; i++) printf("%lld\n", ret[i]);
}
