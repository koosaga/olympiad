// Ivan Carvalho
// Solution to https://dmoj.ca/problem/year2018p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXL = 21;
const int MAXS = 190;
ll dp[MAXL][MAXS][2];
vector<int> digitos;
ll solve(int pos,int soma,int flag){
	if(soma < 0) return 0;
	if(pos == digitos.size()) return (soma == 0);
	if(dp[pos][soma][flag] != -1) return dp[pos][soma][flag];
	if(flag){
		ll total = 0;
		for(int i = 0;i<digitos[pos];i++){
			total += solve(pos+1,soma - i,0);
		}
		total += solve(pos+1, soma - digitos[pos],flag );
		return dp[pos][soma][flag] = total;
	}
	else{
		ll total = 0;
		for(int i = 0;i<=9;i++){
			total += solve(pos+1,soma - i,0);
		}
		return dp[pos][soma][flag] = total;
	}
}
ll qtd(ll val,ll alvo){
	if(val == 0) return 0;
	digitos.clear();
	memset(dp,-1,sizeof(dp));
	while(val != 0){
		digitos.push_back(val % 10);
		val /= 10;
	}
	reverse(digitos.begin(),digitos.end());
	return solve(0,alvo,1);
}
ll existe(ll a,ll b,ll alvo){
	ll contei = qtd(b,alvo) - qtd(a-1,alvo);
	return (contei > 0);
}
int main(){
	ll a,b;
	cin >> a >> b;
	ll resposta = 0;
	for(int i = 1;i<=180;i++){
		resposta += existe(a,b,i);
	}
	cout << resposta << endl;
	return 0;
}