// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c3p5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 17;
const int MAXS = 138;
ll dp[MAXN][MAXS][2];
vector<ll> digitos;
ll solve(int pos,int soma,int flag){
	if(pos == 0){
		if(soma >= 10 || soma < 0) return 0;
		if(flag){
			if(soma <= digitos[pos]) return 1;
			return 0;
		}
		return 1;
	}
	if(dp[pos][soma][flag] != -1) return dp[pos][soma][flag];
	if(flag){
		ll tot = 0;
		for(ll i = 0;i<digitos[pos];i++) tot += solve(pos-1,soma-i,0);
		tot += solve(pos-1,soma - digitos[pos],1);
		return dp[pos][soma][flag] = tot;
	}
	else{
		ll tot = 0;
		for(ll i = 0;i<=9;i++) tot += solve(pos-1,soma-i,0);
		return dp[pos][soma][flag] = tot;
	}
}
ll calcula(ll val,ll objetivo){
	if(val == 0) return 0;
	memset(dp,-1,sizeof(dp));
	digitos.clear();
	while(val != 0){
		digitos.push_back(val % 10);
		val /= 10;
	}
	//for(ll i = digitos.size() - 1;i>=0;i--) printf("%lld",digitos[i]);
	//printf("\n");
	//printf("%lld\n",solve(digitos.size()-1,objetivo,1));
	return solve(digitos.size()-1,objetivo,1);
}
int main(){
	ll A,B,S;
	scanf("%lld %lld %lld",&A,&B,&S);
	ll v1 = calcula(B,S), v2 = calcula(A-1,S);
	printf("%lld\n",v1-v2);
	ll ini = A, fim = B,meio,resp = -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(calcula(meio,S) >= v2 + 1){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}
	printf("%lld\n",resp);
	return 0;
}