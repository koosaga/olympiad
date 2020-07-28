// Ivan Carvalho
// Solution to https://www.spoj.com/problems/LAWRENCE/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 510;
const ll INF = 1e18;
ll entrada[MAXN],quadrado[MAXN],soma[MAXN];
ll F[MAXN][MAXN];
int L[MAXN][MAXN];
ll N,K;
ll C(int i,int j){
	if(i > j) return 0;
	return (soma[j] - soma[i-1])*(soma[j] - soma[i-1]) - (quadrado[j] - quadrado[i-1]);
}
void solve(int k,int l1,int l2,int opt1,int opt2){
	if(l1>l2) return;
	int lm = (l1+l2)/2;
	int opt = -1;
	ll best = INF;
	for(int cand = opt1;cand <= min(opt2,lm);cand++){
		ll novo = F[cand-1][k-1] + C(cand,lm);
		if(novo < best){
			best = novo;
			opt = cand;
		} 
	}
	F[lm][k] = best;
	L[lm][k] = opt;
	solve(k,l1,lm-1,opt1,opt);
	solve(k,lm+1,l2,opt,opt2);
}
int main(){
	cin >> N >> K;
	K++;
	for(int i = 1;i<=N;i++){
		cin >> entrada[i];
		soma[i] = soma[i-1] + entrada[i];
		quadrado[i] = quadrado[i-1] + entrada[i]*entrada[i];
	}
	for(int i = 1;i<=N;i++) F[i][1] = C(1,i);
	for(int k = 2;k<=K;k++){
		solve(k,1,N,1,N);
	}
	cout << F[N][K]/2LL << endl;
	return 0;
}