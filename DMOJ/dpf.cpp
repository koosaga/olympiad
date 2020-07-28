// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpf
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3010;

string s,t;
int dp[MAXN][MAXN],N,M;
stack<char> resposta;

int solve(int a,int b){

	if(a < 0 || b < 0) return 0;

	if(dp[a][b] != -1) return dp[a][b];

	if(s[a] == t[b]) return dp[a][b] = 1 + solve(a-1,b-1);

	return dp[a][b] = max(solve(a-1,b),solve(a,b-1));

}

void build(int a,int b){

	if(a < 0 || b < 0) return;

	if(s[a] == t[b]){
		resposta.push(s[a]);
		build(a-1,b-1);
		return;
	}

	if(solve(a-1,b) > solve(a,b-1)) build(a-1,b);
	else build(a,b-1);

}

int main(){

	memset(dp,-1,sizeof(dp));

	cin >> s;
	cin >> t;

	N = (int)s.size();
	M = (int)t.size();

	build(N-1,M-1);

	while(!resposta.empty()){
		cout << resposta.top();
		resposta.pop();
	}
	cout << endl;

	return 0;

}