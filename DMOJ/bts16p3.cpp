// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bts16p3
#include <cstdio>
#include <cstring>
#define MOD 1000000007
#define MAXN 100010
int dp[MAXN],resp,n,vetor[MAXN];
char entrada[MAXN];
inline int add(int x,int y){
	return (x+y)%MOD;
}
int solve(int pos){
	if(dp[pos] != -1) return dp[pos];
	if(pos == n || vetor[pos+1] != vetor[pos]) return dp[pos] = 1;
	return dp[pos] = add(1,solve(pos+1));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",entrada);
		if('a' <= entrada[0] && entrada[0] <= 'z'){
			vetor[i] = entrada[0] - 'A';
		}
		else{
			vetor[i] = entrada[0] - 'A';
		}
	}
	//for(int i=1;i<=n;i++) printf("%d ",vetor[i]);
	//printf("\n");
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++){
		resp = add(resp,solve(i));
	}
	printf("%d\n",resp);
	return 0;
}