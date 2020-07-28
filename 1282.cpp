// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1282
#include <cstdio>
#include <algorithm>
#define MAXN 1001
using namespace std;
typedef long long ll;
const ll INF = 1e15;
ll X[MAXN],W[MAXN];
ll soma[MAXN][MAXN];
ll F[MAXN][MAXN];
int P[MAXN][MAXN];
int N,K;
void precalcula(){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=i;j++){
			soma[i][j] = soma[i][j-1] + (X[i] - X[j])*W[j];
		}
	}
}
inline ll custo(int i,int j){
	if(i > j) return 0;
	//printf("Custo %lld %lld : %lld\n",i,j,soma[j][j] - soma[j][i-1]);
	return soma[j][j] - soma[j][i-1];
}
void solve(int k,int l1,int l2,int p1,int p2){
	if(l1 > l2) return;
	int lm = (l1+l2)/2;
	P[k][lm] = -1;
	F[k][lm] = INF;
	for(ll g=p1;g<=min(p2,lm-1);g++){
		ll novocusto = F[k-1][g] + custo(g+1,lm);
		if(novocusto < F[k][lm]){
			F[k][lm] = novocusto;
			P[k][lm] = g;
		}
	}
	solve(k,l1,lm-1,p1,P[k][lm]);
	solve(k,lm+1,l2,P[k][lm],p2);
}
int main(){
	while(scanf("%d %d",&N,&K) != EOF){
		for(int i=1;i<=N;i++){
			scanf("%lld %lld",&X[i],&W[i]);
		}
		precalcula();
		for(int l=1;l<=N;l++){
			F[1][l] = custo(1,l);
			P[1][l] = 0;
		}
		//printf("Precalculo Feito\n");
		for(int k=2;k<=K;k++){
			solve(k,0,N,0,N);
		}
		printf("%lld\n",F[K][N]);
	}
	return 0;
}
