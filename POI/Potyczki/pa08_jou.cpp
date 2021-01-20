#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int mod = 1e9 + 9;

int n, adj[20][20];

struct mat{
	int A[20][20];
	mat operator*(const mat &m)const{
		mat ret;
		memset(ret.A, 0, sizeof(ret.A));
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					ret.A[j][k] += 1ll * A[j][i] * m.A[i][k] % mod;
					ret.A[j][k] %= mod;
				}
			}
		}
		return ret;
	}
}E;

int Do(int x){
	mat ret = E, piv;
	memcpy(piv.A, adj, sizeof(piv.A));
	while(x){
		if(x & 1) ret = ret * piv;
		piv = piv * piv;
		x >>= 1;
	}
	lint tmp = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			tmp += ret.A[i][j];
		}
	}
	return tmp % mod;
}

void solve(){
	int m, k, d;
	memset(adj, 0, sizeof(adj));
	memset(E.A, 0, sizeof(E.A));
	cin >> n >> m >> k >> d;
	for(int i=0; i<n; i++) E.A[i][i] = 1;
	for(int i=0; i<m; i++){
		int x, y;
		cin >> x >> y;
		x--; y--;
		adj[x][y] = adj[y][x] = 1;
	}
	if(d == 1){ // special case
		printf("%d\n", k == 1);
		return;
	}
	lint ret = 0;
	for(int i=0; i<(1<<k); i++){
		int tadj[21][21];
		memcpy(tadj, adj, sizeof(tadj));
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if((i >> j) % 2 || (i >> k) % 2){
					// one of them is in graph, remove it
					adj[j][k] = 0;
				}
			}
		}
		int ans = Do(d - 1);
		for(int j=0; j<k; j++){
			if((i >> j) & 1) ans = -ans;
		}
		ret += ans + mod;
		memcpy(adj, tadj, sizeof(tadj));
	}
	printf("%lld\n", ret % mod);
}

int main(){
    solve();
	return 0;
}

