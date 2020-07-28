// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc09s5
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAXN 1011
#define MAXM 30010
using namespace std;
int dp[MAXN][MAXM],resp1,resp2,M,N,K;
int main(){
	scanf("%d %d %d",&M,&N,&K);
	for(int k=1;k<=K;k++){
		int x,y,r,b;
		scanf("%d %d %d %d",&x,&y,&r,&b);
		for(int nx = max(1,x - r);nx <= min(N,x + r);nx++){
			double dist = sqrt(r*r - (nx - x)*(nx - x));
			int ny1 = max((int)ceil(y - dist),1);
			int ny2 = min(M,(int)floor(y + dist));
			dp[nx][ny1] += b;
			dp[nx][ny2+1] -= b;
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			dp[i][j] += dp[i][j-1];
			if(dp[i][j] > resp1){
				resp1 = dp[i][j];
				resp2 = 1;
			}
			else if(dp[i][j] == resp1){
				resp2++;
			}
		}
	}
	printf("%d\n%d\n",resp1,resp2);
	return 0;
}