// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2014J/
#include <iostream>
#define MAXN 200100
#define endl '\n'
using namespace std;
int dp[MAXN],vetor[MAXN],n;
int func(int ini){
	if (dp[ini] != -1) return dp[ini];
	return dp[ini] = func(ini + 1 + vetor[ini+1]);
}
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i=1;i<n;i++) dp[i] = -1;
	dp[n] = 1;
	for(int i=1;i<=n;i++) cin >> vetor[i];
	for(int i=1;i<=n;i++) if (func(i) == 1) cout << i << endl;
	return 0;
}