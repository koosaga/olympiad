// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dps
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e4 + 10;
const int MAXD = 1e2 + 10;
const int MOD = 1e9 + 7;

vector<int> digitos;
string s;
int N,D;
ll dp[MAXN][2][MAXD];

ll solve(int pos,int flag,int resto){

	if(pos == N) return (resto == 0);
	if(dp[pos][flag][resto] != -1) return dp[pos][flag][resto];

	ll tot = 0;
	int limit = (flag) ? (digitos[pos]) : (9);
	for(int i = 0;i<=limit;i++){
		tot += solve(pos+1,flag && (i == limit), (resto + i) % D );
	}

	return dp[pos][flag][resto] = tot % MOD;

}

int main(){

	cin >> s;
	cin >> D;
	N = (int)s.size();
	for(int i = 0;i<N;i++){
		digitos.push_back(s[i] - '0');
	}
	memset(dp,-1,sizeof(dp));

	ll ans = solve(0,1,0) - 1;
	if(ans < 0) ans += MOD;
	cout << ans << endl;


	return 0;

}