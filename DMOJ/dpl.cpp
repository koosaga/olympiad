// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpl
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 3002;

ll dp[MAXN][MAXN];
bool vis[MAXN][MAXN];
int A[MAXN],N;

ll solve(int i,int j){

	if(vis[i][j]) return dp[i][j];

	vis[i][j] = 1;

	if(i == j) return dp[i][j] = A[i];

	return dp[i][j] = max(A[i] - solve(i+1,j), A[j] - solve(i,j-1));

}

int main(){

	cin >> N;
	for(int i = 1;i<=N;i++){
		cin >> A[i];
	} 

	cout << solve(1,N) << endl;

	return 0;

}