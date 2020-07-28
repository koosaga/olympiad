// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c1p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 210;
const ll MOD = 1e5;

char oposto[2*MAXN];
ll dp[MAXN][MAXN],N,flag;
string s,cjt;

ll solve(ll ini,ll fim){
	if(dp[ini][fim] != -1) return dp[ini][fim];
	ll tot = 0;
	for(char car_1 : cjt){
		if(s[ini] != '?' && s[ini] != car_1) continue;
		for(ll quebra = ini + 1;quebra<=fim;quebra++){
			if(s[quebra] != '?' && s[quebra] != oposto[car_1]) continue;
			ll fator1 = (ini + 1 == quebra) ? (1LL) : (solve(ini+1,quebra-1));
			ll fator2 = (quebra + 1 <= fim) ? (solve(quebra+1,fim)) : (1LL);
			tot += fator1*fator2;
		}
	}
	if(tot >= MOD) flag = 1;
	return dp[ini][fim] = tot % MOD;
}

string exibe(ll numero){
	string davez;
	if(numero == 0){
		davez.push_back('0');
	}
	else{
		while(numero != 0){
			davez.push_back((numero % 10) + '0');
			numero /= 10;
		}
	}
	if(flag){
		while(davez.size() < 5){
			davez.push_back('0');
		}
	}
	reverse(davez.begin(),davez.end());
	return davez;
}

int main(){
	memset(dp,-1,sizeof(dp));
	cin >> N;
	cin >> s;
	cjt.push_back('(');
	oposto['('] = ')';
	cjt.push_back('[');
	oposto['['] = ']';
	cjt.push_back('{');
	oposto['{'] = '}';
	cout << exibe(solve(0,N-1)) << endl;
	return 0;
}