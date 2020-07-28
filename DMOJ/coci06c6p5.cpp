// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c6p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 116230;
const int TAM = 13;

int pode[TAM],N;
ll A,B,X,dp[TAM][2][MAX];
vector<ll> digitos,pot;
string entrada;

ll solve(int pos,int flag,ll resto){
	if(pos == N){
		if(resto == 0) return 1;
		return 0;
	}
	if(dp[pos][flag][resto] != -1) return dp[pos][flag][resto];
	ll tot = 0;
	ll limite = 9;
	if(flag) limite = digitos[pos];
	for(ll i = 0;i<=limite;i++){
		if(!pode[i]) continue;
		tot += solve(pos+1, flag && (i == digitos[pos]), (resto + i*pot[pos]) % X );
	}
	return dp[pos][flag][resto] = tot;
}

ll conta(ll numero){
	if(numero == 0){
		if(pode[0]) return 1;
		else return 0;
	}
	digitos.clear();
	pot.clear();
	ll potencia = 1;
	while(numero != 0){
		digitos.push_back(numero % 10LL);
		pot.push_back(potencia);
		numero /= 10LL;
		potencia *= 10LL;
	}
	reverse(digitos.begin(),digitos.end());
	reverse(pot.begin(),pot.end());
	memset(dp,-1,sizeof(dp));
	N = digitos.size();
	if(pode[0]) return solve(0,1,0);
	else{
		ll tot = 0;
		for(int i = 0;i<N;i++){
			tot += solve(i,i == 0,0);
		}
		return tot;
	}
}

ll checa(ll numero){
	while(numero != 0){
		if(!pode[numero % 10]) return 0;
		numero /= 10;
	}
	return 1;
}

int main(){
	cin >> X >> A >> B;
	cin >> entrada;
	for(char c : entrada){
		pode[c - '0'] = 1;
	}
	if(X >= MAX){
		int tot = 0;
		if(A % X != 0) A += (X - (A %X));
		for(ll v = A;v<=B;v+=X){
			tot += checa(v);
		}
		cout << tot << endl;
	}
	else{
		cout << conta(B) - conta(A-1) << endl;	}
	return 0;
}