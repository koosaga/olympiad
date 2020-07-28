// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2008
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 2*(1e3 + 1);
const int MAXB = 1e4 + 1e3;
int pai[MAXN],custo[MAXN],membros_dsp[MAXN],membros_ppp[MAXN],tam[2];
vector<int> valor[2],despesa[2];
int dp[MAXN][MAXB][2];
int D,P,R,B,N;
int find(int x){
	//printf("Trying to find parent %d\n",x);
	if(x == pai[x]){
		//printf("Found\n");
		return x;
	}
	//printf("Recursion\n");
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	//printf("Trying to join %d %d\n",x,y);
	if(x == y) return;
	if(custo[x] > custo[y]){
		custo[x] += custo[y];
		membros_dsp[x] += membros_dsp[y];
		membros_ppp[x] += membros_ppp[y];
		pai[y] = x;
	}
	else{
		custo[y] += custo[x];
		membros_dsp[y] += membros_dsp[x];
		membros_ppp[y] += membros_ppp[x];
		pai[x] = y;
	}
	//printf("Joined\n");
}
int solve(int obj,int aguenta,int tipo){
	//printf("Obj %d Aguenta %d Tipo %d\n",obj,aguenta,tipo);
	if(obj >= tam[tipo]) return 0;
	//printf("Padrao passou\n");
	if(dp[obj][aguenta][tipo] != -1) return dp[obj][aguenta][tipo];
	//printf("Temos que calcular\n");
	int nao_coloca = solve(obj+1,aguenta,tipo);
	if(despesa[tipo][obj] <= aguenta){
		int coloca = valor[tipo][obj] + solve(obj+1, aguenta - despesa[tipo][obj],tipo);
		//printf("DP[%d][%d][%d] = %d\n",obj,aguenta,tipo,max(nao_coloca,coloca));
		return dp[obj][aguenta][tipo] = max(coloca,nao_coloca);
	}
	//printf("DP[%d][%d][%d] = %d\n",obj,aguenta,tipo,nao_coloca);
	return dp[obj][aguenta][tipo] = nao_coloca;
}
int main(){
	scanf("%d %d %d %d",&D,&P,&R,&B);
	N = D + P;
	for(int i=1;i<=D;i++){
		scanf("%d",&custo[i]);
		pai[i] = i;
		membros_dsp[i] = 1;
	}
	for(int i=D+1;i<=N;i++){
		scanf("%d",&custo[i]);
		pai[i] = i;
		membros_ppp[i] = 1;
	}
	while(R--){
		int u,v;
		scanf("%d %d",&u,&v);
		join(u,D+v);
	}
	for(int i=1;i<=N;i++){
		if(find(i) == i){
			if(membros_dsp[i] < membros_ppp[i]){
				valor[0].push_back(membros_ppp[i] - membros_dsp[i]);
				despesa[0].push_back(custo[i]);
			}
			else if(membros_dsp[i] > membros_ppp[i]){
				valor[1].push_back(membros_dsp[i] - membros_ppp[i]);
				despesa[1].push_back(custo[i]);
			}
		}
	}
	tam[0] = valor[0].size();
	tam[1] = valor[1].size();
	//printf("%d %d\n",tam[0],tam[1]);
	memset(dp,-1,sizeof(dp));
	printf("%d %d\n",D + solve(0,B,0), P + solve(0,B,1));
	return 0;
}
