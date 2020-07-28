// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpj
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 302;

double dp[MAXN][MAXN][MAXN];
int N,vis[MAXN][MAXN][MAXN];

double solve(int x,int y,int z){
	
	if(vis[x][y][z]) return dp[x][y][z];
	//printf("Solving %d %d %d\n",x,y,z);
	vis[x][y][z] = 1;

	if(x == 0 && y == 0 && z == 0) return dp[x][y][z] = 0;

	int soma = x + y + z;
	double convertido = (double)soma;
	double tot = (N - soma)/convertido;
	
	//printf("Tot antes %d %d %d %d %lf\n",N - soma,x,y,z,tot);

	if(x != 0) tot += x*((solve(x-1,y,z) + 1)/convertido);
	if(y != 0) tot += y*((solve(x+1,y-1,z) + 1)/convertido);
	if(z != 0) tot += z*((solve(x,y+1,z-1) + 1)/convertido);

	//printf("Tot (%d,%d,%d) = %lf\n",x,y,z,tot);

	return dp[x][y][z] = tot;

}

int main(){

	int a[4] = {0,0,0,0};

	cin >> N;

	for(int i = 1;i<=N;i++){
		int x;
		cin >> x;
		a[x]++;
	}

	printf("%.9lf\n",solve(a[1],a[2],a[3]));

	return 0;
}