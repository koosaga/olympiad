// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpi
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3002;

double dp[MAXN][MAXN],P[MAXN];
int vis[MAXN][MAXN],N;

double solve(int pos,int heads){
	
	if(heads < 0) return 0.0;

	if(pos == 0){
		return (heads == 0);
	}

	if(vis[pos][heads]) return dp[pos][heads];
	vis[pos][heads] = 1;

	return dp[pos][heads] =  (P[pos])*solve(pos-1,heads-1) + (1.0 - P[pos])*solve(pos-1,heads);

}

int main(){

	cin >> N;
	for(int i = 1;i<=N;i++){
		cin >> P[i];
	}

	double tot = 0;
	for(int heads = 0;heads<=N;heads++){
		int tails = N - heads;
		if(heads > tails) tot += solve(N,heads);
	}

	printf("%.9lf\n",tot);

	return 0;

}