// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco2d1p1
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 310;
const ll INF = 1e16;

ll dp[MAXN][MAXN][2],A[MAXN],B[MAXN],T,memo[MAXN][MAXN];
int n,m,K,N,M,vis[MAXN][MAXN][2],iteracao;

ll  solve(int p1,int p2,int lado){
	if(p1 > n || p2 > m) return INF;
	if(vis[p1][p2][lado] == iteracao) return dp[p1][p2][lado];
	vis[p1][p2][lado] = iteracao;
	if(p1 == n && p2 == m) return dp[p1][p2][lado] = 0;
	if(lado == 0){
		ll opt1 = solve(p1+1,p2,0) + abs(A[p1 +1] - A[p1])*((n - p1) + (m - p2));
		ll opt2 = solve(p1,p2+1,1) + abs(B[p2+1] - A[p1])*((n - p1) + (m - p2));
		return dp[p1][p2][lado] = min(opt1,opt2); 
	}
	else{
		ll opt1 = solve(p1+1,p2,0) + abs(A[p1 + 1] - B[p2])*((n - p1) + (m - p2));
		ll opt2 = solve(p1,p2+1,1) + abs(B[p2+1] - B[p2])*((n - p1) + (m - p2));
		return dp[p1][p2][lado] = min(opt1,opt2); 
	}
}

ll testa(int qtd1,int qtd2){
	if(memo[qtd1][qtd2] != 0) return memo[qtd1][qtd2];	
	n = qtd1;m = qtd2;
	iteracao++;
	return memo[qtd1][qtd2] = (qtd1+qtd2)*T - min(solve(0,0,0),solve(0,0,1));
}

bool compara(ll a,ll b){
	return a > b;
}

int main(){
	cin >> K >> T;
	for(int i = 1;i<=K;i++){
		ll x;
		cin >> x;
		if(x >= 0){
			N++;
			A[N] = x;
		}
		else{
			M++;
			B[M] = x;
		}
	}
	
	sort(A,A+N+1);
	sort(B,B+M+1,compara);

	ll ans = 0,opt = M;
	for(int a = 0;a<=N;a++){
		while(opt - 1 >= 0 && testa(a,opt) < testa(a,opt - 1) ){
			opt--;
		}
		ans = max(ans,testa(a,opt));
	}
	opt = N;
	for(int b = 0;b<=M;b++){
		while(opt - 1 >= 0 && testa(opt,b) < testa(opt-1,b)){
			opt--;
		}
		ans = max(ans, testa(opt,b) );
	}

	cout << ans << endl;

	return 0;
}
