// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2013C/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
#define MAXN 30010
using namespace std;
typedef long long ll;
vector<int> grafo[MAXN];
ll dp[MAXN],longest[MAXN];
ll solve(int v){
	if(dp[v] != -1) return dp[v];
	dp[v] = 0;
	for(int i=0;i<grafo[v].size();i++){
		dp[v] += solve(grafo[v][i]);
	}
	return dp[v];
}
ll func(int v){
	if(longest[v] != -1) return longest[v];
	longest[v] = solve(v);
	ll maior = 0;
	for(int i=0;i<grafo[v].size();i++){
		maior = max(maior,func(grafo[v][i]));
	}
	longest[v] += maior;
	return longest[v];
}
int main(){
	memset(dp,-1,sizeof(dp));
	memset(longest,-1,sizeof(longest));
	int n,s;
	getint(n);
	getint(s);
	dp[n] = 1;
	for(int i=1;i<=s;i++){
		int u,v;
		getint(u);
		getint(v);
		grafo[u].push_back(v);
	}
	printf("%lld\n",func(1));
	return 0;
}