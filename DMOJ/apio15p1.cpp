// Ivan Carvalho
// Solution to https://dmoj.ca/problem/apio15p1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2010;
const int MAXM = 110;
int dp[MAXN],N,A,B;
bool tab[MAXM][MAXM],possivel;
ll soma[MAXN],proibido,atual;
ll calc(ll a,ll b){return soma[b] - soma[a-1];}
int solve(int pos){
	if(dp[pos] != -1) return dp[pos];
	if(pos == N + 1) return dp[pos] = 0;
	int best = MAXN;
	for(int quebra = pos;quebra<=N;quebra++){
		if((calc(pos,quebra)) & proibido) continue;
		best = min(best, 1 + solve(quebra+1));
	}
	return dp[pos] = best;
}
void check(int pos,int resta){
	if(possivel) return;
	if(tab[pos][resta]) return;
	tab[pos][resta] = true;
	if(pos == N + 1 && resta == 0) possivel = true;
	if(resta == 0 || pos == N+1) return;
	for(int quebra = pos;quebra<=N;quebra++){
		if((calc(pos,quebra)) & proibido) continue;
		check(quebra+1,resta - 1);
	}
}
int main(){
	cin >> N >> A >> B;
	if(A == 1){
		for(int i = 1;i<=N;i++){
			cin >> soma[i];
			soma[i] += soma[i-1];
		}
		for(ll i = 41;i>=0;i--){
			proibido |= (1LL << i);
			memset(dp,-1,sizeof(dp));
			if(solve(1) > B){
				proibido ^= (1LL << i);
				atual |= (1LL << i);
			}
		}
		cout << atual << endl;
	}
	else{
		for(int i = 1;i<=N;i++){
			cin >> soma[i];
			soma[i] += soma[i-1];
		}
		for(ll i = 37;i>=0;i--){
			proibido |= (1LL << i);
			memset(tab,false,sizeof(tab));
			possivel = false;
			for(int j = A;j<=B;j++) check(1,j);
			if(!possivel){
				proibido ^= (1LL << i);
				atual |= (1LL << i);
			}
		}
		cout << atual << endl;
	}
	return 0;
}
