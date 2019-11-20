#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305;
using lint = long long;

int mod;
lint pwr[MAXN * MAXN], bin[MAXN][MAXN];
int pick[MAXN][MAXN][MAXN];

// {0, 0, 32, 16688, 15312474}
// {993675287, 185671658, 534372228}

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n;

int f(int pos, int r, int c){
	if(pos == n) return ((r + c) % 2 ? (mod - 1) : 1);
	if(pos < n / 2){
		
	}
	else if(pos >= (n + 1) / 2){

	}
	else{
		ret += f(pos + 1, r, c) * pwr[
	}
}
lint TwoDiag(int _n){
	n= _n;
	return f(0, 0, 0);
}

lint OneDiag(int n){
	lint ret = 0;
	pick[0][0][0] = 1;
	for(int i=1; i<=n; i++){
		for(int j=0; j<=i; j++){
			for(int k=0; k<=i; k++){
				pick[i][j][k] = (j ? pick[i-1][j-1][k] : 0) + (k ? pick[i-1][j][k-1] : 0);
				if(pick[i][j][k] >= mod) pick[i][j][k] -= mod;
				if(j && k) pick[i][j][k] += pick[i-1][j-1][k-1];
				if(pick[i][j][k] >= mod) pick[i][j][k] -= mod;
			}
		}
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			for(int k=max(i, j); k<=min(i+j, n); k++){
				lint val = (bin[n][k] * pick[k][i][j] % mod) * pwr[(n - i) * (n - j) + k + 1 - n] % mod;
				if((i + j) % 2 == 1) ret += mod - val;
				else ret += val;
			}
		}
	}
	return ret % mod;
}

lint NoDiag(int n){
	lint ret = 0;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			lint cmp = 0;
			if(i == 0 || j == 0){
				cmp = pwr[n * n - (i + j) * (n - 1)];
			}
			else{
				cmp = pwr[(n - i) * (n - j) + 1];
			}
			cmp *= bin[n][i] * bin[n][j] % mod;
			cmp %= mod;
			if((i + j) % 2 == 1) ret += mod - cmp;
			else ret += cmp;
		}
	}
	return ret % mod;
}

int main(){
	int n; cin >> n >> mod;
	pwr[0] = 1;
	for(int i=1; i<MAXN*MAXN; i++){
		pwr[i] = pwr[i-1] * 2 % mod;
	}
	for(int i=0; i<MAXN; i++){
		bin[i][0] = 1;
		for(int j=1; j<=i; j++){
			bin[i][j] = (bin[i-1][j] + bin[i-1][j-1]) % mod;
		}
	}
	lint ans = NoDiag(n) - 2ll * OneDiag(n) + TwoDiag(n) + 2ll * mod;
	ans %= mod;
	cout << ans << endl;
}
