// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1822
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 201
#define MAXF 51
using namespace std;
int dp[MAXN][MAXF],demanda[MAXN],x,y,z,w,n,instancia;
int solve(int dia,int funcionarios){
	if(dp[dia][funcionarios] != -1) return dp[dia][funcionarios];
	if(dia == n){
		if(funcionarios >= demanda[dia]){
			int custodiario = demanda[dia]*z + (funcionarios - demanda[dia])*w + funcionarios*y;
			return dp[dia][funcionarios] = custodiario;
		}
		else{
			int custodiario = (demanda[dia] - funcionarios)*x + demanda[dia]*z + demanda[dia]*y;
			return dp[dia][funcionarios] = custodiario;
		}
	}
	if(funcionarios >= demanda[dia]){
		int melhor = solve(dia+1,funcionarios) + demanda[dia]*z + (funcionarios - demanda[dia])*w;
		for(int novosfuncionarios = funcionarios - 1;novosfuncionarios >= 0;novosfuncionarios--){
			int custo = solve(dia+1,novosfuncionarios) + demanda[dia]*z + (funcionarios - demanda[dia])*w + (funcionarios - novosfuncionarios)*y;
			melhor = min(melhor,custo);
		}
		return dp[dia][funcionarios] = melhor;
	}
	else{
		int melhor = solve(dia+1,demanda[dia]) + demanda[dia]*z + (demanda[dia] - funcionarios)*x;
		for(int novosfuncionarios = demanda[dia] - 1;novosfuncionarios >= 0;novosfuncionarios--){
			int custo = solve(dia+1,novosfuncionarios) + demanda[dia]*z + (demanda[dia] - funcionarios)*x + (demanda[dia] - novosfuncionarios)*y;
			melhor = min(melhor,custo);
		}
		return dp[dia][funcionarios] = melhor;
	}
}
int main(){
	while(scanf("%d",&n) && n){
		memset(dp,-1,sizeof(dp));
		for(int i=1;i<=n;i++){
			scanf("%d",&demanda[i]);
		}
		scanf("%d %d %d %d",&x,&y,&z,&w);
		printf("Instancia %d\n%d\n\n",++instancia,solve(1,0));
	}
	return 0;
}
