// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc15j5
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 251;
// Ultimo, restam
int n,k;
int dp[MAXN][MAXN][MAXN];
int solve(int numero,int pessoas,int restam){
	if(pessoas == 0 && restam == 0) return 1;
	if(restam < 0 || numero > restam|| pessoas < 0) return 0;
	if(dp[numero][pessoas][restam] != -1) return dp[numero][pessoas][restam];
	int ret = 0;
	for(int i = 1;i<=pessoas;i++) ret += solve(numero+1,pessoas - i,restam - numero*i);
	return dp[numero][pessoas][restam] =  ret + solve(numero+1,pessoas,restam);
}
int main(){
	scanf("%d %d",&k,&n);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",solve(1,n,k));
	return 0;
}